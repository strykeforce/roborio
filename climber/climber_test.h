#pragma once

#include <WPILib.h>
#include <iostream>

#include "climber_test/climber.h"

class Robot : public IterativeRobot {
 public:
  static cheesecake::Climber* climber;

  void RobotInit() override;

  void TeleopPeriodic() override;
};
