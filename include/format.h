#ifndef FORMAT_H
#define FORMAT_H

#include <string>

namespace Format {
std::string ElapsedTime(long times);  // See src/format.cpp
std::string toDoubleDigits(long num);  // See src/format.cpp
};                                    // namespace Format

#endif