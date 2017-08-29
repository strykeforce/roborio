#include <chrono>
#include <iostream>
#include <thread>

#include "AHRS.h"
#include "WPILib.h"

/*
 * This program is used to measure the frequency of NavX errors.
 *
 * It prints a stream of millisecond timestamps corresponding to the last good
 * sensor read. Any errors noted by the NavX library are printed to standard
 * output and are interleaved with the timestamps.
 *
 * Excessive SPI errors have been noted while running this when
 * /etc/init.d/nilvrt is running so run `/etc/init.d/nilvrt stop` first.
 *
 * TIMESTAMP_PERIOD_MS = how often a timestamp is printed to standard output
 * LOOP_SLEEP_MS = run loop wait period
 */

static constexpr double TIMESTAMP_PERIOD_MS = 10 / 1000;
static constexpr auto LOOP_SLEEP_MS = std::chrono::milliseconds(1);

class Robot : public SampleRobot {
 public:
  AHRS gyro{SPI::Port::kMXP, 66};

  void OperatorControl() {
    frc::Timer timer;
    timer.Start();
    while (IsEnabled()) {
      if (timer.HasPeriodPassed(TIMESTAMP_PERIOD_MS)) {
        std::cout << gyro.GetLastSensorTimestamp() << std::endl;
      }
      std::this_thread::sleep_for(LOOP_SLEEP_MS);
    }
  }

  void RobotInit() { gyro.EnableLogging(true); }

  void Disabled() {
    while (IsDisabled()) {
      std::this_thread::sleep_for(LOOP_SLEEP_MS);
    }
  }
};

START_ROBOT_CLASS(Robot)
