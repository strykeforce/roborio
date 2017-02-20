#include <WPILib.h>
#include <iostream>

using namespace std;

class Robot : public IterativeRobot {
  Servo* servo;

 public:
  Robot() {}

  void RobotInit() { servo = new Servo(0); }
  void RobotPeriodic() {}
  void DisabledInit() {}
  void DisabledPeriodic() {}
  void TeleopInit() {}

  void TeleopPeriodic() {
    double pos;
    cin >> pos;
    servo->Set(pos);
  }
};

START_ROBOT_CLASS(Robot)
