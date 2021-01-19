#include <mozu>
#include <iostream>
using namespace mozu::prelude;

auto main() -> int {
  auto freq = hertz(c4);
  auto sine = freq >> mozu::chains::sin;
  while(sine.next()) {
    std::cout << *sine << std::endl;
  }
}
