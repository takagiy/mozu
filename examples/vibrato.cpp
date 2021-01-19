#include <mozu>
using namespace mozu::prelude;

auto main() -> int {
  auto lfo = hertz(c4 / 100) >> sin;
  hertz(c4 + lfo) >> sin >> save("vibrato.wav");
}
