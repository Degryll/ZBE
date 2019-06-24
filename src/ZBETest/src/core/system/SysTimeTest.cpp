#include "gtest/gtest.h"

#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/tools/time/Timer.h"

class DummyTimer : public zbe::Timer {
  public:
    DummyTimer():time(0),meter(0){
    }

    void start() {
    }

    int64_t stop() {
      return 0;
    }

    void reset() {
      time = 0;
      meter = 0;
    }

    int64_t lapTime() {
      int64_t local = (meter % 2)+1;
      time += local;
      meter++;
      return local;
    }

    int64_t totalTime() {
      return time;
    }

    bool isRunning() {return true;}
    int64_t time;
    int64_t meter;
};

TEST(SysTime, DISABLED_SysTime) {
  std::shared_ptr<zbe::SysTime> st = zbe::SysTime::getInstance();
  auto t = std::make_shared<DummyTimer>();
  st->setSystemTimer(t);
  int64_t f1 = st->getFrameTime();
  int64_t t1 = st->getFrameTime();
  int64_t f2 = st->getFrameTime();
  int64_t t2 = st->getFrameTime();
  st->update();
  int64_t f3 = st->getFrameTime();
  int64_t t3 = st->getFrameTime();

  EXPECT_EQ(f1,t1) << "For first frame, total and frame are the same";
  EXPECT_EQ(t1,t2) << "No frame changes without update call";
  EXPECT_EQ(f1,f2) << "No total changes without update call";
  EXPECT_GT(f3,f2) << "After update, total must advance";
  EXPECT_GT(t3,t2) << "After update, frame must advance";
}
