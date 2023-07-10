// Class for Serial Port on Windows PC.
// Opens the port, reads data from the port, writes data from the port

#ifndef SERIALPORT_H
#define SERIALPORT_H

#define ARDUINO_WAIT_TIME 2000
//#define BAUD_RATE CBR_9600
#define BAUD_RATE CBR_115200

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class SerialPort{
private:
    HANDLE handleToCOM;
    bool connected;
    COMSTAT status;
    DWORD errors;
public:
    SerialPort(const char* portName);
    ~SerialPort();

    int ReadSerialPort(char* buffer, unsigned int buf_size);
    bool WriteSerialPort(char* buffer, unsigned int buf_size);
    bool isConnected();
};

#endif // SERIALPORT_H
