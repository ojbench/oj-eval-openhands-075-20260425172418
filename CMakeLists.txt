cmake_minimum_required(VERSION 3.10)
project(str_class)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create an executable that includes str.hpp
# Since this is a header-only implementation, we need a main file
# The OJ will provide the main file, so we just need to ensure str.hpp compiles

# Create a dummy main for testing purposes
add_executable(code test_main.cpp)

# Set the output name to "code" as required by OJ
set_target_properties(code PROPERTIES OUTPUT_NAME "code")
