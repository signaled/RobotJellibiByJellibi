#ifndef __ACTION_RECORDER_H__
#define __ACTION_RECORDER_H__
#include <arduino.h>

#define _MAX_CMD_ 300

class ActionRecorder
{
public:
  uint16_t _lTime[_MAX_CMD_];
  uint8_t _btCmd[_MAX_CMD_];
  unsigned long _refTime;
  int _curRecIdx;
  int _curRepIdx;
public:
  ActionRecorder();
  
  void StartRec(unsigned long curTime);
  bool Rec(unsigned long curTime, unsigned char cmd/*INPUT*/);
  void StopRec();
  int StartRep(unsigned long curTime);
  bool GetRep(unsigned long curTime, unsigned char* cmd/*OUTPUT*/);
  unsigned StopRep();

  int GetCurItemCount();
};

#endif//__ACTION_RECORDER_H__
