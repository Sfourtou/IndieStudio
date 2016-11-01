#ifndef TIMER_HH_
#define TIMER_HH_

#include <sys/time.h>

class Timer
{
public:
  Timer();
  ~Timer();
private:
  struct timeval t0;
  struct timeval t1;
  bool pause;
public:
  void startTime();
  void resetTime();
  int getTimeElapsed();
  int getTimeElapsedSec();
  void paused(bool);
  bool isPaused();
};

#endif
