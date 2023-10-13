#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    std::string result;
    int uptime_hours, uptime_minutes, uptime_seconds;
    uptime_hours = seconds/3600;
    uptime_minutes = (seconds % 3600)/60;
    uptime_seconds = seconds % 60;
    // compute h, m, s
    std::string h = std::to_string(uptime_hours);
    std::string m = std::to_string(uptime_minutes);
    std::string s = std::to_string(uptime_seconds);
    // adding leading zero if needed
    std::string hh = std::string(2 - h.length(),'0') + h;
    std::string mm = std::string(2 - m.length(),'0') + m;
    std::string ss = std::string(2 - s.length(),'0') + s;
    // result hh:mm:ss
    result = hh + ':' + mm + ':' + ss;
    
    return result; }