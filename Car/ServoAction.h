#ifndef __SERVO_ACTION_H__
#define __SERVO_ACTION_H__
#include <arduino.h>

#include <Servo.h>
class ServoAction
{
private:    const int _GRIP_PIN_ = 9; // SERVO 01 포트에 연결 된 핀(포트)    const int _LIFT_PIN_ = 2; // SERVO 02 포트에 연결 된 핀(포트)    const int32_t _STEP_ = 5;    const int32_t _MAX_ = 90;    const int32_t _MIN_ = 10;    int32_t _nGripAngle;    int32_t _nLiftAngle;    
  
  Servo _servoGrip;
  Servo _servoLift;
public:
  ServoAction();
  
  void Init();
  void OpenGrip();
  void Grip();
  void DownGrip();   void LiftGrip();
};

#endif//__SERVO_ACTION_H__