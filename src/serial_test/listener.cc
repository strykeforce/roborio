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
      azimuth_error_{0},
      range_{0},
      thread_{},
      stop_thread_{false} {}

Listener::~Listener() {
  stop_thread_ = true;
  if (thread_.joinable()) thread_.join();
}

int Listener::GetAzimuthError() {
  std::lock_guard<std::mutex> lock(mutex_);
  return azimuth_error_;
}

int Listener::GetRange() {
  std::lock_guard<std::mutex> lock(mutex_);
  return range_;
}

void Listener::Start() { thread_ = std::thread{&Listener::Run, this}; }

void Listener::Run() {
  auto logger = spdlog::get("serial");
  logger->set_level(spdlog::level::debug);
  serial::Serial serial{port_, speed_,
                        serial::Timeout::simpleTimeout(serial::Timeout::max())};
  serial.flushInput();
  while (!stop_thread_) {
    std::string msg = serial.readline();
    auto comma = msg.find(',');
    std::string a = msg.substr(0, comma);
    std::string r = msg.substr(comma + 1);
    logger->debug("a = {}, r = {}", a, r);
    {
      std::lock_guard<std::mutex> lock(mutex_);
      azimuth_error_ = std::stoi(a);
      range_ = std::stoi(r);
    }
  }
  serial.close();
}
