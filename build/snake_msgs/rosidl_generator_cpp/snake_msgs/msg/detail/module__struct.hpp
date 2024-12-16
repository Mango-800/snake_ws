// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from snake_msgs:msg/Module.idl
// generated code does not contain a copyright notice

#ifndef SNAKE_MSGS__MSG__DETAIL__MODULE__STRUCT_HPP_
#define SNAKE_MSGS__MSG__DETAIL__MODULE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__snake_msgs__msg__Module __attribute__((deprecated))
#else
# define DEPRECATED__snake_msgs__msg__Module __declspec(deprecated)
#endif

namespace snake_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Module_
{
  using Type = Module_<ContainerAllocator>;

  explicit Module_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->module = 0;
      this->speed = 0;
      this->pitch = 0.0;
      this->yaw = 0.0;
    }
  }

  explicit Module_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->module = 0;
      this->speed = 0;
      this->pitch = 0.0;
      this->yaw = 0.0;
    }
  }

  // field types and members
  using _module_type =
    int8_t;
  _module_type module;
  using _speed_type =
    int16_t;
  _speed_type speed;
  using _pitch_type =
    double;
  _pitch_type pitch;
  using _yaw_type =
    double;
  _yaw_type yaw;

  // setters for named parameter idiom
  Type & set__module(
    const int8_t & _arg)
  {
    this->module = _arg;
    return *this;
  }
  Type & set__speed(
    const int16_t & _arg)
  {
    this->speed = _arg;
    return *this;
  }
  Type & set__pitch(
    const double & _arg)
  {
    this->pitch = _arg;
    return *this;
  }
  Type & set__yaw(
    const double & _arg)
  {
    this->yaw = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    snake_msgs::msg::Module_<ContainerAllocator> *;
  using ConstRawPtr =
    const snake_msgs::msg::Module_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<snake_msgs::msg::Module_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<snake_msgs::msg::Module_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      snake_msgs::msg::Module_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<snake_msgs::msg::Module_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      snake_msgs::msg::Module_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<snake_msgs::msg::Module_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<snake_msgs::msg::Module_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<snake_msgs::msg::Module_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__snake_msgs__msg__Module
    std::shared_ptr<snake_msgs::msg::Module_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__snake_msgs__msg__Module
    std::shared_ptr<snake_msgs::msg::Module_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Module_ & other) const
  {
    if (this->module != other.module) {
      return false;
    }
    if (this->speed != other.speed) {
      return false;
    }
    if (this->pitch != other.pitch) {
      return false;
    }
    if (this->yaw != other.yaw) {
      return false;
    }
    return true;
  }
  bool operator!=(const Module_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Module_

// alias to use template instance with default allocator
using Module =
  snake_msgs::msg::Module_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace snake_msgs

#endif  // SNAKE_MSGS__MSG__DETAIL__MODULE__STRUCT_HPP_
