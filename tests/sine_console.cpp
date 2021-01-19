#include <mozu>
#include <iostream>
#include <cmath>
using namespace mozu::prelude;

auto main() -> int {
  auto sine = hertz(c4()) >> sin >> cut(1_s);
  while(sine.next()) {
    std::cout << *sine << std::endl;
  }
}
