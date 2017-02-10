#pragma once

#include <cstdint>
#include <string>

namespace deadeye {

uint8_t CalculateChecksum(std::string s);
uint8_t FromHex(const char a);
std::string ToHex(uint8_t);

} /* deadeye */
