#include "Wheel.h"

Wheel::Wheel()
: _pwmPin(0)
, _dirPin(0)
, _bRightWheel(true)
, _nPwm(0)
, _bForward(true)
{
}

void Wheel::Init(int pwmPin, int dirPin, bool bRightWheel) 
{
    _pwmPin = pwmPin;
    _dirPin = dirPin;
    _bRightWheel = bRightWheel;
    pinMode(_pwmPin, OUTPUT);
    pinMode(_dirPin, OUTPUT);
    
    Stop();
}

int32_t Wheel::GetDirection()
{
    if (_bRightWheel) {
        if (_bForward) 
            return LOW;
        else 
            return HIGH;
    }
    else {
        if (_bForward)
            return HIGH;
        else
            return LOW;
    }
}

void Wheel::Apply() 
{
    digitalWrite(_dirPin, GetDirection());

    if ( _nGain == 0) {
        analogWrite( _pwmPin, _nPwm);
    } else {
    
        if ( (_nPwm - _nGain) < _MIN_PWM_) {
            analogWrite( _pwmPin, _MIN_PWM_);
        } else {
            analogWrite( _pwmPin, _nPwm - _nGain);
        }
    }
}

void Wheel::Stop()
{
    _nGain = 0;
    _nPwm = _STOP_PWM_;
    Apply();
}
void Wheel::Up()
{
    if (_bForward) {
        if (_nPwm < _MIN_PWM_) {
          _nPwm = _MIN_PWM_;
        } else {
          _nPwm += _STEP_PWM_;
        }
        if (_nPwm > _MAX_PWM_) {
            _nPwm = _MAX_PWM_;
        }
    } else {
        _nPwm -= _STEP_PWM_;
        if (_nPwm < _MIN_PWM_){
            _nPwm = _STOP_PWM_;
            _bForward = true;
        }
    }
   Apply();
}
void Wheel::Down()
{
    if (_bForward) {
        _nPwm -= _STEP_PWM_;
        if (_nPwm < _MIN_PWM_) {
            _nPwm = _STOP_PWM_;
            _bForward = false;
        }
    } else {
        if (_nPwm < _MIN_PWM_){
          _nPwm = _MIN_PWM_;
        } else {
          _nPwm += _STEP_PWM_;
        }
        if (_nPwm > _MAX_PWM_) {
            _nPwm = _MAX_PWM_;
        }
    }
    Apply();
}


void Wheel::Gain() 
{
    _nGain += _STEP_PWM_;
    if (_nGain + _MIN_PWM_ > _nPwm) {
        _nGain -= _STEP_PWM_;
    }
    Apply();
}
void Wheel::Normal()
{
    if (_nGain > _STEP_PWM_) {
        _nGain -= _STEP_PWM_;
        if (_nGain < 0) 
            _nGain = 0;
    }
    Apply();
}
