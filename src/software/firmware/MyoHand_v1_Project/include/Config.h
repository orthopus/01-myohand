#ifndef CONFIG_H
#define CONFIG_H

/* --- Config Namespace Definition ---
AUTHOR : Come BUTIN
COMPANY : ORTHOPUS

All configuration constants are stored here !
*/

#include <stdint.h>

namespace Config {
/* --- PERIOD CONFIGURATION--- */
// [s], Sampling Period for all the programm
static const float CMD_PERIOD_SEC = 0.01;
// [us], Sampling period in microseconds
static const uint32_t MICROS_PERIOD = CMD_PERIOD_SEC * 1000000;

/* --- EMG CLOSE CONFIGURATION--- */
// [LSD], Dead zone to filter noise : EMG signals under limit go to zero
static const float EMG_CLOSE_MIN_VALUE = 80;
// [LSD], set the max value that EMG reach to scale command on it (max = 1023)
static const float EMG_CLOSE_MAX_VALUE = 600;

/* --- EMG OPEN CONFIGURATION--- */
// [LSD], Dead zone to filter noise : EMG signals under limit go to zero
static const float EMG_OPEN_MIN_VALUE = 80;
// [LSD], set the max value that EMG reach to scale command on it (max = 1023)
static const float EMG_OPEN_MAX_VALUE = 500;

/* --- FILTERING--- */
// [1], set the alpha coefficient for battery LPfilter, with tau = 30sec
static const float BATT_FILT_ALPHA = CMD_PERIOD_SEC / (30.0 + CMD_PERIOD_SEC);

/* --- COMMAND SIGNAL CONFIGURATION--- */
// [LSD] for 20KHz PWM frequency, 799 with 16MHz clock, 999 with 20MHz clock
static const uint16_t PWM_PERIOD = 999;
// [LSD] maximum Command possible
static const uint16_t MAX_CMD = (PWM_PERIOD + 1);
// [LSD], Command scale if needed (max = MAX_CMD)
static const float SPEED_LIMIT_FLOAT = 1.0 * MAX_CMD;
// [LSD], Command scale if needed (max = MAX_CMD)
static const float EMG_SCALE_FLOAT = 1.0;

/* --- CONTROL ALGORITHM CONFIGURATION--- */
// [LSD] Maximum acceleration of command (exprimed by a delta between 2 cmd)
static const uint16_t CMD_MAX_ACCEL = 35;
// [LSD] Maximum deceleration of command (exprimed by a delta between 2 cmd)
static const uint16_t CMD_MAX_DECEL = 50;
// [1] Stall ratio threshold to consider motor as quasi stalled
static const float STALL_RATIO_THOLD = 0.75;
// [1] Command percentage to consider that user did not released muscles after a
// stall state of motor
static const float STALL_CMD_MARGIN = 1.1;
// [period] Time to apply stall torque
static const uint16_t STALL_DETECTION_TIME = 5;
// [period] Time to stay in "Long stall mode"
static const uint16_t STALL_TIMER_LONG = 100;
// [period] Time to stay in "Short stall mode"
static const uint16_t STALL_TIMER_SHORT = 30;

/* --- MOTOR THERMAL LIMITS --- */
// [°C], Stator temperature limit
static const uint16_t STATOR_TEMP_LIMIT = 70;
// [°C], Estimation of outside temperature
static const uint16_t ROTOR_TEMP_LIMIT = 90;
// [°C], Estimation of outside temperature
static const uint16_t DELTA_TEMP_LIMIT = 40;

/* --- CYCLE COUNTERS ADRESSES --- */
static const uint8_t CYCLE_COUNTER_ADDR = 0;
static const uint8_t DIR_CHANGE_COUNTER_ADRR = 2;
static const uint8_t USE_CHRONOMETER_ADDR = 32;

}; // namespace Config

#endif
