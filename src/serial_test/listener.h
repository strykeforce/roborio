#pragma once
#include <atomic>
#include <mutex>
#include <string>
#include <thread>

class Listener {
 private:
  std::string port_;
  uint32_t speed_;
  int azimuth_error_;
  int range_;
  std::thread thread_;
  std::atomic_bool stop_thread_;
  std::mutex mutex_;

  void Run();

 public:
  Listener(std::string port, uint32_t speed = 115200);
  virtual ~Listener();

  void Start();
  int GetAzimuthError();
  int GetRange();
};
