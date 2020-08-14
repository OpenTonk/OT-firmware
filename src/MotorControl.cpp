#include <Arduino.h>

#include "MotorControl.h"

#define RIGHT_FORWARD 0
#define RIGHT_REVERSE 1

#define LEFT_FORWARD 2
#define LEFT_REVERSE 3


MotorControl::MotorControl(MotorPins p)
{
    frequency = 50000;
    resolution = 8;

    config = {
        {100, -100, 10, 0, 0}, // right
        {100, -100, 10, 0, 0}    // left
    };

    firstLoop = true;

    ledcSetup(RIGHT_FORWARD, frequency, resolution);
    ledcSetup(RIGHT_REVERSE, frequency, resolution);
    ledcSetup(LEFT_FORWARD, frequency, resolution);
    ledcSetup(LEFT_REVERSE, frequency, resolution);

    setPins(p);
}

void MotorControl::setPins(MotorPins p)
{
    ledcDetachPin(pins.right.forward);
    ledcDetachPin(pins.right.reverse);

    ledcDetachPin(pins.left.forward);
    ledcDetachPin(pins.left.reverse);

    pins = p;

    ledcAttachPin(pins.right.forward, RIGHT_FORWARD);
    ledcAttachPin(pins.right.reverse, RIGHT_REVERSE);

    ledcAttachPin(pins.left.forward, LEFT_FORWARD);
    ledcAttachPin(pins.left.reverse, LEFT_REVERSE);
}

void MotorControl::setRightSpeed(int speed)
{
    if (speed < config.right.minSpeed)
    {
        config.right.targetSpeed = config.right.minSpeed;
    }
    else if (speed > config.right.maxSpeed)
    {
        config.right.targetSpeed = config.right.maxSpeed;
    }
    else
    {
        config.right.targetSpeed = speed;
    }
}

void MotorControl::setLeftSpeed(int speed)
{
    if (speed < config.left.minSpeed)
    {
        config.left.targetSpeed = config.left.minSpeed;
    }
    else if (speed > config.left.maxSpeed)
    {
        config.left.targetSpeed = config.left.maxSpeed;
    }
    else
    {
        config.left.targetSpeed = speed;
    }
}

void MotorControl::loop()
{
    if (firstLoop)
    {
        oldTime = millis() - 10;
        firstLoop = false;
    }
    else
    {
        oldTime = currentTime;
    }

    currentTime = millis();
    dt = (currentTime - oldTime) / 1000.0;

    //
    // Right 
    //
    if (config.right.currentSpeed < config.right.targetSpeed)
    {
        config.right.currentSpeed += dt * config.right.accel;
    }
    else
    {
        config.right.currentSpeed -= dt * config.right.accel;
    }

    if (config.right.currentSpeed > 0)
    {
        ledcWrite(RIGHT_REVERSE, 0);
        ledcWrite(RIGHT_FORWARD, config.right.currentSpeed / 100 * 255);
    }
    else
    {
        ledcWrite(RIGHT_FORWARD, 0);
        ledcWrite(RIGHT_REVERSE, config.right.currentSpeed / 100 * 255);
    }


    //
    // Left 
    //
    if (config.left.currentSpeed < config.left.targetSpeed)
    {
        config.left.currentSpeed += dt * config.left.accel;
    }
    else
    {
        config.left.currentSpeed -= dt * config.left.accel;
    }

    if (config.left.currentSpeed > 0)
    {
        ledcWrite(LEFT_REVERSE, 0);
        ledcWrite(LEFT_FORWARD, config.left.currentSpeed / 100 * 255);
    }
    else
    {
        ledcWrite(LEFT_FORWARD, 0);
        ledcWrite(LEFT_REVERSE, config.left.currentSpeed / 100 * 255);
    }

    Serial.print("Left: ");
    Serial.print(config.left.currentSpeed / 100 * 255);
    Serial.print(" | Right: ");
    Serial.println(config.right.currentSpeed / 100 * 255);
}
