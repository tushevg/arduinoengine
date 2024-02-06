#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// Serial communication
static const byte SERIAL_BUFFER_SIZE = 40;
static const byte SERIAL_DATA_SIZE = 16;
static const byte SERIAL_MESSAGE_START = '!';
static const byte SERIAL_MESSAGE_END = '\n';
static const byte SERIAL_MESSAGE_MIN_LENGTH = 6;
static const byte SIZE_BITS_IN_BYTE = 8;
static const byte SIZE_8BIT = sizeof(uint8_t);
static const byte SIZE_16BIT = sizeof(uint16_t);
static const byte SIZE_32BIT = sizeof(uint32_t);

// Sender/Receiver addresses
static const byte SR_ADDRESS_INPUT = 0x01;
static const byte SR_ADDRESS_OUTPUT = 0x11;
static const byte SR_ADDRESS_ERROR = 0xEE;

// Input events
static const byte EVENT_HANDSHAKE = 0x00;
static const byte EVENT_POWER = 0x01;
static const byte EVENT_START = 0x02;
static const byte EVENT_STOP = 0x03;
static const byte EVENT_RESUME = 0x04;
static const byte EVENT_PAUSE = 0x05;
static const byte EVENT_TRIAL = 0x06;
static const byte EVENT_SETTIMER = 0x07;
static const byte EVENT_SETDELAY = 0x08;
static const byte EVENT_SETUPTIME = 0x09;
static const byte EVENT_SETDOWNTIME = 0x0A;
static const byte EVENT_SETCYCLES = 0x0B;
static const byte EVENT_SYNC = 0x0C;
static const byte EVENT_TABLE_SIZE = 0x0D;

// Errors
static const byte ERROR_SENDER_RECEIVER_ADDRESS = 0xFF;
static const byte ERROR_SERIAL_MESSAGE_TOO_SHORT = 0x01;
static const byte ERROR_SERIAL_MESSAGE_TRUNCATED = 0x02;
static const byte ERROR_INVALID_CHECKSUM = 0x03;
static const byte ERROR_EVENT_QUEUE_IS_FULL = 0x04;
static const byte ERROR_UNKNOWN_COMMAND_CODE = 0x05;
static const byte ERROR_ARRAY_TO_PACK_TOO_SHORT = 0x06;


#endif /* DEFINITIONS_H */
