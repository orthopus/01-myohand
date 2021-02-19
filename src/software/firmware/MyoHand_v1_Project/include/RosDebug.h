#ifndef ROSDEBUG_H
#define ROSDEBUG_H

#include "CommandSignal.h"
#include "CustomArduinoHardware.h"
#include "Sensor.h"
#include "Status.h"
#include "myohand_ros_logger/msg_def.h"
#include <ros.h>
#include <std_msgs/Byte.h>
#include <std_msgs/Empty.h>

/* --- RosDebug Class Definition ---
AUTHOR : Come BUTIN
COMPANY : ORTHOPUS

This class provides all necessary functions to send
via Serial all the data needed to debug
*/

class RosDebug {
private:
  ros::NodeHandle_<CustomArduinoHarware> nh;
  myohand_ros_logger::msg_def log_message;
  std_msgs::Byte shutoff_msg;
  uint8_t ros_shutoff;
  ros::Publisher p = ros::Publisher("arduino_log", &log_message);

  ros::Subscriber<std_msgs::Byte, RosDebug> sub =
      ros::Subscriber<std_msgs::Byte, RosDebug>("/ros_shutoff",
                                                &onShutoffReceived, this);

  uint16_t debug = 0;

public:
  RosDebug();
  void init();
  void sendData(const Sensor &emgO, const Sensor &emgC, const Sensor &curSens,
                const CommandSignal &cmd, float debug_1, float debug_2,
                float debug_3, float debug_4, uint8_t status);
  void onShutoffReceived(const std_msgs::Byte &shutoff_msg);
  void update();
  uint8_t getRosShutoff() const;
  uint16_t getDebug() const;
};

#endif
