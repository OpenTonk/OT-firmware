#ifndef MotorControl_h
#define MotorControl_h

struct Right
{
    int forward;
    int reverse;
};

struct Left
{
    int forward;
    int reverse;
};

struct MotorPins
{
    Right right;
    Left left;
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
};

#endif