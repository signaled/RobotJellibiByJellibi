#include <JellibiPin.h>
#define HC06BAUDRATE 9600
#include "Drive.h"
#include "ServoAction.h"
ServoAction _grip;
Drive _drive;
JellibiPin _pin;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(HC06BAUDRATE);
  _drive.Init(_pin.Wheel(R), _pin.WheelDir(R), 
              _pin.Wheel(L), _pin.WheelDir(L));
  _grip.Init();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0)
  {
    char cRead = Serial.read();
    Serial.write(cRead);
    
    switch(cRead)
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
        Serial.print("\nUnknown\n");
    }
  }
}
