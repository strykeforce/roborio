#include <WPILib.h>
#include <iostream>

using namespace std;

class Robot : public IterativeRobot {
  frc::PWM* pwm;

 public:
  Robot() {}

  void RobotInit() { pwm = new frc::PWM(0); }
  void RobotPeriodic() {}
  void DisabledInit() {}
  void DisabledPeriodic() {}
  void TeleopInit() {}

  void TeleopPeriodic() {
    uint16_t pos;
    cin >> pos;
    pwm->SetRaw(pos);
  }
};

START_ROBOT_CLASS(Robot)
