// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from snake_msgs:msg/Module.idl
// generated code does not contain a copyright notice

#ifndef SNAKE_MSGS__MSG__DETAIL__MODULE__STRUCT_H_
#define SNAKE_MSGS__MSG__DETAIL__MODULE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Module in the package snake_msgs.
typedef struct snake_msgs__msg__Module
{
  int8_t module;
  int16_t speed;
  double pitch;
  double yaw;
} snake_msgs__msg__Module;

// Struct for a sequence of snake_msgs__msg__Module.
typedef struct snake_msgs__msg__Module__Sequence
{
  snake_msgs__msg__Module * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} snake_msgs__msg__Module__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SNAKE_MSGS__MSG__DETAIL__MODULE__STRUCT_H_
