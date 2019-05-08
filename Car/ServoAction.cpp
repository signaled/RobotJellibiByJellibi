#include "ServoAction.h"
ServoAction::ServoAction()
: _nGripAngle(90)
, _nLiftAngle(0)
{
}

void ServoAction::Init()
{
  _servoGrip.attach(_GRIP_PIN_);
  _servoLift.attach(_LIFT_PIN_);
  _servoGrip.write(_nGripAngle);
  _servoLift.write(_nLiftAngle);
}
void ServoAction::OpenGrip()
{
    _nGripAngle += _STEP_;
    if (_nGripAngle > _MAX_) {
        _nGripAngle = _MAX_;
    }
    _servoGrip.write(_nGripAngle);
    _servoLift.write(_nLiftAngle);  
}

void ServoAction::Grip()
{

    _nGripAngle -= _STEP_;
    if (_nGripAngle < _MIN_){
        _nGripAngle = _MIN_;
    }
        
    _servoGrip.write(_nGripAngle);
    _servoLift.write(_nLiftAngle);

}

void ServoAction::DownGrip()
{
    _nLiftAngle -= _STEP_;
    if (_nLiftAngle < _MIN_) {
        _nLiftAngle = _MIN_;
    }
    _servoGrip.write(_nGripAngle);
    _servoLift.write(_nLiftAngle);
}

void ServoAction::LiftGrip()
{
    _nLiftAngle += _STEP_;
    if (_nLiftAngle > _MAX_) {
        _nLiftAngle = _MAX_;
    }
    _servoGrip.write(_nGripAngle);
    _servoLift.write(_nLiftAngle);
}
