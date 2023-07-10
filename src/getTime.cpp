// Gets current system time in format d-m-Y H-M-S

#include "../hdr/getTime.h"

std::string getTime(){

    std::ostringstream oss;

    auto t = std::time(nullptr);

    auto tm = *std::localtime(&t);

    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");

    return oss.str();
}
