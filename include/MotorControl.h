#ifndef MotorControl_h
#define MotorControl_h

struct MotorPins
{
    struct Motor
    {
        int forward;
        int reverse;
    };

    Motor right;
    Motor left;
};

struct MotorConfig
{
    struct MotorProps
    {
        float maxSpeed;
        float minSpeed;
        float accel;
        float targetSpeed;
        float currentSpeed;
    };

    MotorProps right;
    MotorProps left;
};

class MotorControl
{
private:
    MotorPins pins;
    MotorConfig config;
    int frequency;
    int resolution;

    int oldTime;
    int currentTime;
    float dt;
    bool firstLoop;

public:
    MotorControl(MotorPins pins);
    void setPins(MotorPins pins);
    void setRightSpeed(int speed);
    void setLeftSpeed(int speed);
    void loop();
};

#endif