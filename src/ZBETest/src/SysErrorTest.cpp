#include "gtest/gtest.h"

#include "ZBE/core/system/SysError.h"

TEST(SysError, InitialState) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no Errors.";
  EXPECT_STREQ("",zbe::SysError::getLastErrorString().c_str()) << "Checking error string is "".";
}

TEST(SysError, SetError) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no Errors.";
  EXPECT_STREQ("",zbe::SysError::getLastErrorString().c_str()) << "Checking error string is "".";

  zbe::SysError::setError("Test 1");
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Checking first error.";
  EXPECT_STREQ("Test 1",zbe::SysError::getLastErrorString().c_str()) << "Checking error string.";

  zbe::SysError::setError("Test 2");
  EXPECT_EQ(2,zbe::SysError::getNErrors()) << "Checking second error.";
  EXPECT_STREQ("Test 1",zbe::SysError::getLastErrorString().c_str()) << "Checking that the error string does not change.";
  zbe::SysError::clear();
}

TEST(SysError, Clear) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no Errors.";
  EXPECT_STREQ("",zbe::SysError::getLastErrorString().c_str()) << "Checking error string is "".";

  zbe::SysError::setError("Test 1");
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Checking first error.";
  EXPECT_STREQ("Test 1",zbe::SysError::getLastErrorString().c_str()) << "Checking error string.";

  zbe::SysError::clear();
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Checking that there is no error.";
  EXPECT_STREQ("",zbe::SysError::getLastErrorString().c_str()) << "Checking error string is "" again.";
}

TEST(SysError, Complete) {
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Initially no Errors.";
  EXPECT_STREQ("",zbe::SysError::getLastErrorString().c_str()) << "Checking error string is "".";

  zbe::SysError::setError("Test 1");
  EXPECT_EQ(1,zbe::SysError::getNErrors()) << "Checking first error.";
  EXPECT_STREQ("Test 1",zbe::SysError::getLastErrorString().c_str()) << "Checking error string.";

  zbe::SysError::setError("Test 2");
  EXPECT_EQ(2,zbe::SysError::getNErrors()) << "Checking second error.";
  EXPECT_STREQ("Test 1",zbe::SysError::getLastErrorString().c_str()) << "Checking that the error string does not change.";

   zbe::SysError::clear();
  EXPECT_EQ(0,zbe::SysError::getNErrors())  << "Checking error string is "" again.";
  EXPECT_STREQ("",zbe::SysError::getLastErrorString().c_str()) << "Checking error string is "" again.";

  zbe::SysError::setError("Test 1");
  zbe::SysError::setError("Test 2");
  zbe::SysError::setError("Test 3");
  zbe::SysError::setError("Test 4");
  zbe::SysError::setError("Test 5");
  EXPECT_EQ(5,zbe::SysError::getNErrors())  << "Checking that there is 5 errors.";
  EXPECT_STREQ("Test 1",zbe::SysError::getLastErrorString().c_str())  << "Checking that error string is the string of the first error.";

  zbe::SysError::clear();
  EXPECT_EQ(0,zbe::SysError::getNErrors()) << "Checking that there is no error.";;
  EXPECT_STREQ("",zbe::SysError::getLastErrorString().c_str()) << "Checking error string is "" again.";
}
