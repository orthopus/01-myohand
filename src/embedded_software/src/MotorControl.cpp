#include "MotorControl.h"

MotorControl::MotorControl() {}

// Initialization function of Timer and Clock for PWM
void MotorControl::setPWMfrequency() {
  // Set PB0 as output
  PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTB_gc;

  // Set The f_CLK_PER at 20MHz instead of 16MHz
  // change lines in boards.txt

  // Frequency: Fpwm = Fclk_per/(N(PER+1)) with N the prescalar
  // Max resolution: R_pwm = (log(PER+1))/(log(2))
  TCA0.SINGLE.PER = Config::PWM_PERIOD;

  // CMP sets the duty cycle of the PWM signal -> DT = CMP0 / PER
  TCA0.SINGLE.CMP0 = 0;

  // Counter starts at 0, offset cleaned
  TCA0.SINGLE.CNT = 0x00;

  // Configuring CTRLB register
  // Compare 0 Enabled: Output WO0 (PB0) is enabled
  // Single slope PWM mode is selected
  TCA0.SINGLE.CTRLB = TCA_SINGLE_CMP0EN_bm | TCA_SINGLE_WGMODE_SINGLESLOPE_gc;

  // Set TimerA Prescaler to 1 (instead of 64 by default)
  // /!\ millis() and micros() are using TimerA with 64 prescaler
  //    -> Board configuration file has te be adapted
  // Enable the timer peripheral
  TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc | TCA_SINGLE_ENABLE_bm;
}

void MotorControl::setPins(uint8_t ina_pin, uint8_t inb_pin, uint8_t ena_pin,
                           uint8_t enb_pin, uint8_t pwm_pin) {
  pinMode(ina_pin, OUTPUT);
  pinMode(inb_pin, OUTPUT);
  pinMode(ena_pin, OUTPUT);
  pinMode(enb_pin, OUTPUT);
  pinMode(pwm_pin, OUTPUT);

  digitalWrite(ena_pin, HIGH);
  digitalWrite(enb_pin, HIGH);
}

void MotorControl::initCounters() {
  EEPROM.get(Config::DIR_CHANGE_COUNTER_ADRR, direction_change_counter);
  EEPROM.get(Config::CYCLE_COUNTER_ADDR, total_cycles_counter);
}

// Main function of stall detection and motor stop, return status of motor
Status MotorControl::run(CommandSignal &cmd, const Sensor &current,
                         const Sensor &battery) {
  float current_ratio =
      0; // ratio ~ Imot / Umot; when ratio~=1, the motor is stalled
  Status status = Working;

  // Avoiding calculating ratio for small commands to avoid division by 0 (or
  // noise) Division by 8 is supposed to be fast !
  if (motor_command > Config::MAX_CMD / 8 && battery.getAvgValue() > 0) {
    current_ratio = (Config::MAX_CMD * Data::R_MOT) *
                    current.getRawValueUnit() /
                    (motor_command * battery.getAvgValueUnit());
  }
  // Save result in buffer to get the average
  current_ratio_buffer.push(current_ratio);
  float ratio_avg = current_ratio_buffer.getFloatAverage();

  bool new_stall = false;
  // if ratio is high (motor stalled or near)
  // and current is high (otherwise, the motor won't burn)
  // STALL mode is activated
  if (ratio_avg > Config::STALL_RATIO_THOLD &&
      current.getRawValueUnit() > Data::SAFE_CURRENT) {
    stall_detection_counter++;
  } else if (stall_detection_counter != 0) {
    stall_detection_counter = 0;
  }

  if (stall_detection_counter >= Config::STALL_DETECTION_TIME) {
    new_stall = true;
    stall_shut_off = true;
    stall_timer = 0;
    last_stall_command = motor_command;

    if (cycle_state == 1 && cmd.getDirection() == 1) {
      cycle_state++;
    }
  } // else, if STALL mode is already activated, increment counter
  else if (stall_shut_off) {
    stall_timer++;
  }

  // if the counter exceed "long" time, STALL mode is deactivated
  if (stall_timer >= Config::STALL_TIMER_LONG) {
    stall_shut_off = false;
  }

  // if the STALL mode is activated
  if (stall_shut_off) {
    // for a short time, then motor is stopped in any cases
    if (stall_timer < Config::STALL_TIMER_SHORT) {
      cmd.stop();
      status = StallShort;
    }
    // for an intermediate time, motor can be activated under conditions
    else {
      status = StallLong;
      stall_detection_counter = 0;
      // Command is authorized if the motor is changing its direction
      // or if the command is higher than the last time the motor was stalled
      // (meaning the user wants to apply more pressure)
      if (!cmd.dirChangeHappened() &&
          (cmd.getCommand() < Config::STALL_CMD_MARGIN * last_stall_command)) {
        cmd.stop();
      }
    }
  }
  // if STALL mode is not activated
  else {
    // constrain the positive derivative of the command,
    // to avoid peak current in the motor
    // cmd.derivative_constrain(Config::DELTA_CMD_MAX);
    status = Working;
  }

  // Handle counters for future analysis
  if (cmd.dirChangeHappened()) {
    if (cmd.getDirection() == 1) {
      direction_change_counter++;
      EEPROM.put(Config::DIR_CHANGE_COUNTER_ADRR, direction_change_counter);
    }
    if ((cycle_state == 0 & cmd.getDirection() == 1) ||
        (cycle_state == 2 & cmd.getDirection() == -1)) {
      cycle_state++;
    }
  }
  if (cycle_state >= 3) {
    cycle_state = 0;
    total_cycles_counter++;
    EEPROM.put(Config::CYCLE_COUNTER_ADDR, total_cycles_counter);
  }

  debug = ratio_avg;
  cmd.derivative_constrain(Config::CMD_MAX_ACCEL, Config::CMD_MAX_DECEL);

  return status;
}

// Write on Pins to send command to the motor driver
void MotorControl::write_to_motor(const CommandSignal &cmd) {
  // Store command written to the motor, and set value in PWM register
  motor_command = cmd.getCommand();
  TCA0.SINGLE.CMP0 = motor_command;
  // Set PINs to set the write dimension
  digitalWrite(Pins::MOTOR_INA, cmd.getDirection() == 1);
  digitalWrite(Pins::MOTOR_INB, cmd.getDirection() == -1);
}

// Getters & Setters (useful only)
float MotorControl::getDebug() const { return debug; }

uint16_t MotorControl::getMotorCommand() const { return motor_command; }

uint16_t MotorControl::getTotalCyclesCounter() const {
  return total_cycles_counter;
}
uint16_t MotorControl::getDirectionChangeCounter() const {
  return direction_change_counter;
}
