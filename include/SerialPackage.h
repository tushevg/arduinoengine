#ifndef SERIALPACKAGE_H
#define SERIALPACKAGE_H

#include "Arduino.h"
#include "Definitions.h"

class SerialPackage
{
public:
    SerialPackage();

    void parse(const char *message);
    const char* message();
    void error(uint8_t errorCode);
    
    uint8_t pack8bit(uint8_t index);
    uint16_t pack16bit(uint8_t index);
    uint32_t pack32bit(uint8_t index);

    void unpack8bit(uint8_t index, uint8_t value);
    void unpack16bit(uint8_t index, uint16_t value);
    void unpack32bit(uint8_t index, uint32_t value);

    uint8_t m_address;
    uint8_t m_command;
    
private:    
    uint8_t m_checksum;
    uint8_t m_size;
    uint8_t m_data[SERIAL_DATA_SIZE];
    char m_message[SERIAL_BUFFER_SIZE + 2];

    uint8_t hexToByte(char msb, char lsb);
    uint8_t hexToDec(char hex);
    void byteToHex(char *message, uint8_t value);
    char bitsToHex(uint8_t bits);
    void calculateCheckSum();
};

#endif /* SERIALPACKAGE_H */
