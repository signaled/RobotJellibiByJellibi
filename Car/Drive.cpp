#include "Drive.h"

Drive::Drive()
{  
}

void Drive::Init(int rightPwmPin, 
                 int rightDirPin, 
                 int leftPmwPin, 
                 int leftDirPin)
{
    _rightWheel.Init(rightPwmPin, 
                     rightDirPin, true);
    _leftWheel.Init(leftPmwPin, 
                    leftDirPin, false);
    Stop();
}

void Drive::Stop()
{
    _rightWheel.Stop();
    _leftWheel.Stop();

}

void Drive::Go()
{
    _rightWheel.Up();
    _leftWheel.Up();
}

void Drive::Back()
{
    _rightWheel.Down();
    _leftWheel.Down();
}

void Drive::Left()
{
    _leftWheel.Gain();
    _rightWheel.Normal();
}

void Drive::Right()
{
    _rightWheel.Gain();
    _leftWheel.Normal();
}

void Drive::Nothing()
{
    _leftWheel.Normal();
    _rightWheel.Normal();
}
