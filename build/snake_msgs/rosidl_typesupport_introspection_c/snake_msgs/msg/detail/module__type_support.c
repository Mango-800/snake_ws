// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from snake_msgs:msg/Module.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "snake_msgs/msg/detail/module__rosidl_typesupport_introspection_c.h"
#include "snake_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "snake_msgs/msg/detail/module__functions.h"
#include "snake_msgs/msg/detail/module__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void snake_msgs__msg__Module__rosidl_typesupport_introspection_c__Module_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  snake_msgs__msg__Module__init(message_memory);
}

void snake_msgs__msg__Module__rosidl_typesupport_introspection_c__Module_fini_function(void * message_memory)
{
  snake_msgs__msg__Module__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember snake_msgs__msg__Module__rosidl_typesupport_introspection_c__Module_message_member_array[4] = {
  {
    "module",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(snake_msgs__msg__Module, module),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "speed",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(snake_msgs__msg__Module, speed),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pitch",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(snake_msgs__msg__Module, pitch),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "yaw",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(snake_msgs__msg__Module, yaw),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers snake_msgs__msg__Module__rosidl_typesupport_introspection_c__Module_message_members = {
  "snake_msgs__msg",  // message namespace
  "Module",  // message name
  4,  // number of fields
  sizeof(snake_msgs__msg__Module),
  snake_msgs__msg__Module__rosidl_typesupport_introspection_c__Module_message_member_array,  // message members
  snake_msgs__msg__Module__rosidl_typesupport_introspection_c__Module_init_function,  // function to initialize message memory (memory has to be allocated)
  snake_msgs__msg__Module__rosidl_typesupport_introspection_c__Module_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t snake_msgs__msg__Module__rosidl_typesupport_introspection_c__Module_message_type_support_handle = {
  0,
  &snake_msgs__msg__Module__rosidl_typesupport_introspection_c__Module_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_snake_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, snake_msgs, msg, Module)() {
  if (!snake_msgs__msg__Module__rosidl_typesupport_introspection_c__Module_message_type_support_handle.typesupport_identifier) {
    snake_msgs__msg__Module__rosidl_typesupport_introspection_c__Module_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &snake_msgs__msg__Module__rosidl_typesupport_introspection_c__Module_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
