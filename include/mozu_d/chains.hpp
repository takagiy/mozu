#ifndef NEQUATION_MOZU_CHAINS_HPP
#define NEQUATION_MOZU_CHAINS_HPP
#include "./generator.hpp"

#include <iostream>
#include <utility>
#include <numbers>
#include <cstddef>

namespace mozu::chains {
  generator konst(double constant) {
    while(true) {
      co_yield constant;
    }
  }

  auto add(double rhs) {
    return [=](double x) {
      return x + rhs;
    };
  }

  auto sub(double rhs) {
    return [=](double x) {
      return x - rhs;
    };
  }

  auto mul(double rhs) {
    return [=](double x) {
      return x * rhs;
    };
  }

  auto div(double rhs) {
    return [=](double x) {
      return x / rhs;
    };
  }

  generator add(generator one, generator two) {
    while(one.next() && two.next()) {
      co_yield  *one + *two;
    }
  }

  generator sub(generator one, generator two) {
    while(one.next() && two.next()) {
      co_yield *one - *two;
    }
  }

  generator mul(generator one, generator two) {
    while(one.next() && two.next()) {
      co_yield *one * *two;
    }
  }

  generator div(generator one, generator two) {
    while(one.next() && two.next()) {
      co_yield *one / *two;
    }
  }

  generator hertz(generator freq) {
    double value = 0.;

    while(freq.next()) {
      using std::numbers::pi;

      value += pi * *freq / 44100.;
      if (value > 2 * pi) {
        value -= 2 * pi;
      }

      co_yield value;
    }
  }

  template <DoubleFunction F>
  struct map_t {
    F function_;

    generator operator()(generator&& args) {
      return apply(function_, std::move(args));
    }

    generator apply(F function, generator args) {
      while(args.next()) {
        co_yield function(*args);
      }
    }
  };

  template <DoubleFunction F>
  map_t<F> map(F function) {
    return { function };
  }

  struct cut_t {
    std::size_t length_;

    generator operator()(generator&& source) {
      return apply(length_, std::move(source));
    }

    generator apply(std::size_t length, generator source) {
      for(std::size_t i = 0; i < length && source.next(); ++i) {
        co_yield *source;
      }
    }
  };

  cut_t cut(std::size_t length) {
    return { length };
  }
}

namespace mozu::pitches {
  generator c4() {
    return chains::konst(261.63);
  }
}

namespace mozu::prelude {
  using namespace chains;
  using namespace pitches;
}

namespace mozu {
  generator::generator(double constant) : generator(chains::konst(constant)) {}

  generator operator+(generator&& lhs, generator&& rhs) {
    return chains::add(std::move(lhs), std::move(rhs));
  }

  generator operator-(generator&& lhs, generator&& rhs) {
    return chains::sub(std::move(lhs), std::move(rhs));
  }

  generator operator*(generator&& lhs, generator&& rhs) {
    return chains::mul(std::move(lhs), std::move(rhs));
  }

  generator operator/(generator&& lhs, generator&& rhs) {
    return chains::div(std::move(lhs), std::move(rhs));
  }
}

#endif
