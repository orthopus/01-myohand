#ifndef STATUS_H
#define STATUS_H

/* --- Status Enum Definition ---
AUTHOR : Come BUTIN
COMPANY : ORTHOPUS

Enum to define the status of the motor control
*/

#include <stdint.h>

enum Status : uint8_t {
  Working = 0,
  StallShort = 1,
  StallLong = 2,
  TempAlert = 5,
  VoltageAlert = 6
};

#endif
