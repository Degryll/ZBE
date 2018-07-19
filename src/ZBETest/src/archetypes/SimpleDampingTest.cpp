#include "gtest/gtest.h"

#include "ZBE/archetypes/implementations/SimpleDamping.h"

namespace SimpleDampingTest {

TEST(SimpleDamping, Implementation) {
  zbe::SimpleDamping sd;

  EXPECT_EQ(1.0, sd.getFactor()) << "The empty constructor set the damping factor to 1.0.";

  sd.setFactor(4.2);

  EXPECT_EQ(4.2, sd.getFactor()) << "The new damping factor is 4.2.";

  zbe::SimpleDamping sd2(3.7);

  EXPECT_EQ(3.7, sd2.getFactor()) << "The parametrized constructor set the damping factor to 3.7.";
}

}  // namespace SimpleDampingTest
