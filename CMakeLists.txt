cmake_minimum_required(VERSION 3.7)
project(CH9326LinuxTest C)

set(CMAKE_C_STANDARD 99)

link_directories(lib)
include_directories(lib)
add_executable(CH9326LinuxTest main.c lib/ch9326.h)
target_link_libraries(CH9326LinuxTest ch9326)