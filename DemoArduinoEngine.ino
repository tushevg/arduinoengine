#include "Arduino.h"
#include "DriverSerialPort.h"
#include "SerialPackage.h"
#include "HardwareLayout.h"
#include "Queue.h"
#include "Event.h"


DriverSerialPort *port = new DriverSerialPort();
SerialPackage *package = new SerialPackage();
HardwareLayout *layout = new HardwareLayout();
Queue<Event*> *queue = new Queue<Event*>(16);

volatile uint32_t eventCounter = 0;

void setup()
{
    port->open(9600);
}

void loop()
{
  
  port->poll();
  if (port->received())
  {
    Serial.println(port->message());
    package->parse(port->message());
    Event *eventNew = new Event(package->m_address,
                                package->m_command,
                                eventCounter++);
    layout->dispatch(eventNew, package);
    if (!queue->push(eventNew))
    {
        package->error(ERROR_EVENT_QUEUE_IS_FULL);
        Serial.println(package->message());
    }
  }

  
  if (queue->count() > 0)
  {
    Event *eventOut = queue->pop();
    package->m_address = eventOut->m_address;
    package->m_command = eventOut->m_command;
    package->unpack32bit(0, eventOut->m_counter);
    package->unpack32bit(4, eventOut->m_timestamp);
    package->unpack32bit(8, eventOut->m_value);
    
    Serial.println(package->message());
  }
  

}
