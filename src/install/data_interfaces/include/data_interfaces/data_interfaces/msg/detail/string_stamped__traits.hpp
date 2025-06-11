// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from data_interfaces:msg/StringStamped.idl
// generated code does not contain a copyright notice

#ifndef DATA_INTERFACES__MSG__DETAIL__STRING_STAMPED__TRAITS_HPP_
#define DATA_INTERFACES__MSG__DETAIL__STRING_STAMPED__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "data_interfaces/msg/detail/string_stamped__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace data_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const StringStamped & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: data
  {
    out << "data: ";
    rosidl_generator_traits::value_to_yaml(msg.data, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const StringStamped & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "data: ";
    rosidl_generator_traits::value_to_yaml(msg.data, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const StringStamped & msg, bool use_flow_style = false)
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

}  // namespace data_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use data_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const data_interfaces::msg::StringStamped & msg,
  std::ostream & out, size_t indentation = 0)
{
  data_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use data_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const data_interfaces::msg::StringStamped & msg)
{
  return data_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<data_interfaces::msg::StringStamped>()
{
  return "data_interfaces::msg::StringStamped";
}

template<>
inline const char * name<data_interfaces::msg::StringStamped>()
{
  return "data_interfaces/msg/StringStamped";
}

template<>
struct has_fixed_size<data_interfaces::msg::StringStamped>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<data_interfaces::msg::StringStamped>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<data_interfaces::msg::StringStamped>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // DATA_INTERFACES__MSG__DETAIL__STRING_STAMPED__TRAITS_HPP_
