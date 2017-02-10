#pragma once
#include <atomic>
#include <mutex>
#include <string>
#include <thread>

class Listener {
 public:
  enum Mode {
    kBoiler,
    kGear,
  };

  Listener(std::string port, uint32_t speed = 115200);
  virtual ~Listener();

  void Start();
  Mode GetMode();
  int GetAzimuthError();
  int GetRange();

 private:
  std::string port_;
  uint32_t speed_;
  Mode mode_;
  int azimuth_error_;
  int range_;
  std::thread thread_;
  std::atomic_bool stop_thread_;
  std::mutex mutex_;

  void Run();
};
