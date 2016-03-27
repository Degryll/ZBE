#include "gtest/gtest.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/daemons/DaemonMaster.h"

//Dummy Daemon implementation. Just for test purposes.
class DaemonTestImp : public zbe::Daemon{
  public:
    DaemonTestImp(bool &call) : called(call) {}

    virtual ~DaemonTestImp(){
      called = false;
    }

    virtual void run(){
      called = true;
    }

  private:
    bool &called;
};

TEST(Daemon, DaemonTestImpTest) {
  bool call = false;
  zbe::Daemon *d = new DaemonTestImp(call);
  EXPECT_FALSE(call) << "Nothing executed";
  d->run();
  EXPECT_TRUE(call) << "Daemon called";
  delete d;
  EXPECT_FALSE(call) << "Daemon deleted";
}

TEST(Daemon, DaemonMaster) {
  bool call1 = false;
  bool call2 = false;
  bool call3 = false;
  zbe::DaemonMaster * master = new zbe::DaemonMaster();
  zbe::Daemon * d = new DaemonTestImp(call1);
  master->addDaemon(d);
  d = new DaemonTestImp(call2);
  master->addDaemon(d);
  d = new DaemonTestImp(call3);
  master->addDaemon(d);
  master->run();
  EXPECT_TRUE(call1) << "daemon 1 called";
  EXPECT_TRUE(call2) << "daemon 2 called";
  EXPECT_TRUE(call3) << "daemon 3 called";
  delete master;
  EXPECT_FALSE(call1) << "daemon 1 deleted";
  EXPECT_FALSE(call2) << "daemon 2 deleted";
  EXPECT_FALSE(call3) << "daemon 3 deleted";
}
