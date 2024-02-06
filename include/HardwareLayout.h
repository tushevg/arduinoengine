#ifndef HARDWARELAYOUT_H
#define HARDWARELAYOUT_H

#include <Arduino.h>
#include "Definitions.h"
#include "SerialPackage.h"
#include "Event.h"

class HardwareLayout
{
public:
    HardwareLayout();

    void dispatch(Event *event, SerialPackage *package);

private:
    typedef void (HardwareLayout::*ActionType)(Event *event, SerialPackage *package);
    ActionType m_actionTable[EVENT_TABLE_SIZE];

    void ActionHandshake(Event *event, SerialPackage *package);
    void ActionPower(Event *event, SerialPackage *package);
    void ActionStart(Event *event, SerialPackage *package);
    void ActionStop(Event *event, SerialPackage *package);
    void ActionResume(Event *event, SerialPackage *package);
    void ActionPause(Event *event, SerialPackage *package);
    void ActionTrial(Event *event, SerialPackage *package);
    void ActionSetTimer(Event *event, SerialPackage *package);
    void ActionSetDelay(Event *event, SerialPackage *package);
    void ActionSetUptime(Event *event, SerialPackage *package);
    void ActionSetDowntime(Event *event, SerialPackage *package);
    void ActionSetCycles(Event *event, SerialPackage *package);
};

#endif /* HARDWARELAYOUT_H */
