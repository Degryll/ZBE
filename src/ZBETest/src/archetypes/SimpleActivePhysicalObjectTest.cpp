#include "gtest/gtest.h"

#include "ZBE/archetypes/implementations/SimpleActivePhysicalObject.h"

namespace SimpleActivePhysicalObjectTest {

TEST(SimpleActivePhysicalObject, Implementation) {
  zbe::SimpleActivePhysicalObject apo(0u, 42u);

  EXPECT_EQ(42u, apo.getCollisionablesList()) << "Creates an APO with list index 0 and 42.";

  apo.setCollisionablesList(37u);

  EXPECT_EQ(37u, apo.getCollisionablesList()) << "Change the collisionables list index to 37.";
}

}  // namespace SimpleActivePhysicalObjectTest
