#include <JellibiPin.h>

#include <JellibiButton.h>

#define HC06BAUDRATE 9600

JellibiPin _p;
unsigned long _lSleep = 0;
bool _bDrive = true;

void setup() {
  // put your setup code here, to run once:
  pinMode(_p.Button(U), INPUT);
  pinMode(_p.Button(D), INPUT);
  pinMode(_p.Button(R), INPUT);
  pinMode(_p.Button(L), INPUT);
  Serial.begin(HC06BAUDRATE);
  // LED 
  pinMode(_p.Led(L), OUTPUT);
  pinMode(_p.Led(R), OUTPUT);
}
void UpdateLed(bool bWaitTime) {
  if (bWaitTime) {
    digitalWrite( _p.Led(L), HIGH);
    digitalWrite( _p.Led(R), HIGH);    
  } else {
    digitalWrite( _p.Led(L), (_bDrive)?LOW:HIGH);
    digitalWrite( _p.Led(R), (_bDrive)?HIGH:LOW);
  }
}
int BitCount( uint8_t btByte) 
{
    uint8_t bits = 0;
    while( btByte )
    {
        btByte = btByte & ( btByte - 1 ); 
        bits++;
    }
    return bits;
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long lTime = millis();
  uint8_t bButton = 0;
  if (LOW ==digitalRead(_p.Button(U))) {
    bButton |= 0x01;
  }
  if (LOW ==digitalRead(_p.Button(D))) {
    bButton |= 0x02;
  }
  if (LOW ==digitalRead(_p.Button(L))) {
    bButton |= 0x04;
  }
  if (LOW ==digitalRead(_p.Button(R))) {
    bButton |= 0x08;
  }
  if (BitCount(bButton) > 0)
    Serial.print("["+String(BitCount(bButton))+"]\n");
  if (BitCount(bButton) >= 2 && (_lSleep < lTime)) {
    if (_bDrive) {
      _bDrive = false;
    } else {
      _bDrive = true;
    }
    _lSleep = lTime + 1000; 
  }
  UpdateLed((lTime < _lSleep)?true:false);
  if ((lTime > _lSleep) && (BitCount(bButton)==1)) {
    // shot 
    if (_bDrive) {
      if (bButton & 0x01) {
        Serial.print("U");
      } else if (bButton & 0x02) {
        Serial.print("D");
      } else if (bButton & 0x04) {
        Serial.print("L");
      } else if (bButton & 0x08) {
        Serial.print("R");
      } else {
        Serial.print("X");
      }
    } else {
      if (bButton & 0x01) {
        Serial.print("A"); // lift up
      } else if (bButton & 0x02) {
        Serial.print("B"); // lift down
      } else if (bButton & 0x04) {
        Serial.print("C"); // open grip
      } else if (bButton & 0x08) {
        Serial.print("E"); // close grip
      } else {
        Serial.print("X"); // 
      }
    }
  } else {
    Serial.print("X");
  }
  delay(50);
}
