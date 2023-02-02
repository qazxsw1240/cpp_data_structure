cmake_minimum_required(VERSION 3.24)
project(cpp_data_structure)

set(CMAKE_CXX_STANDARD 17)

add_executable(stack_example stack/main.cpp stack/stack.h stack/array_stack.cpp stack/linked_stack.cpp)
add_executable(queue_example queue/main.cpp queue/queue.h)
add_executable(list_example list/main.cpp list/list.h)
