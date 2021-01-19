#include <mozu>
#include <cmath>
using namespace mozu::prelude;

auto main() -> int {
  auto lfo = hertz(c4() / 100) >> sin >> mul(100);
  hertz(c4() + std::move(lfo)) >> sin >> mul(30000) >> cut(3_s) >> save("vibrato.wav");
}
