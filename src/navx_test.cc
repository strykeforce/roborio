#include <unistd.h>
#include "AHRS.h"
#include "WPILib.h"
AHRS* gyro;

class Robot : public SampleRobot {
 public:
  Robot() { printf("Hello, World!\n"); }

  void OperatorControl() {
    gyro = new AHRS(SPI::Port::kMXP, 500 * 1000, 66);
    // gyro = new AHRS(SerialPort::Port::kMXP);
    // int Error = 0;
    while (true) {
      printf("Raw Acceleration == <%f, %f, %f>\n", gyro->GetRawAccelX(),
             gyro->GetRawAccelY(), gyro->GetRawAccelZ());
      printf("Velocity         == <%f, %f, %f>\n", gyro->GetVelocityX(),
             gyro->GetVelocityY(), gyro->GetVelocityZ());
      printf("displacement     == <%f, %f, %f>\n", gyro->GetDisplacementX(),
             gyro->GetDisplacementY(), gyro->GetDisplacementZ());
      printf("Pitch            == %f\n", gyro->GetPitch());
      printf("Roll             == %f\n", gyro->GetRoll());
      float CurrentYaw = gyro->GetYaw();
      printf("Yaw              == %f\n", CurrentYaw);
      printf("Temp (C)         == %f\n", gyro->GetTempC());
      printf("\n");
#define NOISE 3
#define GOAL 30
      // if(!(GOAL + NOISE > CurrentYaw && CurrentYaw > GOAL - NOISE))
      //	Error++;
      // printf("Error == %i\n", Error);
      // Wait(0.25);
      usleep(25 * 1000);
    }
  }
};

START_ROBOT_CLASS(Robot)
