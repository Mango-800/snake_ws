// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from snake_msgs:msg/Module.idl
// generated code does not contain a copyright notice

#ifndef SNAKE_MSGS__MSG__DETAIL__MODULE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define SNAKE_MSGS__MSG__DETAIL__MODULE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "snake_msgs/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "snake_msgs/msg/detail/module__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace snake_msgs
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_snake_msgs
cdr_serialize(
  const snake_msgs::msg::Module & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_snake_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  snake_msgs::msg::Module & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_snake_msgs
get_serialized_size(
  const snake_msgs::msg::Module & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_snake_msgs
max_serialized_size_Module(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace snake_msgs

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_snake_msgs
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, snake_msgs, msg, Module)();

#ifdef __cplusplus
}
#endif

#endif  // SNAKE_MSGS__MSG__DETAIL__MODULE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
