#include "climber.h"

using namespace cheesecake;

Climber::Climber(double climb_speed, double reverse_speed)
    : frc::Subsystem("Climber"),
      speed_(climb_speed),
      reverse_speed_(reverse_speed) {}

void Climber::Start() {
  t0.Set(speed_);
  t1.Set(speed_);
}

void Climber::Stop() {
  t0.Set(0);
  t1.Set(0);
}

void Climber::Reverse() {
  t0.Set(reverse_speed_);
  t1.Set(reverse_speed_);
}
