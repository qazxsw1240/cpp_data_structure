cmake_minimum_required(VERSION 3.24)
project(cpp_data_structure)

set(CMAKE_CXX_STANDARD 17)

add_executable(stack_example stack_main.cpp stack.h array_stack.cpp linked_stack.cpp)
