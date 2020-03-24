// Generated by gencpp from file am_msgs/BatteryStatus.msg
// DO NOT EDIT!


#ifndef AM_MSGS_MESSAGE_BATTERYSTATUS_H
#define AM_MSGS_MESSAGE_BATTERYSTATUS_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace am_msgs
{
template <class ContainerAllocator>
struct BatteryStatus_
{
  typedef BatteryStatus_<ContainerAllocator> Type;

  BatteryStatus_()
    : header()
    , batteryAVoltage(0.0)
    , batteryACurrent(0.0)
    , batteryBVoltage(0.0)
    , batteryBCurrent(0.0)  {
    }
  BatteryStatus_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , batteryAVoltage(0.0)
    , batteryACurrent(0.0)
    , batteryBVoltage(0.0)
    , batteryBCurrent(0.0)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef float _batteryAVoltage_type;
  _batteryAVoltage_type batteryAVoltage;

   typedef float _batteryACurrent_type;
  _batteryACurrent_type batteryACurrent;

   typedef float _batteryBVoltage_type;
  _batteryBVoltage_type batteryBVoltage;

   typedef float _batteryBCurrent_type;
  _batteryBCurrent_type batteryBCurrent;





  typedef boost::shared_ptr< ::am_msgs::BatteryStatus_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::am_msgs::BatteryStatus_<ContainerAllocator> const> ConstPtr;

}; // struct BatteryStatus_

typedef ::am_msgs::BatteryStatus_<std::allocator<void> > BatteryStatus;

typedef boost::shared_ptr< ::am_msgs::BatteryStatus > BatteryStatusPtr;
typedef boost::shared_ptr< ::am_msgs::BatteryStatus const> BatteryStatusConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::am_msgs::BatteryStatus_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::am_msgs::BatteryStatus_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace am_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'am_msgs': ['/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::am_msgs::BatteryStatus_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::am_msgs::BatteryStatus_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::am_msgs::BatteryStatus_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::am_msgs::BatteryStatus_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::am_msgs::BatteryStatus_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::am_msgs::BatteryStatus_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::am_msgs::BatteryStatus_<ContainerAllocator> >
{
  static const char* value()
  {
    return "dda2ac76d0956d48c511a33ed5f04e86";
  }

  static const char* value(const ::am_msgs::BatteryStatus_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xdda2ac76d0956d48ULL;
  static const uint64_t static_value2 = 0xc511a33ed5f04e86ULL;
};

template<class ContainerAllocator>
struct DataType< ::am_msgs::BatteryStatus_<ContainerAllocator> >
{
  static const char* value()
  {
    return "am_msgs/BatteryStatus";
  }

  static const char* value(const ::am_msgs::BatteryStatus_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::am_msgs::BatteryStatus_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
float32 batteryAVoltage\n\
float32 batteryACurrent\n\
float32 batteryBVoltage\n\
float32 batteryBCurrent\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
";
  }

  static const char* value(const ::am_msgs::BatteryStatus_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::am_msgs::BatteryStatus_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.batteryAVoltage);
      stream.next(m.batteryACurrent);
      stream.next(m.batteryBVoltage);
      stream.next(m.batteryBCurrent);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct BatteryStatus_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::am_msgs::BatteryStatus_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::am_msgs::BatteryStatus_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "batteryAVoltage: ";
    Printer<float>::stream(s, indent + "  ", v.batteryAVoltage);
    s << indent << "batteryACurrent: ";
    Printer<float>::stream(s, indent + "  ", v.batteryACurrent);
    s << indent << "batteryBVoltage: ";
    Printer<float>::stream(s, indent + "  ", v.batteryBVoltage);
    s << indent << "batteryBCurrent: ";
    Printer<float>::stream(s, indent + "  ", v.batteryBCurrent);
  }
};

} // namespace message_operations
} // namespace ros

#endif // AM_MSGS_MESSAGE_BATTERYSTATUS_H
