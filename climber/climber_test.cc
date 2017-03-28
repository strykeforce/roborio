#include "climber_test.h"

#include "climber_test/reverse_climber.h"
#include "climber_test/start_climber.h"
#include "climber_test/stop_climber.h"

using namespace cheesecake;
using namespace std;

cheesecake::Climber* Robot::climber;

void Robot::RobotInit() {
  climber = new Climber(-1.0, 0.25);
  SmartDashboard::PutData("Start Climber", new StartClimber());
  SmartDashboard::PutData("Stop Climber", new StopClimber());
  SmartDashboard::PutData("Lower Climber", new ReverseClimber());
}

void Robot::TeleopPeriodic() { frc::Scheduler::GetInstance()->Run(); }

START_ROBOT_CLASS(Robot)
