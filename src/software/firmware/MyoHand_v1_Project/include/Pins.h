#ifndef PINS_H
#define PINS_H

/* --- Pins Namespace Definition ---
AUTHOR : Come BUTIN
COMPANY : ORTHOPUS

Pins wiring is declared here !
*/

#include <Arduino.h>

namespace Pins {

static const uint8_t CURRENT_SENS = A2;
static const uint8_t TEMP_SENS = A4;
static const uint8_t BATTERY_SENS = A5;
static const uint8_t EMG_O = A6; // EMG used for opening
static const uint8_t EMG_C = A7; // EMG used for closing
static const uint8_t MOTOR_PWM = 9;
static const uint8_t MOTOR_INA = 7;
static const uint8_t MOTOR_INB = A0;
static const uint8_t MOTOR_ENA = 8;
static const uint8_t MOTOR_ENB = A1;

} // namespace Pins

#endif
