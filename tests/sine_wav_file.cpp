#include <mozu>
#include <iostream>
#include <cmath>
using namespace mozu::prelude;

auto main() -> int {
  auto sine = hertz(c4()) >> sin >> cut(1_s) >> mul(30000);
  save("test.wav")(std::move(sine));
}
