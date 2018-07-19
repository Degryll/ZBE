#include "gtest/gtest.h"

#include <cstdio>

#include "ZBE/SDL/tools/SDLTimer.h"
#include "ZBE/core/system/SysError.h"

inline void halfTimeTest(zbe::SDLTimer *t1, zbe::SDLTimer *t2, zbe::SDLTimer *t3) {
  const int delay = 100;

  t1->start();
  EXPECT_TRUE(t1->isRunning());
  t2->start();

  SDL_Delay(delay);

  t2->stop();

  EXPECT_EQ(t1->lapTime(), t2->totalTime());
  EXPECT_TRUE(t1->isRunning());
  EXPECT_FALSE(t2->isRunning());

  t3->start();

  SDL_Delay(delay);

  t3->stop();

  EXPECT_EQ(t1->lapTime(), t3->totalTime());
  EXPECT_TRUE(t1->isRunning());

  t2->start();

  SDL_Delay(delay);

  t2->stop();
  t1->stop();
  EXPECT_FALSE(t1->isRunning());

  EXPECT_EQ(t1->totalTime(),t2->totalTime() + t3->totalTime()) << "Take elapsed times.";
}

TEST (SDLTimer, create) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::SDLTimer *timer = new zbe::SDLTimer(false);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Create Timer.";

  delete timer;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Delete Timer.";
}

TEST (SDLTimer, usage) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::SDLTimer timer1(false);
  zbe::SDLTimer timer2(false);
  zbe::SDLTimer timer3(false);

  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Create Timers.";

  halfTimeTest(&timer1, &timer2, &timer3);

  EXPECT_NE(0u,timer1.totalTime()) << "Timer1 elapsed time.";
  EXPECT_NE(0u,timer2.totalTime()) << "Timer2 elapsed time.";
  EXPECT_NE(0u,timer3.totalTime()) << "Timer3 elapsed time.";

  timer1.reset();
  timer2.reset();
  timer3.reset();

  EXPECT_EQ(0u,timer1.totalTime()) << "Reset Timer1.";
  EXPECT_EQ(0u,timer2.totalTime()) << "Reset Timer2.";
  EXPECT_EQ(0u,timer3.totalTime()) << "Reset Timer3.";

  halfTimeTest(&timer1, &timer2, &timer3);

}




