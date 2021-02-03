#ifndef NEQUATION_MOZU_GENERATOR_HPP
#define NEQUATION_MOZU_GENERATOR_HPP

#include <coroutine>
#include <concepts>
#include <optional>
#include <utility>
#include <ranges>

namespace mozu {
struct generator;

template <class F>
concept Chain = std::invocable<F, generator&&>;

template <class F>
concept DoubleFunction =
  std::invocable<F, double> &&
  std::convertible_to<std::invoke_result_t<F, double>, double>;

struct generator {
  struct promise_type {
    auto get_return_object() {
      return generator(handle_type::from_promise(*this));
    }

    auto initial_suspend() {
      return std::suspend_always();
    }

    auto final_suspend() {
      return std::suspend_always();
    }

    auto yield_value(double value) {
      value_ = value;
      return std::suspend_always();
    }

    void return_void() {}

    void unhandled_exception() {
      std::terminate();
    }

    double value_;
  };

  using handle_type = std::coroutine_handle<promise_type>;

  explicit generator(handle_type handle) : handle_(handle) {}

  generator(const generator&) = delete;

  generator(generator&& other) : handle_(other.handle_) {
    other.handle_ = nullptr;
  }

  ~generator() {
    if (handle_) {
      handle_.destroy();
    }
  }

  generator(double constant);

  generator(const std::ranges::output_range<double> auto&);

  double operator*() const {
    return handle_.promise().value_;
  }

  std::optional<double> next() const {
    handle_.resume();
    return handle_.done() ? std::nullopt : std::optional(**this);
  }

  handle_type handle_;
};
  
auto operator>>(generator&& generator, Chain auto chain) {
  return chain(std::move(generator));
}

namespace chains {
  template <DoubleFunction F>
  struct map_t;

  template <DoubleFunction F>
  map_t<F> map(F function);
}

auto operator>>(generator&& generator, DoubleFunction auto function) {
  return std::move(generator) >> chains::map(function);
}
}

#endif
