/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StickyBarItem.h
 * @since 2017-10-09
 * @date 2017-10-09
 * @author Ludo Batis Degryll
 * @brief Daemon capable of change bar state.
 */

#ifndef ZOMBIENOID_DAEMONS_ITEMS_STICKYBARITEM
#define ZOMBIENOID_DAEMONS_ITEMS_STICKYBARITEM

#include <memory>
#include <cstdint>

#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"

#include "ZBE/events/handlers/time/DaemonTimeHandler.h"

#include "ZBE/entities/avatars/Stated.h"

namespace zombienoid {


/** \brief Daemon capable of change bar state.
 */
class UnStickyBar : public zbe::Daemon {
public:
  UnStickyBar(std::shared_ptr<zbe::Daemon> endDaemon, std::shared_ptr<zbe::Value<int64_t> > itemState, int64_t endState)
    : endDaemon(endDaemon), itemState(itemState), endState(endState) {}
  void run() override {
    endDaemon->run();
    itemState->set(endState);
  }

private:
  std::shared_ptr<zbe::Daemon> endDaemon;
  std::shared_ptr<zbe::Value<int64_t> > itemState;
  int64_t endState;
};

/** \brief Daemon capable of increase an value.
 */

class StickyBarItem : public zbe::Daemon {
public:
  StickyBarItem(std::shared_ptr<zbe::Daemon> initDaemon, std::shared_ptr<zbe::Daemon> endDaemon, std::shared_ptr<zbe::TimeEventGenerator> teg,
                int64_t time, int64_t initState, int64_t endState, std::shared_ptr<zbe::Value<int64_t> > itemState)
    : initDaemon(initDaemon), endDaemon(endDaemon), teg(teg), time(time), initState(initState), endState(endState), itemState(itemState), timer(nullptr) {}
  void run() override {
    if(itemState->get() != initState) {
      itemState->set(initState);
      initDaemon->run();
      std::shared_ptr<zbe::TimeHandler> endHandler = std::make_shared<zbe::DaemonTimeHandler>(std::make_shared<UnStickyBar>(endDaemon, itemState, endState));
      timer = teg->addTimer(endHandler, zbe::SysTime::getInstance()->getEventTime() + time);
    } else {
      timer->increaseTime(time);
    }
  }

private:
  std::shared_ptr<zbe::Daemon> initDaemon;
  std::shared_ptr<zbe::Daemon> endDaemon;
  std::shared_ptr<zbe::TimeEventGenerator> teg;
  int64_t time;
  int64_t initState;
  int64_t endState;
  std::shared_ptr<zbe::Value<int64_t> > itemState;
  std::shared_ptr<zbe::TimerTicket> timer;
};

}  // namespace zombienoid

#endif // ZOMBIENOID_DAEMONS_ITEMS_STICKYBARITEM
