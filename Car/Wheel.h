#ifndef __WHEEL_H__
#define __WHEEL_H__
#include <arduino.h>

class Wheel
{
private:
  int _pwmPin;
  int _dirPin;
  bool _bRightWheel;
  const int _STOP_PWM_ = 0;
  const int32_t _MIN_PWM_ = 40;
  const int32_t _STEP_PWM_ = 10;
  const int32_t _MAX_PWM_ = 180;

    bool _bForward;
    int32_t _nPwm;
    int32_t GetDirection();
    void Apply();
    int32_t _nGain;
public:
  Wheel();
  void Init(int pwmPin, int dirPin, bool bRightWheel);
  void Stop();

  void Up();
  void Down();
  void Gain();
  void Normal();
};

#endif//__WHEEL_H__
