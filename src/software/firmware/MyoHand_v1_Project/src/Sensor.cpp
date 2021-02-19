#include "Sensor.h"

Sensor::Sensor(uint8_t pin, float unit_per_dgt = 1.0)
    : sensor_pin{pin}, unit_per_digit{unit_per_dgt} {
  measure = 0;
  average_value = 0;
  lp_value = 0;
}

void Sensor::setPin() { pinMode(sensor_pin, INPUT); }
void Sensor::acquire() {
  measure = analogRead(sensor_pin);
  sensor_buffer.push(measure);
}
void Sensor::initFilters() {
  for (int i = 0; i < 5; i++) {
    measure = analogRead(sensor_pin);
    sensor_buffer.push(measure);
  }
  lp_value = sensor_buffer.getIntAverage() * unit_per_digit;
}
void Sensor::avgFilter() { average_value = sensor_buffer.getIntAverage(); }
void Sensor::avgFilter(uint8_t size) {
  average_value = sensor_buffer.getIntAverage(size);
}
void Sensor::lp1Filter(float alpha) {
  // alpha = dT / (tau + dT) =~ dT / tau if tau >> dT
  lp_value = alpha * measure * unit_per_digit + (1.0 - alpha) * lp_value;
}

uint16_t Sensor::getRawValue() { return measure; }
float Sensor::getRawValueUnit() { return (measure * unit_per_digit); }
uint16_t Sensor::getAvgValue() { return average_value; }
float Sensor::getLP1ValueUnit() { return lp_value; }
float Sensor::getAvgValueUnit() { return (average_value * unit_per_digit); }
