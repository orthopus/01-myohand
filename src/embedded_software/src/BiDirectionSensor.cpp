#include "BiDirectionSensor.h"

BiDirectionSensor::BiDirectionSensor(const bool dir, const uint16_t mid_val,
                                     const uint8_t pin,
                                     const uint8_t inactive_pin,
                                     const float unit_per_dgt = 1.0)
    : Sensor(pin, unit_per_dgt), direction{dir}, middle_value{mid_val},
      inactive_pin{inactive_pin} {}

void BiDirectionSensor::setPin() {
  pinMode(sensor_pin, INPUT);
  // Set the inactive pin to the ground, so the connector (5V, EMG_O, EMG_C) is
  // transformed into (5V, GND, EMG_C) to connect to the potentiometer
  pinMode(inactive_pin, OUTPUT);
  digitalWrite(inactive_pin, HIGH);
}

void BiDirectionSensor::acquire() {
  uint16_t raw_measure = analogRead(sensor_pin);

  if (direction && raw_measure >= 520) {
    measure = (raw_measure - 520) * 2.5;
  } else if (!direction && raw_measure < 505) {
    measure = (505 - raw_measure) * 2.5;
  } else {
    measure = 0;
  }
  if (measure > 1023) {
    measure = 1023;
  }

  sensor_buffer.push(measure);
}
