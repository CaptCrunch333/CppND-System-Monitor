#include <string>

#include "format.h"

using std::string;

// Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) {
    int hours = seconds/3600;
    int minutes = (seconds - hours*3600)/60;
    int sec_rem = seconds % 60;
    string sep = ":";
    
    return std::to_string(hours) + sep + Format::toDoubleDigits(minutes) + sep + Format::toDoubleDigits(sec_rem);
}

string Format::toDoubleDigits(long num) { return num < 10 ? "0" + std::to_string(num) : std::to_string(num); }