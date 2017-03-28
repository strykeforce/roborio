#pragma once

#include <WPILib.h>

namespace cheesecake {

class StartClimber : public frc::InstantCommand {
 public:
  StartClimber();
  virtual ~StartClimber() = default;

 protected:
  void Initialize() override;
};

} /* cheesecake */
