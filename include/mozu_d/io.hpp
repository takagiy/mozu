#ifndef NEQUATION_MOZU_IO_HPP
#define NEQUATION_MOZU_IO_HPP

#include <string_view>
#include <iostream>
#include <fstream>
#include <cstddef>

namespace mozu::io {
namespace detail {
  void write_bytes(std::ofstream& file, const char* string) {
    file << string;
  }

  void write_bytes(std::ofstream& file, int bytes, std::size_t nbytes= 4) {
    for(std::size_t i = 0; i < nbytes; ++i, bytes >>= 8) {
       file.put(static_cast<char>(bytes & 0xff));
    }
  }
}

auto save(std::string_view path) {
  using detail::write_bytes;

  return [=](generator sample) -> void {
    std::ofstream file(path.data(), std::ios::out | std::ios::binary);

    write_bytes(file, "RIFF"); // 00: RIFF id
    write_bytes(file, 0);      // 04: chunk bytes (temp)
    write_bytes(file, "WAVE"); // 08: format
    write_bytes(file, "fmt "); // 12: fmt id
    write_bytes(file, 16);     // 16: fmt chunk bytes
    write_bytes(file, 1, 2);   // 20: audio type
    write_bytes(file, 1, 2);   // 22: channels
    write_bytes(file, 44100);  // 24: frames per second
    write_bytes(file, 88200);  // 28: bytes per second
    write_bytes(file, 2, 2);   // 32: bytes per frame
    write_bytes(file, 16);     // 34: bits per sample
    write_bytes(file, "data"); // 36: data chunk id 
    write_bytes(file, 0);      // 40: data hunk bytes (temp)
  };
}
}

namespace mozu::prelude {
  using namespace io;
}

#endif
