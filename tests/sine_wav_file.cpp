#include <mozu>
#include <iostream>
#include <cmath>
using namespace mozu::prelude;

auto main() -> int {
  hertz(c4()) >> sin >> mul(30000) >> cut(1_s) >> save("test.wav");
}
