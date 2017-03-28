#pragma once

#include <WPILib.h>

namespace cheesecake {
class Climber : public frc::Subsystem {
 public:
  Climber(double climb_speed, double reverse_speed);
  virtual ~Climber() = default;

  void Start();
  void Stop();
  void Reverse();

 private:
  double speed_;
  double reverse_speed_;
  frc::Talon t0{0};
  frc::Talon t1{1};
};
} /* cheesecake */
