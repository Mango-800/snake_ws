// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from snake_msgs:msg/Module.idl
// generated code does not contain a copyright notice

#ifndef SNAKE_MSGS__MSG__DETAIL__MODULE__TRAITS_HPP_
#define SNAKE_MSGS__MSG__DETAIL__MODULE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "snake_msgs/msg/detail/module__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace snake_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Module & msg,
  std::ostream & out)
{
  out << "{";
  // member: module
  {
    out << "module: ";
    rosidl_generator_traits::value_to_yaml(msg.module, out);
    out << ", ";
  }

  // member: speed
  {
    out << "speed: ";
    rosidl_generator_traits::value_to_yaml(msg.speed, out);
    out << ", ";
  }

  // member: pitch
  {
    out << "pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.pitch, out);
    out << ", ";
  }

  // member: yaw
  {
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Module & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: module
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "module: ";
    rosidl_generator_traits::value_to_yaml(msg.module, out);
    out << "\n";
  }

  // member: speed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "speed: ";
    rosidl_generator_traits::value_to_yaml(msg.speed, out);
    out << "\n";
  }

  // member: pitch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.pitch, out);
    out << "\n";
  }

  // member: yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Module & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace snake_msgs

namespace rosidl_generator_traits
{

[[deprecated("use snake_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const snake_msgs::msg::Module & msg,
  std::ostream & out, size_t indentation = 0)
{
  snake_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use snake_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const snake_msgs::msg::Module & msg)
{
  return snake_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<snake_msgs::msg::Module>()
{
  return "snake_msgs::msg::Module";
}

template<>
inline const char * name<snake_msgs::msg::Module>()
{
  return "snake_msgs/msg/Module";
}

template<>
struct has_fixed_size<snake_msgs::msg::Module>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<snake_msgs::msg::Module>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<snake_msgs::msg::Module>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SNAKE_MSGS__MSG__DETAIL__MODULE__TRAITS_HPP_
