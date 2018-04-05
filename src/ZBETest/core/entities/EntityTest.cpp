#include "gtest/gtest.h"

#include <cstdint>
#include <memory>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"
#include "ZBE/core/tools/containers/Ticket.h"

#include "ZBE/core/entities/Entity.h"


TEST(Entity, Tickets) {
  zbe::Entity *e = new zbe::Entity();

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

  e->setINACTIVE(2);
  e->setACTIVE(3);
  e->setERASED(4);

  EXPECT_EQ(zbe::Ticket::ACTIVE,  t1->getState()) << "Unmodified, still ACTIVE. - 1";
  EXPECT_EQ(zbe::Ticket::INACTIVE,t2->getState()) << "Changed to INACTIVE. - 2";
  EXPECT_EQ(zbe::Ticket::ACTIVE,  t3->getState()) << "Unmodified, changed to the same state, ACTIVE. - 3";
  EXPECT_EQ(zbe::Ticket::ERASED,  t4->getState()) << "Changed to ERASED. - 4";

  e->setERASED(1);
  e->setACTIVE(2);
  e->setINACTIVE(3);

  EXPECT_EQ(zbe::Ticket::ERASED,  t1->getState()) << "Changed to ERASED. - 1";
  EXPECT_EQ(zbe::Ticket::ACTIVE,  t2->getState()) << "Changed to ACTIVE. - 2";
  EXPECT_EQ(zbe::Ticket::INACTIVE,t3->getState()) << "Changed to INACTIVE. - 3";
  EXPECT_EQ(zbe::Ticket::ERASED,  t4->getState()) << "Unmodified, still ERASED. - 4";

  delete e;

  EXPECT_EQ(zbe::Ticket::ERASED,t1->getState()) << "Unmodified, destructor put as ERASED but already set as ERASED. - 1";
  EXPECT_EQ(zbe::Ticket::ERASED,t2->getState()) << "Destructor put as ERASED. - 2";
  EXPECT_EQ(zbe::Ticket::ERASED,t3->getState()) << "Destructor put as ERASED. - 3";
  EXPECT_EQ(zbe::Ticket::ERASED,t4->getState()) << "Unmodified, destructor put as ERASED but already set as ERASED. - 4";
}

TEST(Entity, Tickets_Error) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initialy no errors.";

  zbe::Entity e;

  e.setACTIVE(42);

  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Try to change the state of a missing ticket.";

  zbe::SysError::clear();

  std::shared_ptr<zbe::TicketedElement<int> > t1 = std::make_shared<zbe::TicketedElement<int> >(std::make_shared<int>(1));
  e.addToList(42, t1);

  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Access a valid Ticket.";

  e.setACTIVE(1);

  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Access an invalid Ticket.";

  zbe::SysError::clear();
}

TEST(Entity, values) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initialy no errors.";

  zbe::Entity e;
  std::shared_ptr<zbe::Value<double> >  vald1 = std::make_shared<zbe::SimpleValue<double> >(0.0);
  std::shared_ptr<zbe::Value<double> >  vald2 = std::make_shared<zbe::SimpleValue<double> >(1.0);
  std::shared_ptr<zbe::Value<uint64_t> >  valu1 = std::make_shared<zbe::SimpleValue<uint64_t> >(42);
  std::shared_ptr<zbe::Value<uint64_t> >  valu2 = std::make_shared<zbe::SimpleValue<uint64_t> >(37);
  std::shared_ptr<zbe::Value<int64_t> >  vali1 = std::make_shared<zbe::SimpleValue<int64_t> >(-1);
  std::shared_ptr<zbe::Value<int64_t> >  vali2 = std::make_shared<zbe::SimpleValue<int64_t> >(3);

  e.setDouble(0, vald1);
  e.setDouble(1, vald2);

  e.setUint(0, valu1);
  e.setUint(1, valu2);

  e.setInt(0, vali1);
  e.setInt(1, vali2);

  EXPECT_DOUBLE_EQ(0.0,  e.getDouble(0)->getValue()) << "First double value is 0.0.";
  EXPECT_DOUBLE_EQ(1.0,  e.getDouble(1)->getValue()) << "Second double value is 1.0";
  EXPECT_EQ(42, e.getUint(0)->getValue()) << "First uint value is 42.";
  EXPECT_EQ(37, e.getUint(1)->getValue()) << "Second uint value is 37";
  EXPECT_EQ(-1, e.getInt(0)->getValue()) << "First int value is -1.";
  EXPECT_EQ(3, e.getInt(1)->getValue()) << "Second int value is 3";


  e.getDouble(0)->setValue(-3.0);
  valu1->setValue(84);
  auto v = e.getInt(1);
  v->setValue(-30);

  EXPECT_DOUBLE_EQ(-3.0,  e.getDouble(0)->getValue()) << "First double value now is -3.0.";
  EXPECT_EQ(84, e.getUint(0)->getValue()) << "First uint value now is 84.";
  EXPECT_EQ(-30, e.getInt(1)->getValue()) << "First uint value now is -30.";

  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "No error ocurred.";

  zbe::SysError::clear();
}
