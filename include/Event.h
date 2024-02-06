#ifndef EVENT_H
#define EVENT_H

class Event
{
public:
    Event(uint8_t address, uint8_t command, uint32_t counter = 0) : 
        m_address(address), 
        m_command(command), 
        m_counter(counter), 
        m_timestamp(millis()), 
        m_value(0) {}
    
    uint8_t m_address;
    uint8_t m_command;
    uint32_t m_counter;
    uint32_t m_timestamp;
    uint32_t m_value;
};

#endif /* EVENT_H */
