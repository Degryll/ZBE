#include "gtest/gtest.h"

#include "ZBE/archetypes/implementations/SimplePhysicalObject.h"

namespace SimplePhysicalObjectTest {

TEST(SimplePhysicalObject, Implementation) {
  zbe::SimplePhysicalObject po(42u);

  EXPECT_EQ(42u, po.getActuatorsList()) << "Creates a PO with list index 42.";

  po.setActuatorsList(37u);

  EXPECT_EQ(37u, po.getActuatorsList()) << "Change the actuators list index to 37.";
}

}  // namespace SimplePhysicalObjectTest
