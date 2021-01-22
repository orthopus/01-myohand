#ifndef BIDIRECTIONSENSOR_H
#define BIDIRECTIONSENSOR_H

/* --- VirtualSensor Class Definition ---
AUTHOR : Come BUTIN
COMPANY : ORTHOPUS

This class is implemented to emulate an analogInput
to test the code and debug it. Data are stored in arrays
and can be found in TestValues.h
*/

#include "Sensor.h"
#include <Arduino.h>

class BiDirectionSensor : public Sensor {

private:
  const uint8_t inactive_pin;
  const bool direction;
  const bool middle_value;

public:
  BiDirectionSensor(const bool dir, const uint16_t mid_val, const uint8_t pin,
                    const uint8_t inactive_pin, const float unit_per_dgt = 1.0);
  void setPin();
  void acquire();
};

#endif
