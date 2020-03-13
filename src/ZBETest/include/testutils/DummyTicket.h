/**
 * Copyright 2012 Batis Degryll Ludo
 * @file EntityMock.h
 * @since 2020-02-25
 * @date 2020-02-25
 * @author Batis Degryll Ludo
 * @brief
 */

#ifndef ZBETEST_TESTUTIL_DUMMYTICKET_H_
#define ZBETEST_TESTUTIL_DUMMYTICKET_H_

#include "ZBE/core/tools/containers/Ticket.h"

namespace zbetest {

class DummyTicket : public zbe::Ticket {
public:
  inline void setACTIVE()   {s = ACTIVE;}
  inline void setINACTIVE() {s = INACTIVE;}
  inline void setERASED()   {s = ERASED;}

  inline void setState(State state) {s = state;}

  inline bool isACTIVE()    {return (s == ACTIVE);}
  inline bool isNotACTIVE() {return (s != ACTIVE);}
  inline bool isINACTIVE()  {return (s == INACTIVE);}
  inline bool isERASED()    {return (s == ERASED);}

  inline State getState() {return (s);}

private:
  State s = ACTIVE;
};

}  // namespace zbetest

#endif //ZBETEST_TESTUTIL_DUMMYTICKET_H_
