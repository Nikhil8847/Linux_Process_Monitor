#pragma once

#include <string>
#include <fstream>

using std::string;
using std::ifstream;

class Util {
public:
    static string convertToTime(long int);
    static string getProgressBar(string);
    static ifstream getStream(string);
};