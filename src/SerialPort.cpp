// Class for Serial Port on Windows PC.
// Opens the port, reads data from the port, writes data from the port

#include "../hdr/SerialPort.h"

SerialPort::SerialPort(const char* portName) : connected(false), status({0}), errors(0){

    handleToCOM = CreateFileA(static_cast<LPCSTR>(portName), GENERIC_READ | GENERIC_WRITE,
                              0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    DWORD errCode = GetLastError();

    if      (errCode == 2) { std::cout << "Please, plug the device in!\n"; }
    if      (errCode == 5) { std::cout << "Another app is already using the device!\n"; }
    else if (errCode == 0) {

        DCB dcbSerialParameters {0};

        if (!GetCommState(handleToCOM, &dcbSerialParameters)) { std::cout << "Cannot get current serial parameters!\n"; }
        else {
            dcbSerialParameters.BaudRate = BAUD_RATE;
            dcbSerialParameters.ByteSize = 8;
            dcbSerialParameters.StopBits = ONESTOPBIT;
            dcbSerialParameters.Parity = NOPARITY;
            dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;
        }

        if (!SetCommState(handleToCOM, &dcbSerialParameters)) { std::cout << "Cannot set serial parameters!\n"; }
        else {
            connected = true;
            PurgeComm(handleToCOM, PURGE_RXCLEAR | PURGE_TXCLEAR);
            Sleep(ARDUINO_WAIT_TIME);
        }
    }

}
//=======================================================================
SerialPort::~SerialPort(){
    if (connected){
        CloseHandle(handleToCOM);
        connected = false;
    }
}
//=======================================================================
int SerialPort::ReadSerialPort(char* buffer, unsigned int buf_size){

    DWORD bytesRead;
    unsigned int toRead = 0;

    ClearCommError(handleToCOM, &errors, &status);

    if (status.cbInQue > 0){
        if (status.cbInQue > buf_size) { toRead = buf_size; }
        else                           { toRead = status.cbInQue; };
    }

    if (ReadFile(handleToCOM, buffer, toRead, &bytesRead, NULL)){
        return bytesRead;
    }

    return 0;
}
//=======================================================================
bool SerialPort::WriteSerialPort(char* buffer, unsigned int buf_size){

    DWORD bytesWritten = 0;
    unsigned int toWrite = buf_size;

    ClearCommError(handleToCOM, &errors, &status);

    if (WriteFile(handleToCOM, buffer, toWrite, &bytesWritten, NULL)){
        return true;
    }
    //if (bytesWritten == 0) return false; /// if (bytesWritten != buf_size) return false
    return false;
}
//=======================================================================
bool SerialPort::isConnected(){ return connected; }
