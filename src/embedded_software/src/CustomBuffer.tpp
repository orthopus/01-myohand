#include "CustomBuffer.h"

template <typename T, size_t S> CustomBuffer<T, S>::CustomBuffer() {}

// Return Average as a float, on all data
template <typename T, size_t S>
float CustomBuffer<T, S>::getFloatAverage() const {
  float sum = 0.0;
  for (uint8_t i = 0; i < this->size(); i++) {
    sum += (*this)[i];
  }
  return (sum / this->size());
}

// Return Average as a float, on the last 'size' points
template <typename T, size_t S>
float CustomBuffer<T, S>::getFloatAverage(uint8_t size) const {
  float sum = 0.0;
  uint16_t s = min(this->size(), size);
  for (uint8_t i = 0; i < s; i++) {
    sum += (*this)[i];
  }
  return (sum / s);
}

// Return Average as an int, on all data
template <typename T, size_t S>
uint16_t CustomBuffer<T, S>::getIntAverage() const {
  uint16_t sum = 0;
  for (uint8_t i = 0; i < this->size(); i++) {
    sum += (*this)[i];
  }
  return (sum / this->size());
}

// Return Average as an int, on the last 'size' points
template <typename T, size_t S>
uint16_t CustomBuffer<T, S>::getIntAverage(uint16_t size) const {
  uint16_t sum = 0;
  uint16_t s = min(this->size(), size);
  for (uint8_t i = 0; i < s; i++) {
    sum += (*this)[i];
  }
  return (sum / s);
}
