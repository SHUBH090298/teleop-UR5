// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from data_interfaces:msg/StringStamped.idl
// generated code does not contain a copyright notice

#ifndef DATA_INTERFACES__MSG__DETAIL__STRING_STAMPED__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define DATA_INTERFACES__MSG__DETAIL__STRING_STAMPED__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "data_interfaces/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "data_interfaces/msg/detail/string_stamped__struct.hpp"

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

namespace data_interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_data_interfaces
cdr_serialize(
  const data_interfaces::msg::StringStamped & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_data_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  data_interfaces::msg::StringStamped & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_data_interfaces
get_serialized_size(
  const data_interfaces::msg::StringStamped & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_data_interfaces
max_serialized_size_StringStamped(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace data_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_data_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, data_interfaces, msg, StringStamped)();

#ifdef __cplusplus
}
#endif

#endif  // DATA_INTERFACES__MSG__DETAIL__STRING_STAMPED__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
