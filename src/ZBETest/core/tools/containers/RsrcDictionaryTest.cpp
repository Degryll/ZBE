#include "gtest/gtest.h"

#include <string>

#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/system/SysError.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"

TEST(NameRsrcDictionary, Usage) {
  zbe::NameRsrcDictionary& nrd = zbe::NameRsrcDictionary::getInstance();

  nrd.insert(std::string("aaa"), 1);
  nrd.insert(std::string("aab"), 2);
  nrd.insert(std::string("bbb"), 4);
  nrd.insert(std::string("c"), 4);

  EXPECT_EQ(1, nrd.get("aaa")) << "aaa must return 1";
  EXPECT_EQ(2, nrd.get("aab")) << "aab must return 1";
  EXPECT_EQ(4, nrd.get("bbb")) << "bbb must return 1";
  EXPECT_EQ(4, nrd.get("c")) << "c must return 1";

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initialy no errors.";
  nrd.insert(std::string("c"), 7);

  EXPECT_EQ(1, zbe::SysError::getNErrors()) << "Error rise for re-insert a name.";

  zbe::SysError::clear();

  nrd.get("45aaa");
  EXPECT_EQ(1, zbe::SysError::getNErrors()) << "Error rise for accessing an invalid element.";

  zbe::SysError::clear();
}

TEST(IdRsrcDictionary, Usage) {
  zbe::IdRsrcDictionary& ird = zbe::IdRsrcDictionary::getInstance();

  ird.insert(1, 1);
  ird.insert(2, 2);
  ird.insert(3, 4);
  ird.insert(4, 4);

  EXPECT_EQ(1, ird.get(1)) << "1 must return 1";
  EXPECT_EQ(2, ird.get(2)) << "2 must return 1";
  EXPECT_EQ(4, ird.get(3)) << "3 must return 1";
  EXPECT_EQ(4, ird.get(4)) << "4 must return 1";

  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initialy no errors.";
  ird.insert(4, 7);

  EXPECT_EQ(1, zbe::SysError::getNErrors()) << "Error rise for re-insert an id.";

  zbe::SysError::clear();

  ird.get(5);
  EXPECT_EQ(1, zbe::SysError::getNErrors()) << "Error rise for accessing an invalid element.";

  zbe::SysError::clear();
}

TEST(IdRsrcDictionary, WrongUsage) {
  zbe::IdRsrcDictionary& ird = zbe::IdRsrcDictionary::getInstance();
  
  EXPECT_EQ(0, zbe::SysError::getNErrors()) << "Initialy no errors.";

  ird.insert(0, 1);

  EXPECT_EQ(1, zbe::SysError::getNErrors()) << "An error must be set because id zero is discouraged.";

  zbe::SysError::clear();
}
