#include <RosDebug.h>

RosDebug::RosDebug() {}

void RosDebug::init() {
  nh.getHardware()->setBaud(115200);
  nh.initNode();

  nh.advertise(p);
  // nh.subscribe(sub);
}

void RosDebug::sendData(const Sensor &emgO, const Sensor &emgC,
                        const Sensor &curSens, const CommandSignal &cmd,
                        float debug_1, float debug_2, float debug_3,
                        float debug_4, uint8_t status) {

  log_message.emgO = emgO.getRawValue();
  log_message.emgC = emgC.getRawValue();
  log_message.current = curSens.getRawValue();
  log_message.debug_data_1 = debug_1;
  log_message.debug_data_2 = debug_2;
  log_message.debug_data_3 = debug_3;
  log_message.debug_data_4 = debug_4;
  log_message.command = cmd.getCommand();
  log_message.status = status;

  p.publish(&log_message);

  nh.spinOnce();
}

void RosDebug::onShutoffReceived(const std_msgs::Byte &shutoff_msg) {
  debug += 1;
  if (shutoff_msg.data == 1) {
    ros_shutoff == 1;
  } else {
    ros_shutoff == 0;
  }
}

void RosDebug::update() {
  // nh.negotiateTopics();
  nh.subscribe(sub);
  nh.spinOnce();
}

uint8_t RosDebug::getRosShutoff() const { return ros_shutoff; }

uint16_t RosDebug::getDebug() const { return debug; }
