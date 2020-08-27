#ifndef Socket_h
#define Socket_h

#include <WiFiUdp.h>
#include "MotorControl.h"

class Socket
{
private:
    MotorControl* motorController;
    int clientCount;
    WiFiUDP udp;

public:
    Socket(MotorControl* controller);
    void start();
    void Loop();
};


#endif