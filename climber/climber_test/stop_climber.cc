#include "stop_climber.h"

#include "../climber_test.h"

using namespace cheesecake;
using namespace std;

StopClimber::StopClimber() { Requires(Robot::climber); }

void StopClimber::Initialize() { Robot::climber->Stop(); }
