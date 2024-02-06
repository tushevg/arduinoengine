#include "SerialPackage.h"

SerialPackage::SerialPackage() :
    m_address(0),
    m_command(0),
    m_checksum(0),
    m_size(0)
{
    
}


void SerialPackage::parse(const char *message)
{
    uint8_t messageLength = strlen(message);

    // check message minimum required length 
    if (messageLength < SERIAL_MESSAGE_MIN_LENGTH)
    {
        error(ERROR_SERIAL_MESSAGE_TOO_SHORT);
        return;
    }

    // check if message is whole
    if ((messageLength % 2) != 0)
    {
        error(ERROR_SERIAL_MESSAGE_TRUNCATED);
        return;
    }

    // parse message
    m_address = hexToByte(message[0], message[1]);
    m_command = hexToByte(message[2], message[3]);

    uint8_t i = 0;
    for (uint8_t k = 4; k < (messageLength - 2); k+=2)
    {
        if (i < SERIAL_DATA_SIZE)
        {
            m_data[i++] = hexToByte(message[k], message[k + 1]);
        }
    }
    m_size = i;
    
    // check message validity
    calculateCheckSum();
    
    /*
    uint8_t checksum_test = hexToByte(message[messageLength - 2], message[messageLength - 1]);
    if (m_checksum != checksum_test)
    {
        error(ERROR_INVALID_CHECKSUM);
        return;
    }
    */
}


const char* SerialPackage::message()
{
    // calculate checksum
    calculateCheckSum();

    // convert data to hex message
    m_message[0] = '!';
    byteToHex(&m_message[1], m_address);
    byteToHex(&m_message[3], m_command);
    
    uint8_t i = 5;
    for (uint8_t k = 0; k < m_size; k++)
    {
        if ((i + 2) < SERIAL_BUFFER_SIZE)
        {
            byteToHex(&m_message[i], m_data[k]);
            i += 2;
        }
    }
    byteToHex(&m_message[i], m_checksum);
    
    m_message[i + 2] = '\0';
    
    return m_message;
}


void SerialPackage::error(uint8_t errorCode)
{
    m_address = SR_ADDRESS_ERROR;
    m_command = errorCode;
}



void SerialPackage::unpack8bit(uint8_t index, uint8_t value)
{
    if (index < SERIAL_DATA_SIZE)
        m_data[index] = value;
    m_size = index + SIZE_8BIT;
}


void SerialPackage::unpack16bit(uint8_t index, uint16_t value)
{
    if ((SERIAL_DATA_SIZE - index) >= SIZE_16BIT)
    {
        for (uint8_t k = 0, i = (SIZE_16BIT - 1); k < SIZE_16BIT; k++, i--)
        {
            m_data[index + k] = (uint8_t)(value >> (i * 8));
        }
    }
    m_size = index + SIZE_16BIT;
}


void SerialPackage::unpack32bit(uint8_t index, uint32_t value)
{
    if ((SERIAL_DATA_SIZE - index) >= SIZE_32BIT)
    {
        for (uint8_t k = 0, i = (SIZE_32BIT - 1); k < SIZE_32BIT; k++, i--)
        {
            m_data[index + k] = (uint8_t)(value >> (i * 8));
        }
    }
    m_size = index + SIZE_32BIT;
}


uint8_t SerialPackage::pack8bit(uint8_t index)
{
    uint8_t value = 0;
    if (index < m_size)
        value = m_data[index];
    
    return value;
}


uint16_t SerialPackage::pack16bit(uint8_t index)
{
    uint16_t value = 0;
    uint8_t bitShift = 0;
    for (uint8_t k = 0, i = (SIZE_16BIT - 1); k < SIZE_16BIT; k++, i--)
    {
        if ((index + i) < m_size)
        {
            value |= ((uint16_t)(m_data[index + i]) << bitShift);
            bitShift += SIZE_BITS_IN_BYTE;
        }
    }
    return value;
}


uint32_t SerialPackage::pack32bit(uint8_t index)
{
    uint32_t value = 0;
    uint8_t bitShift = 0;
    for (uint8_t k = 0, i = (SIZE_32BIT - 1); k < SIZE_32BIT; k++, i--)
    {
        if ((index + i) < m_size)
        {
            value |= ((uint32_t)(m_data[index + i]) << bitShift);
            bitShift += SIZE_BITS_IN_BYTE;
        }
    }
    return value;
}

uint8_t SerialPackage::hexToByte(char msb, char lsb)
{
    return (hexToDec(msb) << 4 ) | hexToDec(lsb);
}


uint8_t SerialPackage::hexToDec(char hex)
{
    uint8_t dec = 0;
    
    if (('0' <= hex) && (hex <= '9'))
    {
        dec = hex - '0';
    }
    else if (('a' <= hex) && (hex <= 'f'))
    {
        dec = hex - 'a' + 10;
    }
    else if (('A' <= hex) && (hex <= 'F'))
    {
        dec = hex - 'A' + 10;
    }
    
    return dec;
}


void SerialPackage::calculateCheckSum()
{
    uint16_t CS = m_address + m_command;
    for (uint8_t k = 0; k < m_size; k++)
    {
        CS += m_data[k];
    }

    // calculate two compelemts checksum
    m_checksum = (uint8_t)CS;
    m_checksum = ~m_checksum + 1;
}


void SerialPackage::byteToHex(char *message, uint8_t value)
{
    message[0] = bitsToHex(value >> 4);
    message[1] = bitsToHex(value);
}


char SerialPackage::bitsToHex(uint8_t bits)
{
    bits &= 0xF;
    return (bits > 9) ? (bits - 10 + 'A') : (bits + '0');
}

