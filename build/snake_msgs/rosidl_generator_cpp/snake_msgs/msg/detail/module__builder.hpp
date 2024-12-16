// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from snake_msgs:msg/Module.idl
// generated code does not contain a copyright notice

#ifndef SNAKE_MSGS__MSG__DETAIL__MODULE__BUILDER_HPP_
#define SNAKE_MSGS__MSG__DETAIL__MODULE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "snake_msgs/msg/detail/module__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace snake_msgs
{

namespace msg
{

namespace builder
{

class Init_Module_yaw
{
public:
  explicit Init_Module_yaw(::snake_msgs::msg::Module & msg)
  : msg_(msg)
  {}
  ::snake_msgs::msg::Module yaw(::snake_msgs::msg::Module::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return std::move(msg_);
  }

private:
  ::snake_msgs::msg::Module msg_;
};

class Init_Module_pitch
{
public:
  explicit Init_Module_pitch(::snake_msgs::msg::Module & msg)
  : msg_(msg)
  {}
  Init_Module_yaw pitch(::snake_msgs::msg::Module::_pitch_type arg)
  {
    msg_.pitch = std::move(arg);
    return Init_Module_yaw(msg_);
  }

private:
  ::snake_msgs::msg::Module msg_;
};

class Init_Module_speed
{
public:
  explicit Init_Module_speed(::snake_msgs::msg::Module & msg)
  : msg_(msg)
  {}
  Init_Module_pitch speed(::snake_msgs::msg::Module::_speed_type arg)
  {
    msg_.speed = std::move(arg);
    return Init_Module_pitch(msg_);
  }

private:
  ::snake_msgs::msg::Module msg_;
};

class Init_Module_module
{
public:
  Init_Module_module()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Module_speed module(::snake_msgs::msg::Module::_module_type arg)
  {
    msg_.module = std::move(arg);
    return Init_Module_speed(msg_);
  }

private:
  ::snake_msgs::msg::Module msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::snake_msgs::msg::Module>()
{
  return snake_msgs::msg::builder::Init_Module_module();
}

}  // namespace snake_msgs

#endif  // SNAKE_MSGS__MSG__DETAIL__MODULE__BUILDER_HPP_
