#include <Arduino.h>

#include "MotorControl.h"

MotorControl::MotorControl(MotorPins p)
{
    channel = 0;
    frequency = 5000;
    resolution = 8;

    ledcSetup(channel, frequency, resolution);

    setPins(p)
}

void MotorControl::setPins(MotorPins p)
{
    ledcDetachPin(pins.right.forward);
    ledcDetachPin(pins.right.reverse);

    ledcDetachPin(pins.left.forward);
    ledcDetachPin(pins.left.reverse);

    pins = p;

    ledcAttachPin(pins.right.forward, channel);
    ledcAttachPin(pins.right.reverse, channel);

    ledcAttachPin(pins.left.forward, channel);
    ledcAttachPin(pins.left.reverse, channel);
}

void MotorControl::setRightSpeed(int speed)
{
    
}
