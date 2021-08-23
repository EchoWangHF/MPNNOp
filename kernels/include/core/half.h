#pragma once
#include <stdint.h>
#include <iostream>
#include <memory>

typedef uint16_t half_t;

class half {
 public:
  half() : _data(0) {}
  // 拷贝构造函数，不能使用explicit, 否则无法用于拷贝形式的初始化；
  half(const half& data) { _data = data._data; }
  half(const float& data) { _data = convertFloat2Half(data); }

  half& operator=(const half& data) {
    _data = data._data;
    return *this;
  }
  half& operator=(const float& data) {
    _data = convertFloat2Half(data);
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, const half& data) {
    float float_data = data.convertHalf2Float(data._data);
    os << float_data;
    return os;
  }

  virtual ~half() {}

 private:
  half_t convertFloat2Half(const float& data) const;
  float convertHalf2Float(const half_t& data) const;

 private:
  half_t _data;
};
