#include "gtest/gtest.h"

#include <forward_list>

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/daemons/PunisherDaemon.h"
#include "ZBE/core/daemons/Punishers.h"

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/drawers/Drawer.h"

#include "ZBE/core/tools/containers/ListManager.h"

namespace Punishers {

class MockEntity {
  public:
    MockEntity():data(0){}
    int data;
};

class MockPunish {
  public:
    void apply(MockEntity * e) { e->data = 1; };
};

class MockBehavior: public zbe::Behavior<MockEntity> {
  public:
    void apply(MockEntity * e) { e->data = 2; };
};

class MockDrawer: public zbe::Drawer<MockEntity> {
  public:
    void apply(MockEntity * e) { e->data = 3; };
};

TEST(Punishers, PunisherDaemon) {
    MockEntity a,b,c,d;
    zbe::ListManager<std::forward_list<MockEntity*> > & lm =zbe::ListManager<std::forward_list<MockEntity*> >::getInstance();
    lm.insert(0,new std::forward_list<MockEntity*>());
    lm.insert(1,new std::forward_list<MockEntity*>());
    std::forward_list<MockEntity*> * eList0 = lm.get(0);
    std::forward_list<MockEntity*> * eList1 = lm.get(1);
    eList0->push_front(&a);
    eList0->push_front(&b);
    eList1->push_front(&c);
    eList1->push_front(&d);
    zbe::Daemon* daemon = new zbe::PunisherDaemon<MockPunish,std::forward_list<MockEntity*> >(new MockPunish, 0);
    daemon->run();
    EXPECT_EQ(1, a.data) << "a must has been punished";
    EXPECT_EQ(1, b.data) << "b must has been punished";
    EXPECT_EQ(0, c.data) << "c must has not been punished";
    EXPECT_EQ(0, d.data) << "d must has not been punished";
    delete eList0;
    delete eList1;
}

TEST(Punishers, BehaviorDaemon) {
    MockEntity a,b,c,d;
    zbe::ListManager<std::forward_list<MockEntity*> > & lm =zbe::ListManager<std::forward_list<MockEntity*> >::getInstance();
    lm.insert(0,new std::forward_list<MockEntity*>());
    lm.insert(1,new std::forward_list<MockEntity*>());
    std::forward_list<MockEntity*> * eList0 = lm.get(0);
    std::forward_list<MockEntity*> * eList1 = lm.get(1);
    eList0->push_front(&a);
    eList0->push_front(&b);
    eList1->push_front(&c);
    eList1->push_front(&d);
    zbe::Daemon* daemon = new zbe::BehaviorDaemon<MockEntity, std::forward_list<MockEntity*> >(new MockBehavior, 0);
    daemon->run();
    EXPECT_EQ(2, a.data) << "a must has been punished";
    EXPECT_EQ(2, b.data) << "b must has been punished";
    EXPECT_EQ(0, c.data) << "c must has not been punished";
    EXPECT_EQ(0, d.data) << "d must has not been punished";
    delete eList0;
    delete eList1;
} //BehaviorDaemon //DrawerDaemon

TEST(Punishers, DrawerDaemon) {
    MockEntity a,b,c,d;
    zbe::ListManager<std::forward_list<MockEntity*> > & lm =zbe::ListManager<std::forward_list<MockEntity*> >::getInstance();
    lm.insert(0,new std::forward_list<MockEntity*>());
    lm.insert(1,new std::forward_list<MockEntity*>());
    std::forward_list<MockEntity*> * eList0 = lm.get(0);
    std::forward_list<MockEntity*> * eList1 = lm.get(1);
    eList0->push_front(&a);
    eList0->push_front(&b);
    eList1->push_front(&c);
    eList1->push_front(&d);
    zbe::Daemon* daemon = new zbe::DrawerDaemon<MockEntity, std::forward_list<MockEntity*> >(new MockDrawer, 0);
    daemon->run();
    EXPECT_EQ(3, a.data) << "a must has been punished";
    EXPECT_EQ(3, b.data) << "b must has been punished";
    EXPECT_EQ(0, c.data) << "c must has not been punished";
    EXPECT_EQ(0, d.data) << "d must has not been punished";
    delete eList0;
    delete eList1;
}

}

