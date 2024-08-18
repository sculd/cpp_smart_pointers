cmake_minimum_required(VERSION 3.0)

project(cpp_smart_ptrs)

add_executable(cpp_smart_ptrs main.cpp)

install(TARGETS cpp_smart_ptrs RUNTIME DESTINATION bin)
