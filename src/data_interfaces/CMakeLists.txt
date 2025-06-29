cmake_minimum_required(VERSION 3.8)
project(data_interfaces)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# Generate message interfaces
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/StringStamped.msg"
  DEPENDENCIES std_msgs
)

# Export runtime dependency (required to use the message in other packages)
ament_export_dependencies(rosidl_default_runtime)

# Important: ament_package() must come AFTER rosidl_generate_interfaces
ament_package()
