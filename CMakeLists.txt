cmake_minimum_required(VERSION 3.10)
project(SysMon-cpp)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(SysMon-cpp ${SOURCES})

enable_testing()
add_executable(testCpu tests/test_CpuMonitor.cpp src/CpuMonitor.cpp)
