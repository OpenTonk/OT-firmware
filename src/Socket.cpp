#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>

#include "Socket.h"
#include "MotorControl.h"

int port = 4200;

Socket::Socket(MotorControl *controller)
{
    motorController = controller;
}

void Socket::start()
{
    udp.begin(port);
    Serial.print("udp server listening on ");
    Serial.println(port);
    clientCount = 0;
}

void Socket::Loop()
{
    uint8_t data[4];

    int packetSize = udp.parsePacket();

    if (packetSize)
    {
        int l = udp.read(data, 4);

        if (l < 4)
        {
            data[l] = '\0';
        }
        else
        {
            data[4] = '\0';
        }

        char *msg = (char *)data;

        //Serial.print("Client send: ");
        //Serial.print(sizeof(msg));
        Serial.println(msg);

        if (strcmp(msg, "stop") == 0)
        {
            motorController->setRightSpeed(0);
            motorController->setLeftSpeed(0);
            ESP.restart();
        }

        char n[] = {msg[2], msg[3]};
        int speed = atoi(n);

        if (speed == 99)
        {
            speed = 100;
        }

        if (msg[0] == 'R')
        {
            if (msg[1] == '-')
            {
                speed = -speed;
            }
            motorController->setRightSpeed(speed);

            Serial.print("Right motor: ");
            Serial.println((float)speed / 100.0 * 255);
        }

        if (msg[0] == 'L')
        {
            if (msg[1] == '-')
            {
                speed = -speed;
            }
            motorController->setLeftSpeed(speed);
            Serial.print("Left motor: ");
            Serial.println((float)speed / 100.0 * 255);
        }
    }
    //motorController.loop();
}