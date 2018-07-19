#include "gtest/gtest.h"

#include <forward_list>

#include "ZBE/core/tools/containers/ListJoint.h"
namespace ListJointTest {

TEST(ListJoint, ListForwardJoint_usage) {
  zbe::ListJoint<std::forward_list<int>, int> lj;
  int all[] = {2,88,11,9,45,83,7};
  std::forward_list<int> a;
  a.push_front(7);
  a.push_front(83);
  a.push_front(45);
  std::forward_list<int> b;
  b.push_front(9);
  b.push_front(11);
  std::forward_list<int> c;
  c.push_front(88);
  c.push_front(2);

  lj.add(&a);
  lj.add(&b);
  lj.add(&c);

  int i = 0;
  for(auto val : lj) {
    EXPECT_EQ(all[i],val) << "Element" << i << " must be " << all[i];
    i++;
  }
}

TEST(ListJoint, ListTicketedJoint_usage) {
  zbe::ListTicketedJoint<std::forward_list<int>, int> ltj;
  int all[] = {2,88,45,83,7};
  auto a = std::make_shared<std::forward_list<int> >();
  a->push_front(7);
  a->push_front(83);
  a->push_front(45);
  auto b = std::make_shared<std::forward_list<int> >();
  b->push_front(9);
  b->push_front(11);
  auto c = std::make_shared<std::forward_list<int> >();
  c->push_front(88);
  c->push_front(2);

  std::shared_ptr<zbe::TicketedElement<std::forward_list<int> > > t1 = ltj.add(a);
  std::shared_ptr<zbe::TicketedElement<std::forward_list<int> > > t2 = ltj.add(b);
  std::shared_ptr<zbe::TicketedElement<std::forward_list<int> > > t3 = ltj.add(c);

  t2->setINACTIVE();

  int i = 0;
  for(auto val : ltj) {
    EXPECT_EQ(all[i],val) << "Element" << i << " must be " << all[i];
    i++;
  }
}

} //namespace ListJointTest
