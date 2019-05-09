#include "ActionRecorder.h"
  
ActionRecorder::ActionRecorder()
: _curRecIdx(0)
, _curRepIdx(0)
, _refTime(0)
{
}

void ActionRecorder::StartRec(unsigned long curTime)
{
  _refTime = curTime;
  _curRecIdx = 0;  
}

bool ActionRecorder::Rec(unsigned long curTime, unsigned char cmd)
{
  if (_curRecIdx > _MAX_CMD_) {
    if (Serial) {
      Serial.print("CurIdx Over\n");
    }
    return false;
  }
  _lTime[_curRecIdx] = uint16_t(curTime - _refTime);
  _btCmd[_curRecIdx] = cmd;
  _curRecIdx++;
  return true;
}

void ActionRecorder::StopRec()
{
  
}

int ActionRecorder::StartRep(unsigned long curTime)
{
  _refTime = curTime;  
  _curRepIdx = 0;
}

bool ActionRecorder::GetRep( unsigned long curTime, unsigned char* cmd)
{
  if ((_curRepIdx > _MAX_CMD_) || (_curRepIdx > _curRecIdx)) {
    return false;
  }
  
  unsigned char btRet = 0;
  uint16_t tgtTime = uint16_t(curTime - _refTime);
  uint16_t itemTime = _lTime[_curRepIdx];
  
  if (abs(itemTime - tgtTime) < 10  || (itemTime < tgtTime)) {
    btRet = _btCmd[_curRepIdx];
    _curRepIdx++;
  }
  *cmd = btRet;
  return true;
}

unsigned ActionRecorder::StopRep()
{

}

int ActionRecorder::GetCurItemCount()
{
  
}
