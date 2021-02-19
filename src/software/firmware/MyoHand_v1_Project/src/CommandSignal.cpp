#include "CommandSignal.h"

CommandSignal::CommandSignal(int8_t dir = 1, uint16_t cmd = 0)
    : direction{dir}, command{cmd} {}

// Create a new command value from EMG signals,
// and shift prev values to corresponding variables
#define SQUARED_SHAPE
void CommandSignal::update_from_emg(const Sensor &emgO, const Sensor &emgC) {
  prev_command = command;
  command = 0;
  prev_direction = direction;
  uint16_t emg_close = emgC.getAvgValue();
  uint16_t emg_open = emgO.getAvgValue();
  uint16_t emgO_cmd = 0;
  uint16_t emgC_cmd = 0;

  // If the 2 EMG signals are under MIN Threshold, stop the motor
  if (emg_close < Config::EMG_CLOSE_MIN_VALUE &&
      emg_open < Config::EMG_OPEN_MIN_VALUE) {
    command = 0;
  } else {
    // Detect which EMG signal is stronger than the other, and constrain its
    // boundaries
    if (emg_close >= Config::EMG_CLOSE_MIN_VALUE) {
      emgC_cmd = constrain(emg_close, Config::EMG_CLOSE_MIN_VALUE,
                           Config::EMG_CLOSE_MAX_VALUE);
      // remap EMG signal linearly from [EMG_MIN; EMG_MAX] to [0; MAX_CMD]
      emgC_cmd = (emgC_cmd - Config::EMG_CLOSE_MIN_VALUE) *
                 ((float)Config::MAX_CMD /
                  (Config::EMG_CLOSE_MAX_VALUE - Config::EMG_CLOSE_MIN_VALUE));
    } // else 0
    if (emg_open >= Config::EMG_OPEN_MIN_VALUE) {
      emgO_cmd = constrain(emg_open, Config::EMG_OPEN_MIN_VALUE,
                           Config::EMG_OPEN_MAX_VALUE);
      // remap EMG signal linearly from [EMG_MIN; EMG_MAX] to [0; MAX_CMD]
      emgO_cmd = (emgO_cmd - Config::EMG_OPEN_MIN_VALUE) *
                 ((float)Config::MAX_CMD /
                  (Config::EMG_OPEN_MAX_VALUE - Config::EMG_OPEN_MIN_VALUE));
    } // else 0

    if (emg_close > emg_open) {
      command = emgC_cmd;
      direction = 1;
    } else if (emg_open >= emg_close) {
      command = emgO_cmd;
      direction = -1;
    }

    command = constrain(command, 0, Config::MAX_CMD);

#ifdef SQUARED_SHAPE
    // apply a "square shape", keeping same boundaries, to be more precise with
    // low EMG signals
    command = (1.0 / Config::MAX_CMD) * command * command;
#endif
  }
}

// Constrain the difference (command - prev_command) in [-decel; accel]
void CommandSignal::derivative_constrain(const CommandSignal &prev_cmd,
                                         uint16_t accel, uint16_t decel = 0) {

  uint16_t min_constraint = 0;
  uint16_t max_constraint = prev_cmd.command + accel;

  if (prev_cmd.command > decel) {
    min_constraint = prev_cmd.command - decel;
  }
  if (prev_cmd.command + accel > Config::MAX_CMD) {
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

void CommandSignal::clone(const CommandSignal &cmd_signal) {
  command = cmd_signal.command;
  direction = cmd_signal.direction;
}

// Getters & Setters (useful only)
int8_t CommandSignal::getDirection() const { return direction; }
uint16_t CommandSignal::getCommand() const { return command; }
