cmake_minimum_required(VERSION 3.10)
project(sysmonitor)
set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)
include_directories(include ${CURSES_INCLUDE_DIR})
add_executable(sysmonitor
                src/main.cpp
                src/CpuCollector.cpp
                src/MemoryCollector.cpp
                src/TempCollector.cpp
                src/SystemMonitor.cpp
                src/Logger.cpp
                )

target_link_libraries(sysmonitor ${CURSES_LIBRARIES})