// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from snake_msgs:msg/Module.idl
// generated code does not contain a copyright notice
#include "snake_msgs/msg/detail/module__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
snake_msgs__msg__Module__init(snake_msgs__msg__Module * msg)
{
  if (!msg) {
    return false;
  }
  // module
  // speed
  // pitch
  // yaw
  return true;
}

void
snake_msgs__msg__Module__fini(snake_msgs__msg__Module * msg)
{
  if (!msg) {
    return;
  }
  // module
  // speed
  // pitch
  // yaw
}

bool
snake_msgs__msg__Module__are_equal(const snake_msgs__msg__Module * lhs, const snake_msgs__msg__Module * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // module
  if (lhs->module != rhs->module) {
    return false;
  }
  // speed
  if (lhs->speed != rhs->speed) {
    return false;
  }
  // pitch
  if (lhs->pitch != rhs->pitch) {
    return false;
  }
  // yaw
  if (lhs->yaw != rhs->yaw) {
    return false;
  }
  return true;
}

bool
snake_msgs__msg__Module__copy(
  const snake_msgs__msg__Module * input,
  snake_msgs__msg__Module * output)
{
  if (!input || !output) {
    return false;
  }
  // module
  output->module = input->module;
  // speed
  output->speed = input->speed;
  // pitch
  output->pitch = input->pitch;
  // yaw
  output->yaw = input->yaw;
  return true;
}

snake_msgs__msg__Module *
snake_msgs__msg__Module__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  snake_msgs__msg__Module * msg = (snake_msgs__msg__Module *)allocator.allocate(sizeof(snake_msgs__msg__Module), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(snake_msgs__msg__Module));
  bool success = snake_msgs__msg__Module__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
snake_msgs__msg__Module__destroy(snake_msgs__msg__Module * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    snake_msgs__msg__Module__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
snake_msgs__msg__Module__Sequence__init(snake_msgs__msg__Module__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  snake_msgs__msg__Module * data = NULL;

  if (size) {
    data = (snake_msgs__msg__Module *)allocator.zero_allocate(size, sizeof(snake_msgs__msg__Module), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = snake_msgs__msg__Module__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        snake_msgs__msg__Module__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
snake_msgs__msg__Module__Sequence__fini(snake_msgs__msg__Module__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      snake_msgs__msg__Module__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

snake_msgs__msg__Module__Sequence *
snake_msgs__msg__Module__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  snake_msgs__msg__Module__Sequence * array = (snake_msgs__msg__Module__Sequence *)allocator.allocate(sizeof(snake_msgs__msg__Module__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = snake_msgs__msg__Module__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
snake_msgs__msg__Module__Sequence__destroy(snake_msgs__msg__Module__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    snake_msgs__msg__Module__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
snake_msgs__msg__Module__Sequence__are_equal(const snake_msgs__msg__Module__Sequence * lhs, const snake_msgs__msg__Module__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!snake_msgs__msg__Module__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
snake_msgs__msg__Module__Sequence__copy(
  const snake_msgs__msg__Module__Sequence * input,
  snake_msgs__msg__Module__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(snake_msgs__msg__Module);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    snake_msgs__msg__Module * data =
      (snake_msgs__msg__Module *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!snake_msgs__msg__Module__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          snake_msgs__msg__Module__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!snake_msgs__msg__Module__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
