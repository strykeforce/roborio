#include "reverse_climber.h"

#include "../climber_test.h"

using namespace cheesecake;
using namespace std;

ReverseClimber::ReverseClimber() { Requires(Robot::climber); }

void ReverseClimber::Initialize() { Robot::climber->Reverse(); }
