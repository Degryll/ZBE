#include "gtest/gtest.h"

#include <cstdio>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/containers/TicketedForwardList.h"

TEST(TicketedForwardList, IterationTicketedElements) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::TicketedForwardList<int> l;
  std::shared_ptr<zbe::TicketedElement<int> > t2 = l.push_front(std::make_shared<int>(2));
  std::shared_ptr<zbe::TicketedElement<int> > t3 = l.push_front(std::make_shared<int>(3));
  l.push_front(std::make_shared<int>(5));
  std::shared_ptr<zbe::TicketedElement<int> > t7 = l.push_front(std::make_shared<int>(7));
  l.push_front(std::make_shared<int>(11));
  std::shared_ptr<zbe::TicketedElement<int> > t13 = l.push_front(std::make_shared<int>(13));
  l.push_front(std::make_shared<int>(17));
  l.push_front(std::make_shared<int>(19));
  l.push_front(std::make_shared<int>(23));
  std::shared_ptr<zbe::TicketedElement<int> > t29 = l.push_front(std::make_shared<int>(29));

  auto it = l.begin();
  EXPECT_EQ(29,*(*it++)) << "Element 29.";
  EXPECT_EQ(23,*(*it++)) << "Element 23.";
  EXPECT_EQ(19,*(*it++)) << "Element 19.";
  EXPECT_EQ(17,*(*it++)) << "Element 17.";
  EXPECT_EQ(13,*(*it++)) << "Element 13.";
  EXPECT_EQ(11,*(*it++)) << "Element 11.";
  EXPECT_EQ(7,*(*it++)) << "Element 7.";
  EXPECT_EQ(5,*(*it++)) << "Element 5.";
  EXPECT_EQ(3,*(*it++)) << "Element 3.";
  EXPECT_EQ(2,*(*it++)) << "Element 2.";

  t2->setINACTIVE();
  t7->setERASED();
  t13->setINACTIVE();
  t29->setINACTIVE();

  it = l.begin();

  //EXPECT_EQ(29,*it++) << "Element 29.";  // INACTIVE
  EXPECT_EQ(23,*(*it++)) << "Element 23.";
  EXPECT_EQ(19,*(*it++)) << "Element 19.";
  EXPECT_EQ(17,*(*it++)) << "Element 17.";
  //EXPECT_EQ(13,*it++) << "Element 13.";  // INACTIVE
  EXPECT_EQ(11,*(*it++)) << "Element 11.";
  //EXPECT_EQ(7,*it++) << "Element 7.";    // ERASED
  EXPECT_EQ(5,*(*it++)) << "Element 5.";
  EXPECT_EQ(3,*(*it++)) << "Element 3.";
  //EXPECT_EQ(2,*it++) << "Element 2.";    // INACTIVE

  t2->setERASED();
  t3->setINACTIVE();
  //t7->setERASED();  // Already erased, ticket invalid.
  t13->setACTIVE();
  t29->setERASED();

  it = l.begin();

  //EXPECT_EQ(29,*it++) << "Element 29.";  // ERASED
  EXPECT_EQ(23,*(*it++)) << "Element 23.";
  EXPECT_EQ(19,*(*it++)) << "Element 19.";
  EXPECT_EQ(17,*(*it++)) << "Element 17.";
  EXPECT_EQ(13,*(*it++)) << "Element 13.";    // previously INACTIVE, now ACTIVE
  EXPECT_EQ(11,*(*it++)) << "Element 11.";
  //EXPECT_EQ(7,*it++) << "Element 7.";    // Already ERASED
  EXPECT_EQ(5,*(*it++)) << "Element 5.";
  //EXPECT_EQ(3,*it++) << "Element 3.";    // INACTIVE
  //EXPECT_EQ(2,*it++) << "Element 2.";    // ERASED
}
