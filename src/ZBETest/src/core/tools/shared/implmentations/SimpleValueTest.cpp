#include "gtest/gtest.h"

#include <cstdint>
#include <memory>

#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"

namespace SimpleValueTest {

TEST(SimpleValue, GetSetInt) {
  std::shared_ptr<zbe::Value<int> > val = std::make_shared<zbe::SimpleValue<int> >(0);

  EXPECT_EQ(0, (*val)()) << "Integer value is 0";
  EXPECT_EQ(0, val->get()) << "Integer value is 0";

  val->set(7);

  EXPECT_EQ(7, (*val)()) << "Integer value is 7";
  EXPECT_EQ(7, val->get()) << "Integer value is 7";

  //val->add(35);

//  EXPECT_EQ(42, (*val)()) << "Integer value is the answer to life, the universe and everything";
//  EXPECT_EQ(42, val->get()) << "Integer value is the answer to life, the universe and everything";
}

TEST(SimpleValue, GetSetChar) {
  std::shared_ptr<zbe::Value<char> > val = std::make_shared<zbe::SimpleValue<char> >(0);

  EXPECT_EQ(0, (*val)()) << "Char value is 0";
  EXPECT_EQ(0, val->get()) << "Char value is 0";

  val->set(7);

  EXPECT_EQ(7, (*val)()) << "Char value is 7";
  EXPECT_EQ(7, val->get()) << "Char value is 7";
// [TODO] on todo tipo puede ser "sumado". i.e. vector de strings
//  val->add(35);
//
//  EXPECT_EQ(42, (*val)()) << "Char value is the answer to life, the universe and everything";
//  EXPECT_EQ(42, val->get()) << "Char value is the answer to life, the universe and everything";
}

} // namespace SimpleValueTest
