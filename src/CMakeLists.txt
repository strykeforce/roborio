include_directories(
"${CMAKE_SOURCE_DIR}/vendor/include"
"${CMAKE_SOURCE_DIR}/vendor/serial/include"
"${CMAKE_SOURCE_DIR}/vendor/link"
)

add_executable(dio-test dio_test.cc)
target_link_libraries(dio-test wpi)

add_executable(pwm-test dio_test.cc)
target_link_libraries(pwm-test wpi)

add_executable(navx-test navx_test.cc)
target_link_libraries(navx-test navx_frc_cpp wpi)

add_executable(servo-test servo_test.cc)
target_link_libraries(servo-test wpi)

add_executable(serial-test
serial_test.cc
serial_test/listener.cc
"${CMAKE_SOURCE_DIR}/vendor/link/checksum.cc"
"${CMAKE_SOURCE_DIR}/vendor/link/parser.cc"
"${CMAKE_SOURCE_DIR}/vendor/link/sentence.cc"
)
target_link_libraries(serial-test wpi serial)
