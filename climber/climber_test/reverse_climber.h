#pragma once

#include <WPILib.h>

namespace cheesecake {

class ReverseClimber : public frc::InstantCommand {
 public:
  ReverseClimber();
  virtual ~ReverseClimber() = default;

 protected:
  void Initialize() override;
};

} /* cheesecake */
