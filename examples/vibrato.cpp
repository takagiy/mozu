#include <mozu>
#include <cmath>
using namespace mozu::prelude;

auto main() -> int {
  auto lfo = hertz(c4() / 20) >> sin >> mul(100);
  hertz(c4() * 2 + std::move(lfo)) >> sin >> mul(30000) >> cut(3_s) >> save("vibrato.wav");
}
