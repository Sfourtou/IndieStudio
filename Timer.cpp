#include "Timer.h"

Timer::Timer()
   : pause(false)
{
   gettimeofday(&t0, 0);
   gettimeofday(&t1, 0);
}

Timer::~Timer()
{
}

void Timer::startTime()
{
  gettimeofday(&t0, 0);
  gettimeofday(&t1, 0);
}

int Timer::getTimeElapsed()
{
  struct timeval result;

  gettimeofday(&t1, 0);
  timersub(&t1, &t0, &result);
  return (result.tv_usec);
}

int Timer::getTimeElapsedSec()
{
  struct timeval result;

  gettimeofday(&t1, 0);
  timersub(&t1, &t0, &result);

  return (result.tv_sec);
}

void Timer::resetTime()
{
  gettimeofday(&t0, 0);
}

void Timer::paused(bool new_pause)
{
  pause = new_pause;
}

bool Timer::isPaused()
{
  return (pause);
}
