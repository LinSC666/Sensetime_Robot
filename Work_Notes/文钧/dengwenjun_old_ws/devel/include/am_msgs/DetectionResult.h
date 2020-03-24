// Generated by gencpp from file am_msgs/DetectionResult.msg
// DO NOT EDIT!


#ifndef AM_MSGS_MESSAGE_DETECTIONRESULT_H
#define AM_MSGS_MESSAGE_DETECTIONRESULT_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <am_msgs/Object.h>

namespace am_msgs
{
template <class ContainerAllocator>
struct DetectionResult_
{
  typedef DetectionResult_<ContainerAllocator> Type;

  DetectionResult_()
    : header()
    , objects()  {
    }
  DetectionResult_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , objects(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef std::vector< ::am_msgs::Object_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::am_msgs::Object_<ContainerAllocator> >::other >  _objects_type;
  _objects_type objects;





  typedef boost::shared_ptr< ::am_msgs::DetectionResult_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::am_msgs::DetectionResult_<ContainerAllocator> const> ConstPtr;

}; // struct DetectionResult_

typedef ::am_msgs::DetectionResult_<std::allocator<void> > DetectionResult;

typedef boost::shared_ptr< ::am_msgs::DetectionResult > DetectionResultPtr;
typedef boost::shared_ptr< ::am_msgs::DetectionResult const> DetectionResultConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::am_msgs::DetectionResult_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::am_msgs::DetectionResult_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::am_msgs::DetectionResult_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::am_msgs::DetectionResult_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::am_msgs::DetectionResult_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::am_msgs::DetectionResult_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::am_msgs::DetectionResult_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::am_msgs::DetectionResult_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::am_msgs::DetectionResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d05414622f3f3b983211d67b7ce383ac";
  }

  static const char* value(const ::am_msgs::DetectionResult_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd05414622f3f3b98ULL;
  static const uint64_t static_value2 = 0x3211d67b7ce383acULL;
};

template<class ContainerAllocator>
struct DataType< ::am_msgs::DetectionResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "am_msgs/DetectionResult";
  }

  static const char* value(const ::am_msgs::DetectionResult_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::am_msgs::DetectionResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
\n\
Object[] objects\n\
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
\n\
================================================================================\n\
MSG: am_msgs/Object\n\
int32 object_index\n\
float32 confidence # A value between 0.0 and 1.0.\n\
Rect bounding_box_cv # A bounding box on the camera coordinate.\n\
geometry_msgs/Point[] location_bv # A location on the bird-view coordinate. Z component is always 0.\n\
uint8 label\n\
uint8 LABEL_UNKNOWN=0\n\
uint8 LABEL_PEDESTRIAN=1\n\
uint8 LABEL_CONE=2\n\
uint8 LABEL_GOLF=3\n\
uint8 LABEL_SPRINKLER=4\n\
\n\
================================================================================\n\
MSG: am_msgs/Rect\n\
float32 x\n\
float32 y\n\
float32 width\n\
float32 height\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
";
  }

  static const char* value(const ::am_msgs::DetectionResult_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::am_msgs::DetectionResult_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.objects);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DetectionResult_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::am_msgs::DetectionResult_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::am_msgs::DetectionResult_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "objects[]" << std::endl;
    for (size_t i = 0; i < v.objects.size(); ++i)
    {
      s << indent << "  objects[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::am_msgs::Object_<ContainerAllocator> >::stream(s, indent + "    ", v.objects[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // AM_MSGS_MESSAGE_DETECTIONRESULT_H
