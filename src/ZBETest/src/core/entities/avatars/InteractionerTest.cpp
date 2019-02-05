#include "gtest/gtest.h"

#include <cstdint>
#include <memory>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"
#include "ZBE/core/tools/containers/Ticket.h"
#include "ZBE/core/tools/containers/TicketedElement.h"

#include "ZBE/core/entities/Entity.h"

namespace InteractionerTest {

TEST(Interactioner, usage) {
  zbe::Entity *e = new zbe::Entity();

  std::shared_ptr<zbe::TicketedElement<int> > t1 = std::make_shared<zbe::TicketedElement<int> >(std::make_shared<int>(1));
  std::shared_ptr<zbe::TicketedElement<int> > t2 = std::make_shared<zbe::TicketedElement<int> >(std::make_shared<int>(2));
  std::shared_ptr<zbe::TicketedElement<int> > t3 = std::make_shared<zbe::TicketedElement<int> >(std::make_shared<int>(3));
  std::shared_ptr<zbe::TicketedElement<int> > t4 = std::make_shared<zbe::TicketedElement<int> >(std::make_shared<int>(4));

  e->addTicket(1, t1);
  e->addTicket(2, t2);
  e->addTicket(3, t3);
  e->addTicket(4, t4);

  EXPECT_TRUE(t1->isACTIVE()) << "Add ticket, state ACTIVE by default. - 1";
  EXPECT_TRUE(t2->isACTIVE()) << "Add ticket, state ACTIVE by default. - 2";
  EXPECT_TRUE(t3->isACTIVE()) << "Add ticket, state ACTIVE by default. - 3";
  EXPECT_TRUE(t4->isACTIVE()) << "Add ticket, state ACTIVE by default. - 4";

  e->setINACTIVE(2);
  e->setACTIVE(3);
  e->setERASED(4);

  EXPECT_TRUE(t1->isACTIVE())   << "Unmodified, still ACTIVE. - 1";
  EXPECT_TRUE(t2->isINACTIVE()) << "Changed to INACTIVE. - 2";
  EXPECT_TRUE(t3->isACTIVE())   << "Unmodified, changed to the same state, ACTIVE. - 3";
  EXPECT_TRUE(t4->isERASED())   << "Changed to ERASED. - 4";

  e->setERASED(1);
  e->setACTIVE(2);
  e->setINACTIVE(3);

  EXPECT_TRUE(t1->isERASED())   << "Changed to ERASED. - 1";
  EXPECT_TRUE(t2->isACTIVE())   << "Changed to ACTIVE. - 2";
  EXPECT_TRUE(t3->isINACTIVE()) << "Changed to INACTIVE. - 3";
  EXPECT_TRUE(t4->isERASED())   << "Unmodified, still ERASED. - 4";

  delete e;

  EXPECT_TRUE(t1->isERASED()) << "Unmodified, destructor put as ERASED but already set as ERASED. - 1";
  EXPECT_TRUE(t2->isERASED()) << "Destructor put as ERASED. - 2";
  EXPECT_TRUE(t3->isERASED()) << "Destructor put as ERASED. - 3";
  EXPECT_TRUE(t4->isERASED()) << "Unmodified, destructor put as ERASED but already set as ERASED. - 4";
}

}  // namespace InteractionerTest
