#include "gtest/gtest.h"

#include "ZBE/archetypes/implementations/SimpleWide.h"

namespace SimpleWideTest {

TEST(SimpleWide, Implementation) {
  zbe::SimpleWide sw(3.7);

  EXPECT_EQ(3.7, sw.getWidth()) << "The new SimpleWide with 4.2 width.";

  sw.setWidth(4.2);

  EXPECT_EQ(4.2, sw.getWidth()) << "The new width of 4.2.";
}

}  // namespace SimpleDampingTest
