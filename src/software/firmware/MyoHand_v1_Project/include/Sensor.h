#ifndef SENSOR_H
#define SENSOR_H

/* --- Sensor Class Definition ---
AUTHOR : Come BUTIN
COMPANY : ORTHOPUS

This class provides functions to read analog input,
store the data and filter it.
*/

#include "CustomBuffer.h"
#include <Arduino.h>

class Sensor {
protected:
  const uint8_t sensor_pin;
  const float unit_per_digit;
  uint16_t measure;
  uint16_t average_value;
  float lp_value;
  CustomBuffer<uint16_t, 10> sensor_buffer;

public:
  Sensor(uint8_t pin, const float unit_per_dgt = 1.0);
  void setPin();
  void acquire();
  void initFilters();
  void avgFilter();
  void avgFilter(uint8_t size);
  void lp1Filter(float alpha);

  // Getters & Setters (useful only)
  uint16_t getRawValue();
  float getRawValueUnit();
  uint16_t getAvgValue();
  float getLP1ValueUnit();
  float getAvgValueUnit();
};

#endif
