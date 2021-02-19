#ifndef VIRTUALSENSOR_H
#define VIRTUALSENSOR_H

/* --- VirtualSensor Class Definition ---
AUTHOR : Come BUTIN
COMPANY : ORTHOPUS

This class is implemented to emulate an analogInput
to test the code and debug it. Data are stored in arrays
and can be found in TestValues.h
*/

#include <Arduino.h>
#include "Sensor.h"

class VirtualSensor : public Sensor{

private:
  const uint16_t array_size;
  const uint16_t *measure_array;
  uint16_t index = 0;

public:
  VirtualSensor(const uint16_t *array, const uint16_t size,
        const uint8_t pin, const float unit_per_dgt = 1.0);
  void acquire();
};

#endif
