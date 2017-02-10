#include "sentence.h"

#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>

#include "checksum.h"

using namespace deadeye;
using namespace std;

Sentence::Sentence()
    : parsed_checksum(0), calculated_checksum(0), is_valid_(false) {}

Sentence::~Sentence() {}

bool Sentence::ChecksumOK() const {
  return (parsed_checksum != 0 && calculated_checksum != 0) &&
         (parsed_checksum == calculated_checksum);
}

bool Sentence::Valid() const {
  return is_valid_ && ChecksumOK();
}

string Sentence::ToString() const {
  string ts = this->name;
  ts += ParametersToString();
  return '$' + ts + '*' + ToHex(CalculateChecksum(ts));
}

/** Stringify parameters, comma before each.
 */
string Sentence::ParametersToString() const {
  string ts;
  for_each(parameters.begin(), parameters.end(), [&ts](const string& s) {
    ts += ',';
    ts += s;
  });
  return ts;
}
