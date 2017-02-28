#include <WPILib.h>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

namespace {
const size_t kDICount = 6;
const auto LOOP_SLEEP_MS = std::chrono::milliseconds(1000);
}

class Robot : public IterativeRobot {
  vector<unique_ptr<frc::DigitalInput>> di_vec;

 public:
  Robot() {}

  void RobotInit() {
    for (size_t i = 0; i < kDICount; i++) {
      di_vec.push_back(make_unique<frc::DigitalInput>(i));
    }
  }
  void RobotPeriodic() {}
  void DisabledInit() {}
  void DisabledPeriodic() {}
  void TeleopInit() {}

  void TeleopPeriodic() {
    while (IsEnabled()) {
      for (size_t i = 0; i < kDICount; i++) {
        cout << i << ": " << di_vec[i]->Get() << "\n";
      }
      cout << endl;
      std::this_thread::sleep_for(LOOP_SLEEP_MS);
    }
  }
};

START_ROBOT_CLASS(Robot)
