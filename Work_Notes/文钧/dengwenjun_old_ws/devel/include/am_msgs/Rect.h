// Generated by gencpp from file am_msgs/Rect.msg
// DO NOT EDIT!


#ifndef AM_MSGS_MESSAGE_RECT_H
#define AM_MSGS_MESSAGE_RECT_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace am_msgs
{
template <class ContainerAllocator>
struct Rect_
{
  typedef Rect_<ContainerAllocator> Type;

  Rect_()
    : x(0.0)
    , y(0.0)
    , width(0.0)
    , height(0.0)  {
    }
  Rect_(const ContainerAllocator& _alloc)
    : x(0.0)
    , y(0.0)
    , width(0.0)
    , height(0.0)  {
  (void)_alloc;
    }



   typedef float _x_type;
  _x_type x;

   typedef float _y_type;
  _y_type y;

   typedef float _width_type;
  _width_type width;

   typedef float _height_type;
  _height_type height;





  typedef boost::shared_ptr< ::am_msgs::Rect_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::am_msgs::Rect_<ContainerAllocator> const> ConstPtr;

}; // struct Rect_

typedef ::am_msgs::Rect_<std::allocator<void> > Rect;

typedef boost::shared_ptr< ::am_msgs::Rect > RectPtr;
typedef boost::shared_ptr< ::am_msgs::Rect const> RectConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::am_msgs::Rect_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::am_msgs::Rect_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace am_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'am_msgs': ['/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::am_msgs::Rect_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::am_msgs::Rect_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::am_msgs::Rect_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::am_msgs::Rect_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::am_msgs::Rect_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::am_msgs::Rect_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::am_msgs::Rect_<ContainerAllocator> >
{
  static const char* value()
  {
    return "a91ecea8870c8dcc4ddb26473f3471a8";
  }

  static const char* value(const ::am_msgs::Rect_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xa91ecea8870c8dccULL;
  static const uint64_t static_value2 = 0x4ddb26473f3471a8ULL;
};

template<class ContainerAllocator>
struct DataType< ::am_msgs::Rect_<ContainerAllocator> >
{
  static const char* value()
  {
    return "am_msgs/Rect";
  }

  static const char* value(const ::am_msgs::Rect_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::am_msgs::Rect_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float32 x\n\
float32 y\n\
float32 width\n\
float32 height\n\
";
  }

  static const char* value(const ::am_msgs::Rect_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::am_msgs::Rect_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.x);
      stream.next(m.y);
      stream.next(m.width);
      stream.next(m.height);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Rect_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::am_msgs::Rect_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::am_msgs::Rect_<ContainerAllocator>& v)
  {
    s << indent << "x: ";
    Printer<float>::stream(s, indent + "  ", v.x);
    s << indent << "y: ";
    Printer<float>::stream(s, indent + "  ", v.y);
    s << indent << "width: ";
    Printer<float>::stream(s, indent + "  ", v.width);
    s << indent << "height: ";
    Printer<float>::stream(s, indent + "  ", v.height);
  }
};

} // namespace message_operations
} // namespace ros

#endif // AM_MSGS_MESSAGE_RECT_H
