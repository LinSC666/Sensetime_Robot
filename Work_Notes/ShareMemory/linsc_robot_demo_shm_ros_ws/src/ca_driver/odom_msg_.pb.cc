// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: odom_msg_.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "odom_msg_.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace demo {

namespace {

const ::google::protobuf::Descriptor* odometry_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  odometry_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_odom_5fmsg_5f_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_odom_5fmsg_5f_2eproto() {
  protobuf_AddDesc_odom_5fmsg_5f_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "odom_msg_.proto");
  GOOGLE_CHECK(file != NULL);
  odometry_descriptor_ = file->message_type(0);
  static const int odometry_offsets_[6] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(odometry, pose_pose_position_x_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(odometry, pose_pose_position_y_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(odometry, pose_pose_orientation_x_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(odometry, pose_pose_orientation_y_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(odometry, pose_pose_orientation_z_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(odometry, pose_pose_orientation_w_),
  };
  odometry_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      odometry_descriptor_,
      odometry::default_instance_,
      odometry_offsets_,
      -1,
      -1,
      -1,
      sizeof(odometry),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(odometry, _internal_metadata_),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(odometry, _is_default_instance_));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_odom_5fmsg_5f_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      odometry_descriptor_, &odometry::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_odom_5fmsg_5f_2eproto() {
  delete odometry::default_instance_;
  delete odometry_reflection_;
}

void protobuf_AddDesc_odom_5fmsg_5f_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AddDesc_odom_5fmsg_5f_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\017odom_msg_.proto\022\004demo\"\312\001\n\010odometry\022\034\n\024"
    "pose_pose_position_x\030\001 \001(\001\022\034\n\024pose_pose_"
    "position_y\030\002 \001(\001\022\037\n\027pose_pose_orientatio"
    "n_x\030\003 \001(\001\022\037\n\027pose_pose_orientation_y\030\004 \001"
    "(\001\022\037\n\027pose_pose_orientation_z\030\005 \001(\001\022\037\n\027p"
    "ose_pose_orientation_w\030\006 \001(\001b\006proto3", 236);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "odom_msg_.proto", &protobuf_RegisterTypes);
  odometry::default_instance_ = new odometry();
  odometry::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_odom_5fmsg_5f_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_odom_5fmsg_5f_2eproto {
  StaticDescriptorInitializer_odom_5fmsg_5f_2eproto() {
    protobuf_AddDesc_odom_5fmsg_5f_2eproto();
  }
} static_descriptor_initializer_odom_5fmsg_5f_2eproto_;

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int odometry::kPosePosePositionXFieldNumber;
const int odometry::kPosePosePositionYFieldNumber;
const int odometry::kPosePoseOrientationXFieldNumber;
const int odometry::kPosePoseOrientationYFieldNumber;
const int odometry::kPosePoseOrientationZFieldNumber;
const int odometry::kPosePoseOrientationWFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

odometry::odometry()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:demo.odometry)
}

void odometry::InitAsDefaultInstance() {
  _is_default_instance_ = true;
}

odometry::odometry(const odometry& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:demo.odometry)
}

void odometry::SharedCtor() {
    _is_default_instance_ = false;
  _cached_size_ = 0;
  pose_pose_position_x_ = 0;
  pose_pose_position_y_ = 0;
  pose_pose_orientation_x_ = 0;
  pose_pose_orientation_y_ = 0;
  pose_pose_orientation_z_ = 0;
  pose_pose_orientation_w_ = 0;
}

odometry::~odometry() {
  // @@protoc_insertion_point(destructor:demo.odometry)
  SharedDtor();
}

void odometry::SharedDtor() {
  if (this != default_instance_) {
  }
}

void odometry::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* odometry::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return odometry_descriptor_;
}

const odometry& odometry::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_odom_5fmsg_5f_2eproto();
  return *default_instance_;
}

odometry* odometry::default_instance_ = NULL;

odometry* odometry::New(::google::protobuf::Arena* arena) const {
  odometry* n = new odometry;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void odometry::Clear() {
// @@protoc_insertion_point(message_clear_start:demo.odometry)
#if defined(__clang__)
#define ZR_HELPER_(f) \
  _Pragma("clang diagnostic push") \
  _Pragma("clang diagnostic ignored \"-Winvalid-offsetof\"") \
  __builtin_offsetof(odometry, f) \
  _Pragma("clang diagnostic pop")
#else
#define ZR_HELPER_(f) reinterpret_cast<char*>(\
  &reinterpret_cast<odometry*>(16)->f)
#endif

#define ZR_(first, last) do {\
  ::memset(&first, 0,\
           ZR_HELPER_(last) - ZR_HELPER_(first) + sizeof(last));\
} while (0)

  ZR_(pose_pose_position_x_, pose_pose_orientation_w_);

#undef ZR_HELPER_
#undef ZR_

}

