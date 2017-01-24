include_directories(
"${CMAKE_SOURCE_DIR}/vendor/include"
"${CMAKE_SOURCE_DIR}/vendor/serial/include"
)

add_executable(navx-test navx_test.cc)
target_link_libraries(navx-test navx_frc_cpp wpi)

add_executable(serial-test serial_test.cc serial_test/listener.cc)
target_link_libraries(serial-test wpi serial)
