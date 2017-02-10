#pragma once

#include <string>
#include <cstdint>

#include "sentence.h"

namespace deadeye {

class Parser {
 public:
  Parser();
  virtual ~Parser();

  /** Fills the sentence with the results of parsing the string.
   */
  void ParseText(Sentence& sentence, std::string txt);
};

} /* deadeye */