bool odometry::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:demo.odometry)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional double pose_pose_position_x = 1;
      case 1: {
        if (tag == 9) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &pose_pose_position_x_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(17)) goto parse_pose_pose_position_y;
        break;
      }

      // optional double pose_pose_position_y = 2;
      case 2: {
        if (tag == 17) {
         parse_pose_pose_position_y:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &pose_pose_position_y_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(25)) goto parse_pose_pose_orientation_x;
        break;
      }

      // optional double pose_pose_orientation_x = 3;
      case 3: {
        if (tag == 25) {
         parse_pose_pose_orientation_x:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &pose_pose_orientation_x_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(33)) goto parse_pose_pose_orientation_y;
        break;
      }

      // optional double pose_pose_orientation_y = 4;
      case 4: {
        if (tag == 33) {
         parse_pose_pose_orientation_y:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &pose_pose_orientation_y_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(41)) goto parse_pose_pose_orientation_z;
        break;
      }

      // optional double pose_pose_orientation_z = 5;
      case 5: {
        if (tag == 41) {
         parse_pose_pose_orientation_z:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &pose_pose_orientation_z_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(49)) goto parse_pose_pose_orientation_w;
        break;
      }

      // optional double pose_pose_orientation_w = 6;
      case 6: {
        if (tag == 49) {
         parse_pose_pose_orientation_w:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &pose_pose_orientation_w_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:demo.odometry)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:demo.odometry)
  return false;
#undef DO_
}

void odometry::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:demo.odometry)
  // optional double pose_pose_position_x = 1;
  if (this->pose_pose_position_x() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(1, this->pose_pose_position_x(), output);
  }

  // optional double pose_pose_position_y = 2;
  if (this->pose_pose_position_y() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(2, this->pose_pose_position_y(), output);
  }

  // optional double pose_pose_orientation_x = 3;
  if (this->pose_pose_orientation_x() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(3, this->pose_pose_orientation_x(), output);
  }

  // optional double pose_pose_orientation_y = 4;
  if (this->pose_pose_orientation_y() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(4, this->pose_pose_orientation_y(), output);
  }

  // optional double pose_pose_orientation_z = 5;
  if (this->pose_pose_orientation_z() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(5, this->pose_pose_orientation_z(), output);
  }

  // optional double pose_pose_orientation_w = 6;
  if (this->pose_pose_orientation_w() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(6, this->pose_pose_orientation_w(), output);
  }

  // @@protoc_insertion_point(serialize_end:demo.odometry)
}

::google::protobuf::uint8* odometry::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:demo.odometry)
  // optional double pose_pose_position_x = 1;
  if (this->pose_pose_position_x() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(1, this->pose_pose_position_x(), target);
  }

  // optional double pose_pose_position_y = 2;
  if (this->pose_pose_position_y() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(2, this->pose_pose_position_y(), target);
  }

  // optional double pose_pose_orientation_x = 3;
  if (this->pose_pose_orientation_x() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(3, this->pose_pose_orientation_x(), target);
  }

  // optional double pose_pose_orientation_y = 4;
  if (this->pose_pose_orientation_y() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(4, this->pose_pose_orientation_y(), target);
  }

  // optional double pose_pose_orientation_z = 5;
  if (this->pose_pose_orientation_z() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(5, this->pose_pose_orientation_z(), target);
  }

  // optional double pose_pose_orientation_w = 6;
  if (this->pose_pose_orientation_w() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(6, this->pose_pose_orientation_w(), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:demo.odometry)
  return target;
}

int odometry::ByteSize() const {
// @@protoc_insertion_point(message_byte_size_start:demo.odometry)
  int total_size = 0;

  // optional double pose_pose_position_x = 1;
  if (this->pose_pose_position_x() != 0) {
    total_size += 1 + 8;
  }

  // optional double pose_pose_position_y = 2;
  if (this->pose_pose_position_y() != 0) {
    total_size += 1 + 8;
  }

  // optional double pose_pose_orientation_x = 3;
  if (this->pose_pose_orientation_x() != 0) {
    total_size += 1 + 8;
  }

  // optional double pose_pose_orientation_y = 4;
  if (this->pose_pose_orientation_y() != 0) {
    total_size += 1 + 8;
  }

  // optional double pose_pose_orientation_z = 5;
  if (this->pose_pose_orientation_z() != 0) {
    total_size += 1 + 8;
  }

  // optional double pose_pose_orientation_w = 6;
  if (this->pose_pose_orientation_w() != 0) {
    total_size += 1 + 8;
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void odometry::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:demo.odometry)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  const odometry* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const odometry>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:demo.odometry)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:demo.odometry)
    MergeFrom(*source);
  }
}

