#include <mozu>
#include <cmath>
using namespace mozu::prelude;

auto main() -> int {
  auto sine = hertz(c4()) >> sin >> mul(30000);
  auto quantize = [](double x) -> double {
    return int(x) / 10000 * 10000;
  };
  std::move(sine) >> quantize >> cut(1_s) >> save("quantize.wav");
}
