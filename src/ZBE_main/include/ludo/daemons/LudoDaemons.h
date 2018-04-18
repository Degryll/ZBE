/**
 * Copyright 2012 Batis Degryll Ludo
 * @file LudoEntities.h
 * @since 2017-02-25
 * @date 2017-02-25
 * @author Ludo
 * @brief Entities for ludo's proving grounds.
 */

#ifndef ZBE_MAIN_LUDO_DAEMONS_LUDODAEMONS
#define ZBE_MAIN_LUDO_DAEMONS_LUDODAEMONS

#include <cstdint>
#include <memory>

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/system/SysTime.h"

#include "ludo/entities/LudoEntities.h"

namespace ludo {

template<typename T>
class ListEraser : virtual public zbe::Daemon {
public:
  ListEraser(uint64_t listId): id(listId), lmT(zbe::RsrcStore<zbe::TicketedForwardList<T> >::getInstance()){}
  void run(){
    lmT.get(id)->clear();
  }
private:
  uint64_t id;
  zbe::RsrcStore<zbe::TicketedForwardList<T> >& lmT;
};

class StateRotator : public zbe::Daemon {
  public:
	StateRotator(const StateRotator&) = delete;
	void operator=(const StateRotator&) = delete;

  	StateRotator(std::shared_ptr<GraphicElement> graphElem, int64_t minState, int64_t maxState)
  	  : ge(graphElem), mState(minState),  states(maxState - minState + 1), sysTime(zbe::SysTime::getInstance()) {}

  	void run() {
      int64_t current = ge->getState() - mState;
      current = ((current+1) % states) + mState;
      ge->setState(current);
      ge->setTimeStamp(sysTime.getEventTime());
  	}

  private:
    std::shared_ptr<GraphicElement> ge;
    int64_t mState;
    int64_t states;
    zbe::SysTime &sysTime = zbe::SysTime::getInstance();
};

} // namespace

#endif //ZBE_MAIN_LUDO_DAEMONS_LUDODAEMONS
