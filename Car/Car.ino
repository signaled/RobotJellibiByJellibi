#include <JellibiButton.h>
#include <JellibiPin.h>
#define HC06BAUDRATE 9600
#include "Drive.h"
#include "ServoAction.h"
#include "ActionRecorder.h"

ServoAction _grip;
Drive _drive;
ActionRecorder _rec;

bool _bReplay = false;
bool _bRec = false;

JellibiButton _recButton;
JellibiButton _repButton;
JellibiPin _pin;

void LedControl() {
  digitalWrite(_pin.Led(L), (_bRec)?HIGH:LOW);
  digitalWrite(_pin.Led(R), (_bReplay)?HIGH:LOW);
}

void ModeSetup(unsigned long lCurTime) {
  if (_repButton.Check()) { // Toggle ReplayMode
    if (_bReplay ) {
      _bReplay = false;
    } else {
      if (_bRec) {
        
      } else {
        _bReplay = true;
        _drive.Stop();
        _rec.StartRep(lCurTime);
      }
    }
  }
  if (_recButton.Check()) { // Toggle Rec
    if( _bRec ) {
      _bRec = false;
    } else {
      if (_bReplay) {
        
      } else {
        _bRec = true;
        _drive.Stop();
        _rec.StartRec(lCurTime);
      }
    }
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(HC06BAUDRATE);
  _drive.Init(_pin.Wheel(R), _pin.WheelDir(R), 
              _pin.Wheel(L), _pin.WheelDir(L));
  _grip.Init();
  _repButton.Init(_pin.Button(U), false);
  _recButton.Init(_pin.Button(D), false);

  pinMode(_pin.Led(R), OUTPUT);
  pinMode(_pin.Led(L), OUTPUT);
  digitalWrite(_pin.Led(R), LOW);
  digitalWrite(_pin.Led(L), LOW);
  Serial.print("Hello\n");
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long cur = millis();
  uint8_t btCmd = 0;
  ModeSetup(cur);
  LedControl();
  
  if (_bReplay) {
    if (!_rec.GetRep(cur, &btCmd)){
      _bReplay = false;
    }
  } else {
    if(Serial.available()>0)
    {
      btCmd = Serial.read();
      if (_bRec) {
        if (!_rec.Rec(cur, btCmd)) {
          _bRec = false;
        }
      }
    }    
  }
  
  switch(btCmd)
  {
    case 'U':
    case 'u':
      _drive.Go();
      break;
    case 'R':
    case 'r': 
      _drive.Right();
      break;
    case 'D':
    case 'd':
      _drive.Back();
      break;
    case 'L':
    case 'l':
      _drive.Left();
      break;
    case 'S':
    case 's':
      _drive.Stop();
      break;
    case 'C':
    case 'c':
      _grip.OpenGrip();
      break;
    case 'e':
    case 'E':
      _grip.Grip();
      break;
    case 'a':
    case 'A':
      _grip.LiftGrip();
      break;
    case 'B':
    case 'b':
      _grip.DownGrip();
      break;
    case 'X':
    case 'x':
      _drive.Nothing();
    default:
    break;
  }
}
