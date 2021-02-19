#include <Arduino.h>

#include "BiDirectionSensor.h"
#include "CommandSignal.h"
#include "CustomBuffer.h"
#include "MotorControl.h"
#include "Sensor.h"
#include "ThermalNode.h"
#include "VirtualSensor.h"

#include "Config.h"
#include "Data.h"
#include "Pins.h"

#include "RosDebug.h"
#include "Status.h"

#include "TestValues.h"

//#define VIRTUAL_TEST
//#define EMG_FROM_POTENTIOMETER
#define CURRENT_MONITORING_ACTIVATED
#define TEMP_SECURITY_ACTIVATED
#define VOLTAGE_SECURITY_ACTIVATED

bool newValue = false;
uint64_t previousTime;
uint16_t executionTime;
uint16_t use_chronometer;
uint64_t last_chrono_time;

#ifdef VIRTUAL_TEST
VirtualSensor emgClose(emgC_array, ARRAY_SIZE, Pins::EMG_C);
VirtualSensor emgOpen(emgO_array, ARRAY_SIZE, Pins::EMG_O);
VirtualSensor currentSens(cur_array, ARRAY_SIZE, Pins::CURRENT_SENS,
                          Data::AMP_PER_UNIT);
VirtualSensor battSens(batt_array, ARRAY_SIZE, Pins::BATTERY_SENS,
                       Data::VOLT_PER_UNIT);
#else
#ifdef EMG_FROM_POTENTIOMETER
BiDirectionSensor emgClose(true, 580, Pins::EMG_O, Pins::EMG_C);
BiDirectionSensor emgOpen(false, 580, Pins::EMG_O, Pins::EMG_C);
#else
Sensor emgClose(Pins::EMG_C);
Sensor emgOpen(Pins::EMG_O);
#endif
Sensor currentSens(Pins::CURRENT_SENS, Data::AMP_PER_UNIT);
Sensor battSens(Pins::BATTERY_SENS, Data::VOLT_PER_UNIT);
#endif
Sensor tempSens(Pins::TEMP_SENS, Data::DEG_PER_UNIT);

ThermalNode rotor(Config::CMD_PERIOD_SEC, Data::TAU_ROT, Data::RTH_ROT, 22.0,
                  Data::R_MOT);
ThermalNode stator(Config::CMD_PERIOD_SEC, Data::TAU_ST, Data::RTH_ST, 22.0,
                   0.0, Data::T_EXT);

MotorControl motor_control;

CommandSignal emg_command;

RosDebug ros_debug;

float debug_snapshot_1 = 0.0;
float debug_snapshot_2 = 0.0;
uint16_t debug_counter = 0;

Status status = Working;

void setup() {
  emgOpen.setPin();
  emgClose.setPin();
  currentSens.setPin();
  battSens.setPin();

  battSens.initFilters();

  motor_control.setPins(Pins::MOTOR_INA, Pins::MOTOR_INB, Pins::MOTOR_ENA,
                        Pins::MOTOR_ENB, Pins::MOTOR_PWM);
  motor_control.setPWMfrequency();
  motor_control.initCounters();

  ros_debug.init();

  EEPROM.get(Config::USE_CHRONOMETER_ADDR, use_chronometer);

  previousTime = micros();

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  // ----- ACQUISITION -----
  // AnalogRead function may take some times !

  emgOpen.acquire();
  emgClose.acquire();
  currentSens.acquire();
  tempSens.acquire();
  battSens.acquire();

  // ----- EMG FILTERING AND COMMAND -----
  emgOpen.avgFilter();
  emgClose.avgFilter();
  emg_command.update_from_emg(emgOpen, emgClose);
  debug_snapshot_1 = emg_command.getCommand();

  // ----- TEMPERATURE ESTIMATION ------
  // currentSens.avgFilter(5);
  tempSens.avgFilter(3);
  battSens.avgFilter(3);
  battSens.lp1Filter(Config::BATT_FILT_ALPHA);
  rotor.update_temp(currentSens.getRawValueUnit(), stator);
  stator.update_temp(rotor, true);

  // ----- STALL TORQUE MONITORING ------
#ifdef CURRENT_MONITORING_ACTIVATED
  status = motor_control.stall_handler(emg_command, currentSens, battSens);
  // debug_snapshot_2 = command.getCommand();
#endif

  // ----- TEMPERATURE SECURITY CHECK ------
#ifdef TEMP_SECURITY_ACTIVATED
  if (ThermalNode::getDeltaTemp(rotor, stator) > Config::DELTA_TEMP_LIMIT ||
      stator.getTemp() > Config::STATOR_TEMP_LIMIT ||
      rotor.getTemp() > Config::ROTOR_TEMP_LIMIT) {
    motor_control.stop();
    status = TempAlert;
  }
#endif

  // motor_control.stop();

// ----- VOLTAGE SECURITY CHECK ------
#ifdef VOLTAGE_SECURITY_ACTIVATED
  if (battSens.getLP1ValueUnit() < Data::MIN_VOLTAGE) {
    status = VoltageAlert;
    motor_control.stop();
  }
#endif

  // ----- MOTOR CONTROL ------
  motor_control.write_to_motor();

  // ----- DATA LOG ------
  ros_debug.sendData(
      emgOpen, emgClose, currentSens, motor_control.getMotorCommand(),
      battSens.getAvgValueUnit(), currentSens.getRawValueUnit(),
      ros_debug.getRosShutoff(), ros_debug.getRosShutoff(), status);
  // current.getRawValueUnit()
  // executionTime
  // rotor.getTemp()
  // motor_control.getDebug
  // battSens.getAvgValueUnit()
  //

  // ----- LOOP TIME MONITOR ------
  if (millis() > last_chrono_time + 10000) {
    last_chrono_time = millis();
    use_chronometer++;
    EEPROM.put(Config::USE_CHRONOMETER_ADDR, use_chronometer);
  }

  executionTime = (uint16_t)(micros() - previousTime);
  while (micros() - previousTime < Config::MICROS_PERIOD) {
  };
  previousTime = micros();
}
