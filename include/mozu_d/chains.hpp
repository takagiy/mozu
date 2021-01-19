#ifndef NEQUATION_MOZU_CHAINS_HPP
#define NEQUATION_MOZU_CHAINS_HPP
#include "./generator.hpp"

#include <numbers>
#include <cmath>

namespace mozu::chains {
  generator konst(double constant) {
    while(true) {
      co_yield constant;
    }
  }

  generator add(const generator& one, const generator& two) {
    while(one.next() && two.next()) {
      co_yield  *one + *two;
    }
  }

  generator sub(const generator& one, const generator& two) {
    while(one.next() && two.next()) {
      co_yield *one - *two;
    }
  }

  generator mul(const generator& one, const generator& two) {
    while(one.next() && two.next()) {
      co_yield *one * *two;
    }
  }

  generator div(const generator& one, const generator& two) {
    while(one.next() && two.next()) {
      co_yield *one / *two;
    }
  }

  generator hertz(const generator& freq) {
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

  generator sin(const generator& theta) {
    while(theta.next()) {
      co_yield std::sin(*theta);
    }
  }
}

namespace mozu::pitches {
  inline generator c4 = chains::konst(261.63);
}

namespace mozu::prelude {
  using namespace mozu::chains;
  using namespace mozu::pitches;
}

namespace mozu {
  generator::generator(double constant) : generator(chains::konst(constant)) {}

  generator operator+(const generator& lhs, const generator& rhs) {
    return chains::add(lhs, rhs);
  }

  generator operator-(const generator& lhs, const generator& rhs) {
    return chains::sub(lhs, rhs);
  }

  generator operator*(const generator& lhs, const generator& rhs) {
    return chains::mul(lhs, rhs);
  }

  generator operator/(const generator& lhs, const generator& rhs) {
    return chains::div(lhs, rhs);
  }
}

#endif
