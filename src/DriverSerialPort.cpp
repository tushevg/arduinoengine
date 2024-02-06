#include "DriverSerialPort.h"

DriverSerialPort::DriverSerialPort() :
    m_flagReady(false),
    m_flagReceiving(false),
    m_bufferIndex(0)
{

}


void DriverSerialPort::open(const uint32_t baudRate)
{
    Serial.begin(baudRate);
}


void DriverSerialPort::poll()
{
    m_flagReady = false;

    if (Serial.available())
    {
        char newByte = (char)Serial.read();

        if (m_flagReceiving)
        {
            // extend buffer
            m_buffer[m_bufferIndex] = newByte;
            m_bufferIndex++;

            // disable message to buffer
            if ((newByte == SERIAL_MESSAGE_END) || (m_bufferIndex > SERIAL_BUFFER_SIZE))
            {
                m_flagReceiving = false;
                m_flagReady = true;
                m_buffer[m_bufferIndex - 1] = '\0';
            }
        }
        else
        {
            // enable message to buffer
            if (newByte == SERIAL_MESSAGE_START)
            {
                m_flagReceiving = true;
                m_bufferIndex = 0;
            }
        }
    }
}


bool DriverSerialPort::received()
{
   return m_flagReady;
}


const char* DriverSerialPort::message()
{
    return m_buffer;
}
