#include <WPILib.h>
#include <iostream>

using namespace std;

class Robot : public IterativeRobot {
  Servo *left_servo, *right_servo;

 public:
  Robot() {}

  void RobotInit() {
    left_servo = new Servo(0);
    right_servo = new Servo(1);
  }
  void RobotPeriodic() {}
  void DisabledInit() {}
  void DisabledPeriodic() {}
  void TeleopInit() {}

  void TeleopPeriodic() {
    int pos;
    cin >> pos;
    // left_servo->Set(pos);
    // right_servo->Set(pos);

    switch (pos) {
      case 1:
        left_servo->Set(0.75);
        right_servo->Set(0.32);
        break;
      case 3:
        left_servo->Set(0.84);
        right_servo->Set(0.2);
        break;
      case 4:
        left_servo->Set(0.45);
        right_servo->Set(0.6);
        break;
      case 2:
      default:
        left_servo->Set(0.5);
        right_servo->Set(0.5);
        break;
    }
  }
};

START_ROBOT_CLASS(Robot)
