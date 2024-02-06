#include "HardwareLayout.h"

HardwareLayout::HardwareLayout()
{
    // links events with actions
    m_actionTable[EVENT_HANDSHAKE] = &HardwareLayout::ActionHandshake;
    m_actionTable[EVENT_POWER] = &HardwareLayout::ActionPower;
    m_actionTable[EVENT_START] = &HardwareLayout::ActionStart;
    m_actionTable[EVENT_STOP] = &HardwareLayout::ActionStop;
    m_actionTable[EVENT_RESUME] = &HardwareLayout::ActionResume;
    m_actionTable[EVENT_PAUSE] = &HardwareLayout::ActionPause;
    m_actionTable[EVENT_TRIAL] = &HardwareLayout::ActionTrial;
    m_actionTable[EVENT_SETTIMER] = &HardwareLayout::ActionSetTimer;
    m_actionTable[EVENT_SETDELAY] = &HardwareLayout::ActionSetDelay;
    m_actionTable[EVENT_SETUPTIME] = &HardwareLayout::ActionSetUptime;
    m_actionTable[EVENT_SETDOWNTIME] = &HardwareLayout::ActionSetDowntime;
    m_actionTable[EVENT_SETCYCLES] = &HardwareLayout::ActionSetCycles;
}


void HardwareLayout::dispatch(Event *event, SerialPackage *package)
{
    // check validity of address
    if (event->m_address != SR_ADDRESS_INPUT)
    {
        event->m_address = SR_ADDRESS_ERROR;
        event->m_command = ERROR_SENDER_RECEIVER_ADDRESS;
        return;
    }

    // check validity of command
    if (event->m_command >= EVENT_TABLE_SIZE)
    {
        event->m_address = SR_ADDRESS_ERROR;
        event->m_command = ERROR_UNKNOWN_COMMAND_CODE;
    }

    // evoke callback
    if (m_actionTable[event->m_command] != NULL)
    {
        event->m_address = SR_ADDRESS_OUTPUT;
        (this->*m_actionTable[event->m_command])(event, package);
    }
}


void HardwareLayout::ActionHandshake(Event *event, SerialPackage *package)
{

    event->m_value = package->pack32bit(0);
}


void HardwareLayout::ActionPower(Event *event, SerialPackage *package)
{
    //uint8_t doline = package->pack8bit(0);
    //uint8_t dostate = package->pack8bit(1);

    // set doline to dostate
}


void HardwareLayout::ActionStart(Event *event, SerialPackage *package)
{
    // start
}


void HardwareLayout::ActionStop(Event *event, SerialPackage *package)
{
    // stop
}


void HardwareLayout::ActionResume(Event *event, SerialPackage *package)
{
    // resume
}


void HardwareLayout::ActionPause(Event *event, SerialPackage *package)
{
    // pause
}


void HardwareLayout::ActionTrial(Event *event, SerialPackage *package)
{
    //uint8_t trigger_mask = package->pack8bit(0);
}


void HardwareLayout::ActionSetTimer(Event *event, SerialPackage *package)
{
    //uint32_t timer_period = package->pack32bit(0);
}


void HardwareLayout::ActionSetDelay(Event *event, SerialPackage *package)
{
    //uint8_t index = package->pack8bit(0);
    //uint8_t value = package->pack32bit(1);
}


void HardwareLayout::ActionSetUptime(Event *event, SerialPackage *package)
{
    //uint8_t index = package->pack8bit(0);
    //uint8_t value = package->pack32bit(1);
}


void HardwareLayout::ActionSetDowntime(Event *event, SerialPackage *package)
{
    //uint8_t index = package->pack8bit(0);
    //uint8_t value = package->pack32bit(1);
}


void HardwareLayout::ActionSetCycles(Event *event, SerialPackage *package)
{
    //uint8_t index = package->pack8bit(0);
    //uint8_t value = package->pack32bit(1);
}
