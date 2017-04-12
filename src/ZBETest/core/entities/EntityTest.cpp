#include "gtest/gtest.h"

#include <memory>

#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/tools/containers/Ticket.h"
#include "ZBE/core/system/SysError.h"

//Dummy Entity implementation. Just for test purposes.
class EntityTest : public zbe::Entity {
};

TEST(Entity, Usage) {
  EntityTest *e = new EntityTest;

  std::shared_ptr<zbe::TicketedElement<int> > t1 = std::make_shared<zbe::TicketedElement<int> >(std::make_shared<int>(1));
  std::shared_ptr<zbe::TicketedElement<int> > t2 = std::make_shared<zbe::TicketedElement<int> >(std::make_shared<int>(2));
  std::shared_ptr<zbe::TicketedElement<int> > t3 = std::make_shared<zbe::TicketedElement<int> >(std::make_shared<int>(3));
  std::shared_ptr<zbe::TicketedElement<int> > t4 = std::make_shared<zbe::TicketedElement<int> >(std::make_shared<int>(4));

  e->addToList(1, t1);
  e->addToList(2, t2);
  e->addToList(3, t3);
  e->addToList(4, t4);

  EXPECT_EQ(zbe::Ticket::ACTIVE,t1->getState()) << "Add ticket, state ACTIVE by default. - 1";
  EXPECT_EQ(zbe::Ticket::ACTIVE,t2->getState()) << "Add ticket, state ACTIVE by default. - 2";
  EXPECT_EQ(zbe::Ticket::ACTIVE,t3->getState()) << "Add ticket, state ACTIVE by default. - 3";
  EXPECT_EQ(zbe::Ticket::ACTIVE,t4->getState()) << "Add ticket, state ACTIVE by default. - 4";

  e->setState(2, zbe::Ticket::INACTIVE);
  e->setState(3, zbe::Ticket::ACTIVE);
  e->setState(4, zbe::Ticket::ERASED);

  EXPECT_EQ(zbe::Ticket::ACTIVE,t1->getState())   << "Unmodified, still ACTIVE. - 1";
  EXPECT_EQ(zbe::Ticket::INACTIVE,t2->getState()) << "Changed to INACTIVE. - 2";
  EXPECT_EQ(zbe::Ticket::ACTIVE,t3->getState())   << "Unmodified, changed to the same state, ACTIVE. - 3";
  EXPECT_EQ(zbe::Ticket::ERASED,t4->getState())   << "Changed to ERASED. - 4";

  e->setState(1, zbe::Ticket::ERASED);
  e->setState(2, zbe::Ticket::ACTIVE);
  e->setState(3, zbe::Ticket::INACTIVE);

  EXPECT_EQ(zbe::Ticket::ERASED,t1->getState())   << "Changed to ERASED. - 1";
  EXPECT_EQ(zbe::Ticket::ACTIVE,t2->getState())   << "Changed to ACTIVE. - 2";
  EXPECT_EQ(zbe::Ticket::INACTIVE,t3->getState()) << "Changed to INACTIVE. - 3";
  EXPECT_EQ(zbe::Ticket::ERASED,t4->getState())   << "Unmodified, still ERASED. - 4";

  delete e;

  EXPECT_EQ(zbe::Ticket::ERASED,t1->getState()) << "Unmodified, destructor put as ERASED but already set as ERASED. - 1";
  EXPECT_EQ(zbe::Ticket::ERASED,t2->getState()) << "Destructor put as ERASED. - 2";
  EXPECT_EQ(zbe::Ticket::ERASED,t3->getState()) << "Destructor put as ERASED. - 3";
  EXPECT_EQ(zbe::Ticket::ERASED,t4->getState()) << "Unmodified, destructor put as ERASED but already set as ERASED. - 4";
}

TEST(Entity, MissUsage) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initialy no errors.";

  EntityTest *e = new EntityTest;

  e->setState(42, zbe::Ticket::ACTIVE);

  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Try to change the state of a missing ticket.";

  zbe::SysError::clear();

  std::shared_ptr<zbe::TicketedElement<int> > t1 = std::make_shared<zbe::TicketedElement<int> >(std::make_shared<int>(1));
  e->addToList(42, t1);

  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Access a valid Ticket.";

  e->setState(1, zbe::Ticket::ACTIVE);

  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Access an invalid Ticket.";

  zbe::SysError::clear();
}
