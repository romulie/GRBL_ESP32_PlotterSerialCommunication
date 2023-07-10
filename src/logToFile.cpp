// Opens file (const std::string &filename) and appends the incoming message (const std::string &msg)
// preceded by current system time in format d-m-Y H-M-S

#include "../hdr/logToFile.h"

bool logToFile(const std::string &filename, const std::string &msg){

    setlocale(LC_ALL, "rus");

    std::ofstream output(filename, std::ios::app);

    if (!output.is_open()) {
        std::cerr << "Failed to open WRITE-file: "<< filename << '\n';
        return false;
    }

    else {
        output << getTime() << '\t' << msg;// << '\n';
    }

    output.close();

    return true;
}
