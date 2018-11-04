#include "gtest/gtest.h"

#include <forward_list>

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/daemons/PunisherDaemon.h"
#include "ZBE/core/daemons/Punishers.h"

#include "ZBE/core/behaviors/Behavior.h"

#include "ZBE/core/tools/containers/RsrcStore.h"

namespace Punishers {

class MockEntity {
  public:
    MockEntity() : data(0){}
    int data;
};

class MockPunish {
  public:
    void apply(MockEntity * me) { me->data = 1; };
};

class MockTimedPunish {
  public:
    void apply(MockEntity * me, int64_t) { me->data = 2; };
};


TEST(PunisherDaemon, PunisherDaemon) {
    EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initialy no errors.";
    MockEntity a,b,c,d;
    zbe::RsrcStore<std::forward_list<MockEntity*> > & lm =zbe::RsrcStore<std::forward_list<MockEntity*> >::getInstance();
    lm.insert(2, std::make_shared<std::forward_list<MockEntity*> >());
    lm.insert(1, std::make_shared<std::forward_list<MockEntity*> >());
    std::shared_ptr<std::forward_list<MockEntity*> > eList2 = lm.get(2);
    std::shared_ptr<std::forward_list<MockEntity*> > eList1 = lm.get(1);
    eList2->push_front(&a);
    eList2->push_front(&b);
    eList1->push_front(&c);
    eList1->push_front(&d);
    zbe::Daemon* daemon = new zbe::PunisherDaemon<MockPunish, std::forward_list<MockEntity*> >(std::make_shared<MockPunish>(), lm.get(2));
    daemon->run();
    EXPECT_EQ(1, a.data) << "a must has been punished";
    EXPECT_EQ(1, b.data) << "b must has been punished";
    EXPECT_EQ(0, c.data) << "c must has not been punished";
    EXPECT_EQ(0, d.data) << "d must has not been punished";

    EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Finaly no errors.";
}

}  // namespace Punishers
