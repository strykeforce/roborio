#include <chrono>
#include <thread>

#include "WPILib.h"
#include "spdlog/spdlog.h"

#include "serial_test/listener.h"

/*
 * This program is used to test serial connections.
 * It listens on the specified port and speed for strings of the format:
 * "integer,integer\n"
 * LOOP_SLEEP_MS = run loop wait period
 */

static constexpr auto LOOP_SLEEP_MS = std::chrono::milliseconds(20);

class Robot : public SampleRobot {
 private:
 public:
  void OperatorControl() {
    Listener listener{"/dev/ttyUSB0"};
    listener.Start();
    auto logger = spdlog::get("serial");
    while (IsEnabled()) {
      logger->info("azimuth error: {}, range: {}", listener.GetAzimuthError(),
                   listener.GetRange());
      std::this_thread::sleep_for(LOOP_SLEEP_MS);
    }
  }

  void RobotInit() {
    // serial.setTimeout(serial::Timeout::max());
    auto logger = spdlog::stdout_color_st("serial");
  }

  void Disabled() {
    while (IsDisabled()) {
      std::this_thread::sleep_for(LOOP_SLEEP_MS);
    }
  }
};

START_ROBOT_CLASS(Robot)
