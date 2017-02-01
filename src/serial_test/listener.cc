#include "listener.h"

#include <atomic>
#include <mutex>
#include <string>
#include <thread>

#include "serial/serial.h"
#include "spdlog/spdlog.h"

Listener::Listener(std::string port, uint32_t speed)
    : port_{port},
      speed_{speed},
      mode_{Listener::Mode::kGear},
      azimuth_error_{0},
      range_{0},
      thread_{},
      stop_thread_{false} {}

Listener::~Listener() {
  stop_thread_ = true;
  if (thread_.joinable()) thread_.join();
}

int Listener::GetMode() {
  std::lock_guard<std::mutex> lock(mutex_);
  return mode_;
}

void Listener::Send(int azimuth_error, int range) {
  std::lock_guard<std::mutex> lock(mutex_);
  azimuth_error_ = azimuth_error;
  range_ = range;
}

void Listener::Start() { thread_ = std::thread{&Listener::Run, this}; }

void Listener::Run() {
  auto logger = spdlog::get("serial");
  logger->set_level(spdlog::level::debug);
  serial::Timeout timeout{0, 5, 0, 0, 0};
  serial::Serial serial{port_, speed_, timeout};
  serial.flushInput();
  while (!stop_thread_) {
    std::string mode = serial.read(1);
    logger->debug("mode = {}", mode);
    char command = mode[0];
    {
      std::lock_guard<std::mutex> lock(mutex_);
      switch (command) {
        case 'B':
          mode_ = kBoiler;
          break;
        case 'G':
          mode_ = kGear;
          break;
        default:
          logger->error("unrecognized mode = {}", command);
      }
      serial.write(std::to_string(azimuth_error_) + "," +
                   std::to_string(range) + "\n");
    }
  }
  serial.close();
}
