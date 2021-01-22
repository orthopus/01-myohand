#include "CommandSignal.h"

CommandSignal::CommandSignal(int8_t dir = 1, uint16_t cmd = 0)
    : direction{dir}, prev_direction{dir}, command{cmd}, prev_command{cmd} {}

// Check if the direction has changed
bool CommandSignal::dirChangeHappened() const {
  int8_t dir_change = direction * prev_direction;
  return (dir_change == -1);
}

// Create a new command value from EMG signals,
// and shift prev values to corresponding variables
#define SQUARED_SHAPE
void CommandSignal::update_from_emg(const Sensor &emgO, const Sensor &emgC) {
  prev_command = command;
  command = 0;
  prev_direction = direction;
  uint16_t emg_close = emgC.getAvgValue();
  uint16_t emg_open = emgO.getAvgValue();

  // If the 2 EMG signals are under MIN Threshold, stop the motor
  if (emg_close < Config::EMG_MIN_VALUE && emg_open < Config::EMG_MIN_VALUE) {
    command = 0;
  } else {
    // Detect which EMG signal is stronger than the other, and constrain its
    // boundaries
    if (emg_close > emg_open && emg_close >= Config::EMG_MIN_VALUE) {
      command =
          constrain(emg_close, Config::EMG_MIN_VALUE, Config::EMG_MAX_VALUE);
      direction = 1;
    } else if (emg_open >= emg_close && emg_open >= Config::EMG_MIN_VALUE) {
      command =
          constrain(emg_open, Config::EMG_MIN_VALUE, Config::EMG_MAX_VALUE);
      direction = -1;
    }
    // remap EMG signal linearly from [EMG_MIN; EMG_MAX] to [0; SPEED_LIMIT]
    command = (command - Config::EMG_MIN_VALUE) *
              (Config::EMG_SCALE_FLOAT * Config::MAX_CMD /
               (Config::EMG_MAX_VALUE - Config::EMG_MIN_VALUE));
    command = constrain(command, 0, Config::MAX_CMD);

#ifdef SQUARED_SHAPE
    // apply a "square shape", keeping same boundaries, to be more precise with
    // low EMG signals
    command = (1.0 / Config::MAX_CMD) * command * command;
#endif
  }
}

// Constrain the difference (command - prev_command) in [-decel; accel]
void CommandSignal::derivative_constrain(uint16_t accel, uint16_t decel = 0) {

  uint16_t min_constraint = 0;
  uint16_t max_constraint = prev_command + accel;

  if (prev_command > decel) {
    min_constraint = prev_command - decel;
  }
  if (prev_command + accel > Config::MAX_CMD) {
    max_constraint = Config::MAX_CMD;
  }

  command = constrain(command, min_constraint, max_constraint);
  /*
    if (prev_command > decel) {
      if (command < prev_command - decel) {
        command = prev_command - decel;
      }
    }
    if (command > prev_command + accel) {
      command = prev_command + accel;
    }*/
}

// Set command to zero
void CommandSignal::stop() { command = 0; }

// Getters & Setters (useful only)
int8_t CommandSignal::getDirection() const { return direction; }
uint16_t CommandSignal::getCommand() const { return command; }
uint16_t CommandSignal::getPrevCommand() const { return prev_command; }
