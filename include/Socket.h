#ifndef Socket_h
#define Socket_h

#include "MotorControl.h"

bool StartSocketServer(MotorControl controller);

void SocketLoop();

#endif