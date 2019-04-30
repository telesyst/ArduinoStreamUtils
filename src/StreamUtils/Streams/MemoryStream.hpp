// StreamUtils - github.com/bblanchon/ArduinoStreamUtils
// Copyright Benoit Blanchon 2019
// MIT License

#pragma once

#include <Stream.h>

#include "../Buffers/CircularBuffer.hpp"
#include "../Ports/DefaultAllocator.hpp"

namespace StreamUtils {

template <typename TAllocator>
class BasicMemoryStream : public Stream {
 public:
  BasicMemoryStream(size_t capacity, TAllocator allocator = TAllocator())
      : _buffer(capacity, allocator) {}

  BasicMemoryStream(const BasicMemoryStream &src) : _buffer(src._buffer) {}

  int available() override {
    return static_cast<int>(_buffer.available());
  }

  int peek() override {
    return _buffer.isEmpty() ? -1 : _buffer.peek();
  }

  int read() override {
    return _buffer.isEmpty() ? -1 : _buffer.read();
  }

  // WARNING: we cannot use "override" because most cores don't define this
  // function as virtual
  virtual size_t readBytes(char *data, size_t size) {
    return _buffer.readBytes(data, size);
  }

  size_t write(uint8_t data) {
    return _buffer.isFull() ? 0 : _buffer.write(data);
  }

  size_t write(const uint8_t *data, size_t size) override {
    return _buffer.write(data, size);
  }

  using Stream::write;

  void flush() override {
    _buffer.clear();
  }

 private:
  CircularBuffer<TAllocator> _buffer;
};

using MemoryStream = BasicMemoryStream<DefaultAllocator>;

}  // namespace StreamUtils