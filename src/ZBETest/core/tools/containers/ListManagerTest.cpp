#include "gtest/gtest.h"

#include "ZBE/core/tools/containers/ListManager.h"
#include "ZBE/core/system/SysError.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"

TEST(ListManager, Usage) {
  zbe::ListManager< zbe::TicketedForwardList<int> >& lm = zbe::ListManager< zbe::TicketedForwardList<int> >::getInstance();

  zbe::TicketedForwardList<int> *l1 = new zbe::TicketedForwardList<int>();
  zbe::TicketedForwardList<int> *l2 = new zbe::TicketedForwardList<int>();
  zbe::TicketedForwardList<int> *l3 = new zbe::TicketedForwardList<int>();
  zbe::TicketedForwardList<int> *l4 = new zbe::TicketedForwardList<int>();

  lm.insert( 42u, l1);
  lm.insert( 37u, l2);
  lm.insert( 17u, l3);
  lm.insert(314u, l4);

  EXPECT_EQ(l1,lm.get( 42u)) << "Add List Id. -  42";
  EXPECT_EQ(l2,lm.get( 37u)) << "Add List Id. -  37";
  EXPECT_EQ(l3,lm.get( 17u)) << "Add List Id. -  17";
  EXPECT_EQ(l4,lm.get(314u)) << "Add List Id. - 314";

  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initialy no errors.";
  EXPECT_EQ(0,lm.get(3u)) << "Access an invalid id, return list 0.";
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Error rise for accessing an invalid list.";

  zbe::SysError::clear();
}
