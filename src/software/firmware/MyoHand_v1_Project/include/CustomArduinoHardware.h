#ifndef CUSTOMARDUINOHARDWARE_H
#define CUSTOMARDUINOHARDWARE_H

/*
 */

#include <Arduino.h>
#include <ArduinoHardware.h>
#include <ros.h>

class CustomArduinoHarware : public ArduinoHardware {
public:
  CustomArduinoHarware() : ArduinoHardware(&Serial1, 115200){};
};

#endif
