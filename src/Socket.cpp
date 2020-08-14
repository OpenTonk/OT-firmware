#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>

#include "Socket.h"
#include "MotorControl.h"

int port = 4200;
int clientCount = 0;
WiFiServer server(0);
MotorControl motorController({{4, 2},
                              {18, 19}});

bool StartSocketServer(MotorControl controller)
{
    server.begin(port);
    Serial.print("tcp server listening on ");
    Serial.println(port);

    motorController = controller;

    return true;
}

void SocketLoop()
{
    WiFiClient client = server.available();
    uint8_t data[5];

    if (client)
    {
        Serial.println("New client");
        clientCount++;

        if (clientCount > 1)
        {
            client.stop();
        }
        else
        {
            while (client.connected())
            {
                if (client.available())
                {
                    int l = client.read(data, 5);

                    if (l < 5)
                    {
                        data[l] = '\0';
                    }
                    else
                    {
                        data[5] = '\0';
                    }

                    char *msg = (char *)data;

                    Serial.print("Client send: ");
                    Serial.print(sizeof(msg));
                    Serial.println(msg);

                    if (strcmp(msg, "stop") == 0)
                    {
                        client.stop();
                        motorController.setRightSpeed(0);
                        motorController.setLeftSpeed(0);
                        ESP.restart();
                    }

                    char n[] = {msg[2], msg[3], msg[4]};
                    int speed = atoi(n);

                    if (msg[0] == 'R')
                    {
                        if (msg[1] == '-')
                        {
                            speed = -speed;
                        }
                        motorController.setRightSpeed(speed);
                    }

                    if (msg[0] == 'L')
                    {
                        if (msg[1] == '-')
                        {
                            speed = -speed;
                        }
                        motorController.setLeftSpeed(speed);
                    }
                }
                motorController.loop();
            }
        }

        clientCount--;
        Serial.println("Client disconnected");
    }
}