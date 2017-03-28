#pragma once

#include <WPILib.h>

namespace cheesecake {

class StopClimber : public frc::InstantCommand {
 public:
  StopClimber();
  virtual ~StopClimber() = default;

 protected:
  void Initialize() override;
};

} /* cheesecake */
