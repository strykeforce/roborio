#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace deadeye {

class Sentence {
  friend class Parser;

 public:
  // FIXME: need to be private, not always calculated
  std::string text;
  std::string name;
  std::vector<std::string> parameters;
  std::string checksum;
  uint8_t parsed_checksum;
  uint8_t calculated_checksum;

  Sentence();
  virtual ~Sentence();

  bool ChecksumOK() const;
  bool Valid() const;
  std::string ToString() const;

 protected:
  virtual std::string ParametersToString() const;

 private:
  bool is_valid_;
};

} /* deadeye */
