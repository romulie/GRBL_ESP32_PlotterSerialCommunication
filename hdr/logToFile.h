// Opens file (const std::string &filename) and appends the incoming message (const std::string &msg)
// preceded by current system time in format d-m-Y H-M-S

#ifndef LOGTOFILE_H
#define LOGTOFILE_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "getTime.h"

bool logToFile(const std::string &filename, const std::string &msg);

#endif // LOGTOFILE_H



