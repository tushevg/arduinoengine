#include <Arduino.h>
#include "DriverSerialPort.h"

DriverSerialPort *port = new DriverSerialPort();

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
    }
}
