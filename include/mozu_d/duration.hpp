#ifndef NEQUATION_MOZU_DURATION_HPP
#define NEQUATION_MOZU_DURATION_HPP

namespace mozu::duration {
size_t secs(long double nsecs) {
  return nsecs * 441000.;
}

namespace literals {
  size_t operator "" _s(unsigned long long nsecs) {
    return secs(nsecs);
  }

  size_t operator "" _s(long double nsecs) {
    return secs(nsecs);
  }
}
}

namespace mozu::prelude {
  using namespace duration;
  using namespace duration::literals;
}

#endif
