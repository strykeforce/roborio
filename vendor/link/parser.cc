#include "parser.h"

#include <string>
#include <cstdint>
#include <cstring>
#include <memory>

#include "sentence.h"
#include "checksum.h"

using namespace deadeye;

Parser::Parser() {}
Parser::~Parser() {}

void Parser::ParseText(Sentence& sentence, std::string line) {
  sentence.is_valid_ = false;  // assume invalid
  if (line.size() == 0) {
    return;
  }

  sentence.text = line;

  // sentence starts with '$'
  size_t dollar = line.find_last_of('$');
  if (dollar == std::string::npos) {
    // no dollar sign, invalid
    return;
  }
  size_t startbyte = dollar;

  // remove any chars leading '$'
  line = line.substr(startbyte + 1);
  if (line[0] == ',') {
    // empty command, invalid
    return;
  }

  // get checksum
  size_t checksum_idx = line.find_last_of('*');
  if (checksum_idx == std::string::npos) {
    // no checksum, invalid
    return;
  }

  sentence.calculated_checksum =
      CalculateChecksum(line.substr(0, checksum_idx));

  // make our own copy of c-str for strtok to modify, modifying line's c-str is
  // undefined behavior.
  auto parameters =
      std::unique_ptr<char[]>(new char[std::strlen(line.c_str()) + 1]);
  std::strcpy(parameters.get(), line.c_str());

  // command is first token
  char* parm = std::strtok(parameters.get(), ",*");
  if (parm == NULL) {
    // empty sentence or command, invalid
    return;
  }
  sentence.name = std::string(parm);
  parm = std::strtok(NULL, ",*");

  // clear out previous parameters
  sentence.parameters.clear();
  while (parm != NULL) {
    sentence.parameters.push_back(std::string(parm));
    parm = std::strtok(NULL, ",*");
  }

  if (sentence.parameters.empty()) {
    // should have at least checksum, invalid
    return;
  }
  std::string checksum = sentence.parameters.back();
  sentence.parsed_checksum = 16 * FromHex(checksum[0]) + FromHex(checksum[1]);
  // remove checksum
  sentence.parameters.pop_back();

  // made it!
  sentence.is_valid_ = true;
}
