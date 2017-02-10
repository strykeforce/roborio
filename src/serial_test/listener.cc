#include "listener.h"

#include <atomic>
#include <mutex>
#include <string>
#include <thread>

#include "serial/serial.h"
#include "spdlog/spdlog.h"

#include "parser.h"
#include "sentence.h"

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

Listener::Mode Listener::GetMode() {
  std::lock_guard<std::mutex> lock(mutex_);
  return mode_;
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
  serial::Timeout timeout{0, 50, 0, 0, 0};
  serial::Serial serial{port_, speed_, timeout};
  serial.flushInput();
  deadeye::Parser parser;
  while (!stop_thread_) {
    std::string line = serial.readline();
    deadeye::Sentence sentence;
    parser.ParseText(sentence, line);
    bool valid = sentence.Valid();
    logger->trace(
        "name = {}, valid = {}, parameters[0] = {}, parameters[1] = {}",
        sentence.name, valid, sentence.parameters[0], sentence.parameters[1]);
    if (!valid) {
      logger->warn("sentence invalid");
      continue;
    }
    int azimuth_error = std::stoi(sentence.parameters[0]);
    int range = std::stoi(sentence.parameters[1]);
    {
      std::lock_guard<std::mutex> lock(mutex_);
      azimuth_error_ = azimuth_error;
      range_ = range;
    }
  }
  serial.close();
}
