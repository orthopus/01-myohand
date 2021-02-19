#ifndef _ROS_serial_logger_msg_def_h
#define _ROS_serial_logger_msg_def_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace serial_logger
{

  class msg_def : public ros::Msg
  {
    public:
      typedef uint16_t _emgO_type;
      _emgO_type emgO;
      typedef uint16_t _emgC_type;
      _emgC_type emgC;
      typedef uint16_t _current_type;
      _current_type current;
      typedef float _debug_data_1_type;
      _debug_data_1_type debug_data_1;
      typedef float _debug_data_2_type;
      _debug_data_2_type debug_data_2;
      typedef float _debug_data_3_type;
      _debug_data_3_type debug_data_3;
      typedef float _debug_data_4_type;
      _debug_data_4_type debug_data_4;
      typedef uint16_t _command_type;
      _command_type command;
      typedef uint8_t _status_type;
      _status_type status;

    msg_def():
      emgO(0),
      emgC(0),
      current(0),
      debug_data_1(0),
      debug_data_2(0),
      debug_data_3(0),
      debug_data_4(0),
      command(0),
      status(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->emgO >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->emgO >> (8 * 1)) & 0xFF;
      offset += sizeof(this->emgO);
      *(outbuffer + offset + 0) = (this->emgC >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->emgC >> (8 * 1)) & 0xFF;
      offset += sizeof(this->emgC);
      *(outbuffer + offset + 0) = (this->current >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->current >> (8 * 1)) & 0xFF;
      offset += sizeof(this->current);
      union {
        float real;
        uint32_t base;
      } u_debug_data_1;
      u_debug_data_1.real = this->debug_data_1;
      *(outbuffer + offset + 0) = (u_debug_data_1.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_debug_data_1.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_debug_data_1.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_debug_data_1.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->debug_data_1);
      union {
        float real;
        uint32_t base;
      } u_debug_data_2;
      u_debug_data_2.real = this->debug_data_2;
      *(outbuffer + offset + 0) = (u_debug_data_2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_debug_data_2.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_debug_data_2.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_debug_data_2.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->debug_data_2);
      union {
        float real;
        uint32_t base;
      } u_debug_data_3;
      u_debug_data_3.real = this->debug_data_3;
      *(outbuffer + offset + 0) = (u_debug_data_3.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_debug_data_3.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_debug_data_3.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_debug_data_3.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->debug_data_3);
      union {
        float real;
        uint32_t base;
      } u_debug_data_4;
      u_debug_data_4.real = this->debug_data_4;
      *(outbuffer + offset + 0) = (u_debug_data_4.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_debug_data_4.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_debug_data_4.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_debug_data_4.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->debug_data_4);
      *(outbuffer + offset + 0) = (this->command >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->command >> (8 * 1)) & 0xFF;
      offset += sizeof(this->command);
      *(outbuffer + offset + 0) = (this->status >> (8 * 0)) & 0xFF;
      offset += sizeof(this->status);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->emgO =  ((uint16_t) (*(inbuffer + offset)));
      this->emgO |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->emgO);
      this->emgC =  ((uint16_t) (*(inbuffer + offset)));
      this->emgC |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->emgC);
      this->current =  ((uint16_t) (*(inbuffer + offset)));
      this->current |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->current);
      union {
        float real;
        uint32_t base;
      } u_debug_data_1;
      u_debug_data_1.base = 0;
      u_debug_data_1.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_debug_data_1.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_debug_data_1.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_debug_data_1.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->debug_data_1 = u_debug_data_1.real;
      offset += sizeof(this->debug_data_1);
      union {
        float real;
        uint32_t base;
      } u_debug_data_2;
      u_debug_data_2.base = 0;
      u_debug_data_2.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_debug_data_2.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_debug_data_2.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_debug_data_2.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->debug_data_2 = u_debug_data_2.real;
      offset += sizeof(this->debug_data_2);
      union {
        float real;
        uint32_t base;
      } u_debug_data_3;
      u_debug_data_3.base = 0;
      u_debug_data_3.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_debug_data_3.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_debug_data_3.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_debug_data_3.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->debug_data_3 = u_debug_data_3.real;
      offset += sizeof(this->debug_data_3);
      union {
        float real;
        uint32_t base;
      } u_debug_data_4;
      u_debug_data_4.base = 0;
      u_debug_data_4.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_debug_data_4.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_debug_data_4.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_debug_data_4.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->debug_data_4 = u_debug_data_4.real;
      offset += sizeof(this->debug_data_4);
      this->command =  ((uint16_t) (*(inbuffer + offset)));
      this->command |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->command);
      this->status =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->status);
     return offset;
    }

    const char * getType(){ return "serial_logger/msg_def"; };
    const char * getMD5(){ return "8a60facf2b9d21412b18d2030b3eeac4"; };

  };

}
#endif
