#ifndef DATA_H
#define DATA_H

/* --- Data Namespace Definition ---
AUTHOR : Come BUTIN
COMPANY : ORTHOPUS

All data constants from motor or model are stored here !
*/

#include <stdint.h>

namespace Data {
/* --- MOTOR GLOBAL CHARACTERISTICS --- */
// [V], Battery Voltage
// static const float BATT_VOLTAGE = 7.0;
// [Ohm], Motor resistance
static const float R_MOT = 0.65;
// [A], Stall current under battery voltage
// static const float MAX_CURRENT = BATT_VOLTAGE / R_MOT;
// [A], Maximum continuous current of motor
static const float SAFE_CURRENT = 1.50;
// [A], Minimum voltage of battery authorized to protect the battery
static const float MIN_VOLTAGE = 7;

// [A/LSB] Gain of current feedback sensor :
static const float AMP_PER_UNIT = (5.0 / 1023.0 / 0.140);
// [V/LSB] Gain of battery voltage feedback :
static const float VOLT_PER_UNIT = (5.0 / 1023.0 / 0.5);
// [°C/LSB] Gain of thermal sensor :
static const float DEG_PER_UNIT = (5.0 / 1023.0 / 0.010);

/* --- MOTOR THERMAL MODEL --- */
// [°C], Estimation of outside temperature
static const uint16_t T_EXT = 21;
// [°C/W] Thermal resistance between rotor and stator
static const uint16_t RTH_ROT = 6;
// [s] Thermal time constant of the rotor
static const uint16_t TAU_ROT = 9;
// [°C/W] Thermal resistance between stator and the exterior
static const uint16_t RTH_ST = 7;
// [s] Thermal time constant of the rotor
static const uint16_t TAU_ST = 750;
}; // namespace Data

#endif
