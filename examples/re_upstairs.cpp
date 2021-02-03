#include <mozu>
#include <cmath>
#include <list>
using namespace mozu::prelude;

auto main() -> int {
  items(std::list{60, 62, 64, 65, 67, 69, 71, 72}) >> stretch(0.5_s) >> key_to_freq >> hertz >> rect(1./3.) >> mul(65534 / 2) >> save("re_upstairs.wav");
}
