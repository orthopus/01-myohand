#ifndef CUSTOMBUFFER_H
#define CUSTOMBUFFER_H

/* --- CustomBuffer Class Definition ---
AUTHOR : Come BUTIN
COMPANY : ORTHOPUS

This class is a subclass of CircularBuffer, available here :
https://github.com/rlogiacco/CircularBuffer.git#master

It provides template class for CircularBuffer, with functions
to calculate Average.
*/

#include <CircularBuffer.h>

template <typename T, size_t S>
class CustomBuffer : public CircularBuffer<T, S> {

public:
  /**
   * Disables copy constructor
   */
  CustomBuffer(const CustomBuffer &) = delete;
  CustomBuffer(CustomBuffer &&) = delete;

  /**
   * Disables assignment operator
   */
  CustomBuffer &operator=(const CustomBuffer &) = delete;
  CustomBuffer &operator=(CustomBuffer &&) = delete;

  CustomBuffer();

  // Return Average as a float, on all data or on the
  // last 'size' points
  float getFloatAverage() const;
  float getFloatAverage(uint8_t size) const;

  // Return Average as a float, on all data or on the
  // last 'size' points
  // /!\ WARNING : if the sum of all elements has a chance
  // to Overflow an uint16_t (65535), please use float version
  uint16_t getIntAverage() const;
  uint16_t getIntAverage(uint16_t size) const;
};

// Since CustomBuffer is a Template class and is not
// compiled by default, the .tpp file has to be included
#include <CustomBuffer.tpp>
#endif
