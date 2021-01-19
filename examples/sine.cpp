#include <mozu>
using namespace mozu::prelude;

auto main() -> int {
  hertz(c4) >> sin >> save("sine.wav");
}
