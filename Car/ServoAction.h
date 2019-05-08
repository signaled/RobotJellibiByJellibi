#ifndef __SERVO_ACTION_H__
#define __SERVO_ACTION_H__
#include <arduino.h>

#include <Servo.h>
class ServoAction
{
private:
  
  Servo _servoGrip;
  Servo _servoLift;
public:
  ServoAction();
  
  void Init();
  void OpenGrip();
  void Grip();
  void DownGrip();
};

#endif//__SERVO_ACTION_H__