void odometry::MergeFrom(const odometry& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:demo.odometry)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  if (from.pose_pose_position_x() != 0) {
    set_pose_pose_position_x(from.pose_pose_position_x());
  }
  if (from.pose_pose_position_y() != 0) {
    set_pose_pose_position_y(from.pose_pose_position_y());
  }
  if (from.pose_pose_orientation_x() != 0) {
    set_pose_pose_orientation_x(from.pose_pose_orientation_x());
  }
  if (from.pose_pose_orientation_y() != 0) {
    set_pose_pose_orientation_y(from.pose_pose_orientation_y());
  }
  if (from.pose_pose_orientation_z() != 0) {
    set_pose_pose_orientation_z(from.pose_pose_orientation_z());
  }
  if (from.pose_pose_orientation_w() != 0) {
    set_pose_pose_orientation_w(from.pose_pose_orientation_w());
  }
}

void odometry::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:demo.odometry)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void odometry::CopyFrom(const odometry& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:demo.odometry)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool odometry::IsInitialized() const {

  return true;
}

void odometry::Swap(odometry* other) {
  if (other == this) return;
  InternalSwap(other);
}
void odometry::InternalSwap(odometry* other) {
  std::swap(pose_pose_position_x_, other->pose_pose_position_x_);
  std::swap(pose_pose_position_y_, other->pose_pose_position_y_);
  std::swap(pose_pose_orientation_x_, other->pose_pose_orientation_x_);
  std::swap(pose_pose_orientation_y_, other->pose_pose_orientation_y_);
  std::swap(pose_pose_orientation_z_, other->pose_pose_orientation_z_);
  std::swap(pose_pose_orientation_w_, other->pose_pose_orientation_w_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata odometry::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = odometry_descriptor_;
  metadata.reflection = odometry_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// odometry

// optional double pose_pose_position_x = 1;
void odometry::clear_pose_pose_position_x() {
  pose_pose_position_x_ = 0;
}
 double odometry::pose_pose_position_x() const {
  // @@protoc_insertion_point(field_get:demo.odometry.pose_pose_position_x)
  return pose_pose_position_x_;
}
 void odometry::set_pose_pose_position_x(double value) {
  
  pose_pose_position_x_ = value;
  // @@protoc_insertion_point(field_set:demo.odometry.pose_pose_position_x)
}

// optional double pose_pose_position_y = 2;
void odometry::clear_pose_pose_position_y() {
  pose_pose_position_y_ = 0;
}
 double odometry::pose_pose_position_y() const {
  // @@protoc_insertion_point(field_get:demo.odometry.pose_pose_position_y)
  return pose_pose_position_y_;
}
 void odometry::set_pose_pose_position_y(double value) {
  
  pose_pose_position_y_ = value;
  // @@protoc_insertion_point(field_set:demo.odometry.pose_pose_position_y)
}

// optional double pose_pose_orientation_x = 3;
void odometry::clear_pose_pose_orientation_x() {
  pose_pose_orientation_x_ = 0;
}
 double odometry::pose_pose_orientation_x() const {
  // @@protoc_insertion_point(field_get:demo.odometry.pose_pose_orientation_x)
  return pose_pose_orientation_x_;
}
 void odometry::set_pose_pose_orientation_x(double value) {
  
  pose_pose_orientation_x_ = value;
  // @@protoc_insertion_point(field_set:demo.odometry.pose_pose_orientation_x)
}

// optional double pose_pose_orientation_y = 4;
void odometry::clear_pose_pose_orientation_y() {
  pose_pose_orientation_y_ = 0;
}
 double odometry::pose_pose_orientation_y() const {
  // @@protoc_insertion_point(field_get:demo.odometry.pose_pose_orientation_y)
  return pose_pose_orientation_y_;
}
 void odometry::set_pose_pose_orientation_y(double value) {
  
  pose_pose_orientation_y_ = value;
  // @@protoc_insertion_point(field_set:demo.odometry.pose_pose_orientation_y)
}

// optional double pose_pose_orientation_z = 5;
void odometry::clear_pose_pose_orientation_z() {
  pose_pose_orientation_z_ = 0;
}
 double odometry::pose_pose_orientation_z() const {
  // @@protoc_insertion_point(field_get:demo.odometry.pose_pose_orientation_z)
  return pose_pose_orientation_z_;
}
 void odometry::set_pose_pose_orientation_z(double value) {
  
  pose_pose_orientation_z_ = value;
  // @@protoc_insertion_point(field_set:demo.odometry.pose_pose_orientation_z)
}

// optional double pose_pose_orientation_w = 6;
void odometry::clear_pose_pose_orientation_w() {
  pose_pose_orientation_w_ = 0;
}
 double odometry::pose_pose_orientation_w() const {
  // @@protoc_insertion_point(field_get:demo.odometry.pose_pose_orientation_w)
  return pose_pose_orientation_w_;
}
 void odometry::set_pose_pose_orientation_w(double value) {
  
  pose_pose_orientation_w_ = value;
  // @@protoc_insertion_point(field_set:demo.odometry.pose_pose_orientation_w)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace demo

// @@protoc_insertion_point(global_scope)