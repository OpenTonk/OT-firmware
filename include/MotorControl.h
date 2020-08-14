#ifndef MotorControl_h
#define MotorControl_h

struct MotorPins
{
    struct RightPins
    {
        int forward;
        int reverse;
    };

    struct LeftPins
    {
        int forward;
        int reverse;
    };

    RightPins right;
    LeftPins left;
};

class MotorControl
{
private:
    MotorPins pins;
    int channel;
    int frequency;
    int resolution;

public:
    MotorControl(MotorPins pins);
    void setPins(MotorPins pins);
    void setRightSpeed(int speed);
    void loop();
};

#endif