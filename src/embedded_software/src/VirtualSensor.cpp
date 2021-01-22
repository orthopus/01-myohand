#include "VirtualSensor.h"

VirtualSensor::VirtualSensor(const uint16_t *array, const uint16_t size,
                             const uint8_t pin, const float unit_per_dgt = 1.0)
    : Sensor(pin, unit_per_dgt), array_size{size}, measure_array{array} {}

void VirtualSensor::acquire() {
  measure = measure_array[index];
  sensor_buffer.push(measure);

  index++;
  if (index >= array_size) {
    index = 0;
  }
}
