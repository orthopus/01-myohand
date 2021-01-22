#ifndef ROSDEBUG_H
#define ROSDEBUG_H

#include <ros.h>
#include "serial_logger/msg_def.h"
#include "Sensor.h"
#include "CommandSignal.h"
#include "Status.h"

/* --- RosDebug Class Definition ---
AUTHOR : Come BUTIN
COMPANY : ORTHOPUS

This class provides all necessary functions to send
via Serial all the data needed to debug
*/

class RosDebug
{
private:
  ros::NodeHandle nh;
  serial_logger::msg_def log_message;
  ros::Publisher p = ros::Publisher("arduino_log", &log_message);

public:
  RosDebug();
  void init();
  void sendData(const Sensor &emgO, const Sensor &emgC,
                const Sensor &curSens, const CommandSignal &cmd,
                float debug_1, float debug_2,
                float debug_3, float debug_4,
                uint8_t status);
};

#endif
