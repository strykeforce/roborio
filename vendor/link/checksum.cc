#include "checksum.h"

#include <cstdio>

uint8_t deadeye::CalculateChecksum(std::string s) {
  uint8_t checksum = 0;
  for (const char& c : s) {
    checksum ^= c;
  }
  return checksum;
}

uint8_t deadeye::FromHex(const char a) {
  if (a >= 'A' && a <= 'F')
    return a - 'A' + 10;
  else
    return a - '0';
}

std::string deadeye::ToHex(uint8_t i) {
  char buf[3];
  std::sprintf(buf, "%02X", i);
  return std::string(buf);
}
