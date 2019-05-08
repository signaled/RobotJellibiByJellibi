#ifndef __DRIVE_H__
#define __DRIVE_H__
#include "Wheel.h"

class Drive
{
private:


    Wheel _rightWheel;
    Wheel _leftWheel;  
public:
    Drive();
    void Init(int rightPwmPin, 
              int rightDirPin, 
              int leftPmwPin, 
              int leftDirPin);
    void Stop();
    void Go();  
    void Back();
    void Left();
    void Right();
    void Nothing();
};

#endif//__DRIVE_H__