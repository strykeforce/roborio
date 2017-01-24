include_directories(include)

add_library(serial
src/serial.cc
src/impl/unix.cc
)

target_link_libraries(serial rt)

set_target_properties(serial PROPERTIES
  CXX_STANDARD 11
  CXX_EXTENSIONS OFF
  CXX_STANDARD_REQUIRED YES)
