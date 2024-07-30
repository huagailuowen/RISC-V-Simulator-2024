cmake_minimum_required(VERSION 3.11)

project(RISC-V-Simulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-O2")
# set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_CXX_FLAGS "-Wall -Wextra -g")
# set(CMAKE_CXX_FLAGS "-Wall -fsanitize=address -fsanitize=undefined -fsanitize=leak -g -O0")

include_directories(src/include)
add_subdirectory(src)
add_executable(code src/main.cpp)

target_link_libraries(code src)
