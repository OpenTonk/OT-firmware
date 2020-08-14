#include <Arduino.h>

#include "AccessPoint.h"
#include "Socket.h"

#include "MotorControl.h"

void setup() {
  Serial.begin(9600);

  Serial.println("Trying to start AP");

  if (startAP())
  {
    Serial.print("AP IP: ");
    Serial.println(getIP());
  } else {
    Serial.println("Failed to start AP!");
    Serial.println("Restarting in 10 seconds");

    for (size_t i = 0; i < 10; i++)
    {
      Serial.print(".");
      sleep(1);
    }
    
    ESP.restart();
  }

  StartSocketServer();
}

void loop() {
  SocketLoop();
}