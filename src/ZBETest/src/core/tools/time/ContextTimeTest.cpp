#include "gtest/gtest.h"

#include <cstdio>

#include "ZBE/core/tools/time/ContextTime.h"
#include "ZBE/core/tools/time/SubordinateTime.h"
#include "ZBE/core/system/SysError.h"

#include "testutils/MockedContextTime.h"

namespace ContextTimeTest {

TEST (ContextTimeTest, DISABLED_Hierarchy) {
  zbe::ContextTime::setMaxFrameTime(1000);
  std::shared_ptr<zbetest::MockedContextTime> grandpa = std::make_shared<zbetest::MockedContextTime>();
  std::shared_ptr<zbe::ContextTime> parent = zbe::SubordinateTime::child(grandpa);
  std::shared_ptr<zbe::ContextTime> uncle = parent->clone();
  std::shared_ptr<zbe::ContextTime> child = zbe::SubordinateTime::child(parent);

  grandpa->setFixedTime(0);
  grandpa->update();
  parent->update();
  uncle->update();
  child->update();

  EXPECT_EQ(0, grandpa->getTotalTime()) << "Grandpa time must be 0";
  EXPECT_EQ(0, parent->getTotalTime()) << "Parent must match granda time (0)";
  EXPECT_EQ(0, uncle->getTotalTime()) << "Uncle must match granda time (0)";
  EXPECT_EQ(0, child->getTotalTime()) << "Child must match parent time (0)";

  EXPECT_EQ(0, grandpa->getRemainTime()) << "Grandpa remain time must be 0";
  EXPECT_EQ(0, parent->getRemainTime()) << "parent remain time must be 0";
  EXPECT_EQ(0, uncle->getRemainTime()) << "uncle remain time must be 0";
  EXPECT_EQ(0, child->getRemainTime()) << "child remain time must be 0";

  grandpa->setFixedTime(1000);
  grandpa->update();
  parent->update();
  uncle->update();
  child->update();

  EXPECT_EQ(1000, grandpa->getTotalTime()) << "Grandpa time must be 1000";
  EXPECT_EQ(1000, parent->getTotalTime()) << "Parent must match granda time (1000)";
  EXPECT_EQ(1000, uncle->getTotalTime()) << "Uncle must match granda time (1000)";
  EXPECT_EQ(1000, child->getTotalTime()) << "Child must match parent time (1000)";

  EXPECT_EQ(1000, grandpa->getRemainTime()) << "Grandpa remain time must be 1000";
  EXPECT_EQ(1000, parent->getRemainTime()) << "parent remain time must be 1000";
  EXPECT_EQ(1000, uncle->getRemainTime()) << "uncle remain time must be 1000";
  EXPECT_EQ(1000, child->getRemainTime()) << "child remain time must be 1000";

  parent->pause();

  grandpa->setFixedTime(2000);
  grandpa->update();
  parent->update();
  uncle->update();
  child->update();

  EXPECT_EQ(2000, grandpa->getTotalTime()) << "Grandpa time must be 2000";
  EXPECT_EQ(1000, parent->getTotalTime()) << "Parent must keep previous time (1000)";
  EXPECT_EQ(2000, uncle->getTotalTime()) << "Uncle must match granda time (2000)";
  EXPECT_EQ(1000, child->getTotalTime()) << "Child must match parent time (1000)";

  EXPECT_EQ(1000, grandpa->getRemainTime()) << "Grandpa remain time must be 1000";
  EXPECT_EQ(0, parent->getRemainTime()) << "parent remain time must be 0";
  EXPECT_EQ(1000, uncle->getRemainTime()) << "uncle remain time must be 1000";
  EXPECT_EQ(0, child->getRemainTime()) << "child remain time must be 0";


  // TODO
  parent->resume(2000);

  grandpa->setFixedTime(3000);
  grandpa->update();
  parent->update();
  uncle->update();
  child->update();

  EXPECT_EQ(3000, grandpa->getTotalTime()) << "Grandpa time must be 3000";
  EXPECT_EQ(3000, parent->getTotalTime()) << "Parent must advance by 1000 (2000)";
  EXPECT_EQ(3000, uncle->getTotalTime()) << "Uncle must match granda time (3000)";
  EXPECT_EQ(3000, child->getTotalTime()) << "Child must match parent time (2000)";

  EXPECT_EQ(1000, grandpa->getRemainTime()) << "Grandpa remain time must be 1000";
  EXPECT_EQ(1000, parent->getRemainTime()) << "parent remain time must be 1000";
  EXPECT_EQ(1000, uncle->getRemainTime()) << "uncle remain time must be 1000";
  EXPECT_EQ(1000, child->getRemainTime()) << "child remain time must be 1000";
}

}  // namespace ContextTimeTest
