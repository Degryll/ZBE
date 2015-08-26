#include "gtest/gtest.h"

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/containers/ArrayList.h"
#include "ZBE/core/tools/containers/ArrayListIterator.h"

TEST(ArrayList, Create) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::ArrayList<int> *l = new zbe::ArrayList<int>(10);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Create List.";
  delete l;
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Delete List.";
}

TEST(ArrayList, Insert) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::ArrayList<int> l(10);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Create List.";
  l.insert(42);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Insert.";
}

TEST(ArrayList, NotEnoughSpace) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::ArrayList<int> l(1);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Create List.";
  l.insert(42);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Insert element with space.";
  l.insert(37);
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Insert element without space, error is set.";
  zbe::SysError::clear();
}

TEST(ArrayList, NormalIteration) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::ArrayList<int> l(10);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Create List.";
  l.insert(2);
  l.insert(3);
  l.insert(5);
  l.insert(7);
  l.insert(11);
  l.insert(13);
  l.insert(17);
  l.insert(19);
  l.insert(23);
  l.insert(29);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Insert 10 elements.";

  zbe::ArrayListIterator<int> it(l.begin());
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Get Iterator.";

  EXPECT_EQ(29,*it++) << "Element 29.";
  EXPECT_EQ(23,*it++) << "Element 23.";
  EXPECT_EQ(19,*it++) << "Element 19.";
  EXPECT_EQ(17,*it++) << "Element 17.";
  EXPECT_EQ(13,*it++) << "Element 13.";
  EXPECT_EQ(11,*it++) << "Element 11.";
  EXPECT_EQ(7,*it++) << "Element 7.";
  EXPECT_EQ(5,*it++) << "Element 5.";
  EXPECT_EQ(3,*it++) << "Element 3.";
  EXPECT_EQ(2,*it++) << "Element 2.";
}

TEST(ArrayList, NormalIterationTicketed) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::ArrayListTicketed<int> l(10);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Create List.";
  l.insert(2);
  l.insert(3);
  l.insert(5);
  l.insert(7);
  l.insert(11);
  l.insert(13);
  l.insert(17);
  l.insert(19);
  l.insert(23);
  l.insert(29);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Insert 10 elements.";

  zbe::ArrayListTicketedIterator<int> it(l.begin());

  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Get Iterator.";

  EXPECT_EQ(29,*it++) << "Element 29.";
  EXPECT_EQ(23,*it++) << "Element 23.";
  EXPECT_EQ(19,*it++) << "Element 19.";
  EXPECT_EQ(17,*it++) << "Element 17.";
  EXPECT_EQ(13,*it++) << "Element 13.";
  EXPECT_EQ(11,*it++) << "Element 11.";
  EXPECT_EQ(7,*it++) << "Element 7.";
  EXPECT_EQ(5,*it++) << "Element 5.";
  EXPECT_EQ(3,*it++) << "Element 3.";
  EXPECT_EQ(2,*it++) << "Element 2.";
}

TEST(ArrayList, IterationTicketedElements) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no errors.";

  zbe::ArrayListTicketed<int> l(10);
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Create List.";
  zbe::Ticket &t2 = l.insert(2);
  zbe::Ticket &t3 = l.insert(3);
  l.insert(5);
  zbe::Ticket &t7 = l.insert(7);
  l.insert(11);
  zbe::Ticket &t13 = l.insert(13);
  l.insert(17);
  l.insert(19);
  l.insert(23);
  zbe::Ticket &t29 = l.insert(29);

  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Insert 10 elements.";

  zbe::ArrayListTicketedIterator<int> it(l.begin());

  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Get Iterator.";

  EXPECT_EQ(29,*it++) << "Element 29.";
  EXPECT_EQ(23,*it++) << "Element 23.";
  EXPECT_EQ(19,*it++) << "Element 19.";
  EXPECT_EQ(17,*it++) << "Element 17.";
  EXPECT_EQ(13,*it++) << "Element 13.";
  EXPECT_EQ(11,*it++) << "Element 11.";
  EXPECT_EQ(7,*it++) << "Element 7.";
  EXPECT_EQ(5,*it++) << "Element 5.";
  EXPECT_EQ(3,*it++) << "Element 3.";
  EXPECT_EQ(2,*it++) << "Element 2.";

  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Normal iteration.";

  t2.setINACTIVE();
  t7.setERASED();
  t13.setINACTIVE();
  t29.setINACTIVE();

  it.reset();

  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Reset iterator 1.";

  //EXPECT_EQ(29,*it++) << "Element 29.";  // INACTIVE
  EXPECT_EQ(23,*it++) << "Element 23.";
  EXPECT_EQ(19,*it++) << "Element 19.";
  EXPECT_EQ(17,*it++) << "Element 17.";
  //EXPECT_EQ(13,*it++) << "Element 13.";  // INACTIVE
  EXPECT_EQ(11,*it++) << "Element 11.";
  //EXPECT_EQ(7,*it++) << "Element 7.";    // ERASED
  EXPECT_EQ(5,*it++) << "Element 5.";
  EXPECT_EQ(3,*it++) << "Element 3.";
  //EXPECT_EQ(2,*it++) << "Element 2.";    // INACTIVE

  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Ticketed iteration 1.";

  t2.setERASED();
  t3.setINACTIVE();
  //t7.setERASED();  // Already erased, ticket invalid.
  t13.setACTIVE();
  t29.setERASED();

  it.reset();

  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Reset iterator 2.";

  //EXPECT_EQ(29,*it++) << "Element 29.";  // ERASED
  EXPECT_EQ(23,*it++) << "Element 23.";
  EXPECT_EQ(19,*it++) << "Element 19.";
  EXPECT_EQ(17,*it++) << "Element 17.";
  EXPECT_EQ(13,*it++) << "Element 13.";    // previously INACTIVE, now ACTIVE
  EXPECT_EQ(11,*it++) << "Element 11.";
  //EXPECT_EQ(7,*it++) << "Element 7.";    // Already ERASED
  EXPECT_EQ(5,*it++) << "Element 5.";
  //EXPECT_EQ(3,*it++) << "Element 3.";    // INACTIVE
  //EXPECT_EQ(2,*it++) << "Element 2.";    // ERASED

  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Ticketed iteration 2.";
}

