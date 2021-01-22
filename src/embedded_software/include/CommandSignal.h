#ifndef COMMANDSIGNAL_H
#define COMMANDSIGNAL_H

/* --- CommandSignal Class Definition ---
AUTHOR : Come BUTIN
COMPANY : ORTHOPUS

This class provides a container for the command signal,
ie a Direction (+/- 1) and a positive Intensity.

It also provides a function to transform EMG signal into
a command.
*/

#include "Config.h"
#include "Sensor.h"

class CommandSignal {
private:
  int8_t direction;
  int8_t prev_direction;
  uint16_t command;
  uint16_t prev_command;

public:
  CommandSignal(int8_t dir = 1, uint16_t cmd = 0);

  // Check if the direction has changed
  bool dirChangeHappened() const;

  // Create a new command value from EMG signals,
  // and shift prev values to corresponding variables
  void update_from_emg(const Sensor &emgO, const Sensor &emgC);

  // Constrain the difference (command - prev_command) in [-decel; accel]
  void derivative_constrain(uint16_t accel, uint16_t decel = 0);

  // Set command to zero
  void stop();

  // Getters & Setters (useful only)
  int8_t getDirection() const;
  uint16_t getCommand() const;
  uint16_t getPrevCommand() const;
};

#endif
