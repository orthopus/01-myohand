#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

/* --- MotorControl Class Definition ---
AUTHOR : Come BUTIN
COMPANY : ORTHOPUS

This class provide all the functions relative to
the motor control, especially :
- the PWM configuration
- stall torque management
- motor driver control
*/

#include "CommandSignal.h"
#include "Config.h"
#include "CustomBuffer.h"
#include "Data.h"
#include "Pins.h"
#include "Status.h"
#include <Arduino.h>
#include <EEPROM.h>

class MotorControl {

private:
  // Stall current monitoring for detection
  CustomBuffer<float, 5> current_ratio_buffer;
  // State of stall detection and stop
  bool stall_shut_off = false;
  // Period counter to enable current in motor after stall detection
  uint8_t stall_timer = 0;
  // Period counter to enable current in motor after stall detect
  uint16_t stall_detection_counter = 0;

  // Motor Command
  uint16_t motor_command = 0;
  uint16_t last_stall_command = 0;

  // Cycle counter for future data analysis
  uint16_t total_cycles_counter = 0;
  uint16_t direction_change_counter = 0;
  uint8_t cycle_state = 0;

  // TO BE DELETED : debug variable to debug the code easier
  float debug = 0.0;

public:
  MotorControl();

  // Initialization function of Timer and Clock for PWM
  void setPWMfrequency();

  // Initilization function of pins mode for driver control
  void setPins(uint8_t ina_pin, uint8_t inb_pin, uint8_t ena_pin,
               uint8_t enb_pin, uint8_t pwm_pin);

  // Initilization function of cycle counters
  void initCounters();

  // Main function of stall detection and motor stop, return status of motor
  Status run(CommandSignal &cmd, const Sensor &current, const Sensor &battery);

  // Write on Pins to send command to the motor driver
  void write_to_motor(const CommandSignal &cmd);

  // Getters & Setters (useful only)
  float getDebug() const;

  uint16_t getMotorCommand() const;
  uint16_t getTotalCyclesCounter() const;
  uint16_t getDirectionChangeCounter() const;
};

#endif
