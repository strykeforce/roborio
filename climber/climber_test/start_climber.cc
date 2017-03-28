#include "start_climber.h"

#include "../climber_test.h"

using namespace cheesecake;
using namespace std;

StartClimber::StartClimber() { Requires(Robot::climber); }

void StartClimber::Initialize() { Robot::climber->Start(); }
