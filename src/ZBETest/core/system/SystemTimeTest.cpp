#include "gtest/gtest.h"

#include "ZBE/core/system/SystemTime.h"
#include "ZBE/core/tools/Timer.h"

class DummyTimer : public zbe::Timer {
  public:
    DummyTimer():time(0),meter(0){
    }

    void start() {
    }

    uint64_t stop() {
    }

    void reset() {
      time = 0;
      meter = 0;
    }

    uint64_t lapTime() {
      uint64_t local = (meter % 2)+1;
      time += local;
      meter++;
      return local;
    }

    uint64_t totalTime() {
      return time;
    }

    bool running() {return true;}
    uint64_t time;
    uint64_t meter;
};

TEST(SystemTime, SystemTime) {
  zbe::SystemTime st = zbe::SystemTime::getInstance();
  zbe::Timer *t = new DummyTimer();
  st.setSystemTimer(t);
  uint64_t f1 = st.getFrameTime();
  uint64_t t1 = st.getFrameTime();
  uint64_t f2 = st.getFrameTime();
  uint64_t t2 = st.getFrameTime();
  st.update();
  uint64_t f3 = st.getFrameTime();
  uint64_t t3 = st.getFrameTime();

  EXPECT_EQ(f1,t1) << "For first frame, total and frame are the same";
  EXPECT_EQ(t1,t2) << "No frame changes without update call";
  EXPECT_EQ(f1,f2) << "No total changes without update call";
  EXPECT_GT(f3,f2) << "After update, total must advance";
  EXPECT_GT(t3,t2) << "After update, frame must advance";
}
