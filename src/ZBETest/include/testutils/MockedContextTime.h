/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MockedContextTime.h
 * @since 2018-07-17
 * @date 2018-07-17
 * @author Batis Degryll Ludo
 * @brief ContextTime with settable time. For testing purposes.
 */

#ifndef ZBETEST_TESTUTIL_MOCKEDCONTEXTTIME_H_
#define ZBETEST_TESTUTIL_MOCKEDCONTEXTTIME_H_

#include <cstdint>
#include <memory>

#include "ZBE/core/tools/time/ContextTime.h"

namespace zbetest {

/** \brief ContextTime with settable time. For testing purposes.
*/
class MockedContextTime : public zbe::ContextTime {
public:

  MockedContextTime(uint64_t fixedTime = 0) : fixedTime(fixedTime) {}

  std::shared_ptr<ContextTime> clone() {
    return std::make_shared<MockedContextTime>(fixedTime);
  };

  void setFixedTime(uint64_t fixedTime) { this->fixedTime = fixedTime;}

  uint64_t getFixedTime() { return fixedTime;}

private:
  uint64_t fixedTime;

  uint64_t _getTotalTime() {
    return fixedTime;
  }

};



}  // namespace zbetest

#endif  // ZBETEST_TESTUTIL_MOCKEDCONTEXTTIME_H_
