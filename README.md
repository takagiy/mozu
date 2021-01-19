# mozu
synth

## Examples

[**click to play↓!**](https://imgur.com/a/2R90w8j)

```cpp
#include <mozu>
#include <cmath>
using namespace mozu::prelude;

auto main() -> int {
  hertz(c4()) >> sin >> mul(30000) >> cut(1_s) >> save("sine.wav");
}
```

[**click to play↓!**](https://imgur.com/a/xqoOjW4)

```cpp
#include <mozu>
#include <cmath>
using namespace mozu::prelude;

auto main() -> int {
  auto lfo = hertz(c4() / 100) >> sin >> mul(100);
  hertz(c4() + std::move(lfo)) >> sin >> mul(30000) >> cut(3_s) >> save("vibrato.wav");
}
```

[**click to play↓!**](https://imgur.com/a/v952XgK)

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
