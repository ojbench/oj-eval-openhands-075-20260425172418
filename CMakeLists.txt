cmake_minimum_required(VERSION 3.10)
project(str_class)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The OJ will provide the main file, we just need to make sure str.hpp is available
# For local testing, we can create a test main if it exists
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test_main.cpp")
    add_executable(code test_main.cpp)
else()
    # Create a minimal main for compilation testing
    add_executable(code main.cpp)
endif()

# Set the output name to "code" as required by OJ
set_target_properties(code PROPERTIES OUTPUT_NAME "code")
