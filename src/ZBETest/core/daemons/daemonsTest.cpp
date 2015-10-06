#include "gtest/gtest.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/daemons/DaemonMaster.h"

//Dummy Daemon implementation. Just for test purposes.
class DaemonTestImp : public zbe::Daemon{
  public:
    DaemonTestImp(bool & call):called(call){
    }
    virtual ~DaemonTestImp(){
      called = false;
    }

    virtual void run(){
      called = true;
    }

  private:
    bool & called;
};

TEST(Daemon, Base) {
  bool call = false;
  zbe::Daemon * d = new DaemonTestImp(call);
  d->run();
  ASSERT_TRUE(call) << "Daemon called";
  delete d;
  ASSERT_FALSE(call) << "Daemon deleted";
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
  ASSERT_TRUE(call1);
  ASSERT_TRUE(call2);
  ASSERT_TRUE(call3) << "All daemons called";
  delete master;
  ASSERT_FALSE(call1);
  ASSERT_FALSE(call2);
  ASSERT_FALSE(call3) << "All daemons deleted";
}
