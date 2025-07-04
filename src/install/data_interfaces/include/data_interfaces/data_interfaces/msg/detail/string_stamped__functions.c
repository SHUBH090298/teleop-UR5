// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from data_interfaces:msg/StringStamped.idl
// generated code does not contain a copyright notice
#include "data_interfaces/msg/detail/string_stamped__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `data`
#include "rosidl_runtime_c/string_functions.h"

bool
data_interfaces__msg__StringStamped__init(data_interfaces__msg__StringStamped * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    data_interfaces__msg__StringStamped__fini(msg);
    return false;
  }
  // data
  if (!rosidl_runtime_c__String__init(&msg->data)) {
    data_interfaces__msg__StringStamped__fini(msg);
    return false;
  }
  return true;
}

void
data_interfaces__msg__StringStamped__fini(data_interfaces__msg__StringStamped * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // data
  rosidl_runtime_c__String__fini(&msg->data);
}

bool
data_interfaces__msg__StringStamped__are_equal(const data_interfaces__msg__StringStamped * lhs, const data_interfaces__msg__StringStamped * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // data
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->data), &(rhs->data)))
  {
    return false;
  }
  return true;
}

bool
data_interfaces__msg__StringStamped__copy(
  const data_interfaces__msg__StringStamped * input,
  data_interfaces__msg__StringStamped * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // data
  if (!rosidl_runtime_c__String__copy(
      &(input->data), &(output->data)))
  {
    return false;
  }
  return true;
}

data_interfaces__msg__StringStamped *
data_interfaces__msg__StringStamped__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  data_interfaces__msg__StringStamped * msg = (data_interfaces__msg__StringStamped *)allocator.allocate(sizeof(data_interfaces__msg__StringStamped), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(data_interfaces__msg__StringStamped));
  bool success = data_interfaces__msg__StringStamped__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
data_interfaces__msg__StringStamped__destroy(data_interfaces__msg__StringStamped * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    data_interfaces__msg__StringStamped__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
data_interfaces__msg__StringStamped__Sequence__init(data_interfaces__msg__StringStamped__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  data_interfaces__msg__StringStamped * data = NULL;

  if (size) {
    data = (data_interfaces__msg__StringStamped *)allocator.zero_allocate(size, sizeof(data_interfaces__msg__StringStamped), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = data_interfaces__msg__StringStamped__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        data_interfaces__msg__StringStamped__fini(&data[i - 1]);
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
data_interfaces__msg__StringStamped__Sequence__fini(data_interfaces__msg__StringStamped__Sequence * array)
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
      data_interfaces__msg__StringStamped__fini(&array->data[i]);
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

data_interfaces__msg__StringStamped__Sequence *
data_interfaces__msg__StringStamped__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  data_interfaces__msg__StringStamped__Sequence * array = (data_interfaces__msg__StringStamped__Sequence *)allocator.allocate(sizeof(data_interfaces__msg__StringStamped__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = data_interfaces__msg__StringStamped__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
data_interfaces__msg__StringStamped__Sequence__destroy(data_interfaces__msg__StringStamped__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    data_interfaces__msg__StringStamped__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
data_interfaces__msg__StringStamped__Sequence__are_equal(const data_interfaces__msg__StringStamped__Sequence * lhs, const data_interfaces__msg__StringStamped__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!data_interfaces__msg__StringStamped__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
data_interfaces__msg__StringStamped__Sequence__copy(
  const data_interfaces__msg__StringStamped__Sequence * input,
  data_interfaces__msg__StringStamped__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(data_interfaces__msg__StringStamped);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    data_interfaces__msg__StringStamped * data =
      (data_interfaces__msg__StringStamped *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!data_interfaces__msg__StringStamped__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          data_interfaces__msg__StringStamped__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!data_interfaces__msg__StringStamped__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
