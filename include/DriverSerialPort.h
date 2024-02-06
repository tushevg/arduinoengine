#ifndef DRIVERSERIALPORT_H
#define DRIVERSERIALPORT_H

#include <Arduino.h>
#include "Definitions.h"

class DriverSerialPort
{
public:
    DriverSerialPort();

    void open(const uint32_t baudRate);
    void poll();
    bool received();
    const char* message();

private:
    bool m_flagReady;
    bool m_flagReceiving;
    uint32_t m_bufferIndex;
    char m_buffer[SERIAL_BUFFER_SIZE + 1];
};

#endif /* DRIVERSERIALPORT_H */
