#include "gtest/gtest.h"

#include <forward_list>

#include "ZBE/core/tools/containers/ListJoint.h"
namespace ListJointTest {

TEST(ListJoint, Usage) {
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
  for(auto val : lj){
    EXPECT_EQ(all[i],val) << "Element" << i << " must be " << all[i];
    i++;
  }
}

} //namespace ListJointTest
