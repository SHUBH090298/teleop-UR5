// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from data_interfaces:msg/StringStamped.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "data_interfaces/msg/detail/string_stamped__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace data_interfaces
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void StringStamped_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) data_interfaces::msg::StringStamped(_init);
}

void StringStamped_fini_function(void * message_memory)
{
  auto typed_message = static_cast<data_interfaces::msg::StringStamped *>(message_memory);
  typed_message->~StringStamped();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember StringStamped_message_member_array[2] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(data_interfaces::msg::StringStamped, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "data",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(data_interfaces::msg::StringStamped, data),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers StringStamped_message_members = {
  "data_interfaces::msg",  // message namespace
  "StringStamped",  // message name
  2,  // number of fields
  sizeof(data_interfaces::msg::StringStamped),
  StringStamped_message_member_array,  // message members
  StringStamped_init_function,  // function to initialize message memory (memory has to be allocated)
  StringStamped_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t StringStamped_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &StringStamped_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace data_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<data_interfaces::msg::StringStamped>()
{
  return &::data_interfaces::msg::rosidl_typesupport_introspection_cpp::StringStamped_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, data_interfaces, msg, StringStamped)() {
  return &::data_interfaces::msg::rosidl_typesupport_introspection_cpp::StringStamped_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
