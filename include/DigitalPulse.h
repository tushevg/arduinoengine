#ifndef DIGITALPULSE_H
#define DIGITALPULSE_H

#include <Arduino.h>

class DigitalPulse
{
public:
    DigitalPulse();

    uint32_t duration();
    void start();
    void stop();
    void resume();
    void pause();
    void update();

    uint8_t m_pin;
    uint32_t m_delay;
    uint32_t m_uptime;
    uint32_t m_downtime;
    uint32_t m_cycles;

private:

    uint8_t m_state;
    uint8_t m_stateHistory;
    uint32_t m_cycleIndex;
    uint32_t m_timeout;
    uint32_t m_timestamp;

    enum PulseState : uint8_t
    {
        STATE_IDLE = 0,
        STATE_DELAY = 1,
        STATE_UPTIME = 2,
        STATE_DOWNTIME = 3,
        STATE_PERIOD = 4
    };
};

#endif /* DIGITALPULSE_H */
