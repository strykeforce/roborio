cmake_minimum_required(VERSION 3.2)
project(tools)

set(WPI_LIBS /opt/wpilib CACHE PATH "WPILib directory.")

set(CMAKE_CXX_COMPILER /usr/bin/arm-frc-linux-gnueabi-g++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -fstrict-aliasing -std=c++1y")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

include_directories(
  SYSTEM
  "${WPI_LIBS}/include"
)

link_directories(
  "${WPI_LIBS}/lib"
)

add_executable(climber-test
climber_test.cc
climber_test/climber.cc
climber_test/start_climber.cc
climber_test/stop_climber.cc
climber_test/reverse_climber.cc
)
target_link_libraries(climber-test wpi)
