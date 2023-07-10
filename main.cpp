// This console program opens serial port (see const std::string port param. below)
// on a Windows PC to which Arduino/ESP32 board is connected.
// You can send commands to the Arduino/ESP32 board (c-type string) to control 2d plotter
// Program receives the incoming data, prints it to the console
// and logs the data to the file (see const std::string log_file_name param. below).

#include <iostream>
#include <iomanip>
#include <thread>
#include <string>
#include <conio.h>

#include "hdr/SerialPort.h"
#include "hdr/logToFile.h"

#define INPUT_DATA_BYTES 1 // read data 1 byte at a time in order to get the end of the message ('}' symbol)

char inputData[INPUT_DATA_BYTES];
const std::string port = {"COM9"};
const std::string log_file_name = {"2d_plotter.txt"};
std::string data_received;

int main(){

    SerialPort arduino(port.c_str());

    if (arduino.isConnected()){
        std::cout << "Connected to the port " << port << std::endl;
    }
    else { std::cin.get(); }


    while (arduino.isConnected()){

        /// getting console input to send command to the plotter
        if (kbhit() != 0) {
            std::string command;// = "Y100\n Y50\n Y60\n Y40";
            std::getline(std::cin, command);
            if (!command.empty()) {
                command += '\n';
                char *cmd = const_cast<char*>(command.c_str());
                bool write_status = arduino.WriteSerialPort(cmd, command.size());//
                if (write_status) {
                    std::cout << "Command " << command << " sent successfully!" << std::endl;
                }
            }
        }
        /// reading data from plotter
        if (arduino.ReadSerialPort(inputData, INPUT_DATA_BYTES)){
            std::string currentChunk(inputData);
            data_received += currentChunk;
        }

        if (data_received.back() == '\n'){
            std::cout << "----RECEIVED: " << data_received;
            /// logging received data to file
            if (!logToFile(log_file_name, data_received)) {
                std::cerr << "Logging to file failed!\n";
            }
            data_received.clear();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

    }

    system("pause");

    return 0;
}
