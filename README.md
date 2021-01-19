# mozu
synth

## Examples

[**click to play↓!**](doc/resources/sine.mp4)

```cpp
#include <mozu>
#include <cmath>
using namespace mozu::prelude;

auto main() -> int {
  hertz(c4()) >> sin >> mul(30000) >> cut(1_s) >> save("sine.wav");
}
```

[**click to play↓!**](doc/resources/vibrato.mp4)

```cpp
#include <mozu>
#include <cmath>
using namespace mozu::prelude;

auto main() -> int {
  auto lfo = hertz(c4() / 100) >> sin >> mul(100);
  hertz(c4() + std::move(lfo)) >> sin >> mul(30000) >> cut(3_s) >> save("vibrato.wav");
}
```

[**click to play↓!**](doc/resources/quantize.mp4)

```cpp
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
```
