/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StickyBarItem.h
 * @since 2017-10-09
 * @date 2017-10-09
 * @author Ludo
 * @brief Daemon capable of change bar state.
 */

#ifndef ZBE_MAIN_ZMBIENOID_DAEMONS_ITEMS_STICKYBARITEM
#define ZBE_MAIN_ZMBIENOID_DAEMONS_ITEMS_STICKYBARITEM

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
  UnStickyBar(std::shared_ptr<zbe::AvatarEntity<zbe::Stated> > aeStated, uint64_t state): aeStated(aeStated), state(state) {}
  void run(){
    zbe::Stated* s;
    aeStated->assignAvatar(&s);
    s->setState(state);
  }

private:
  std::shared_ptr<zbe::AvatarEntity<zbe::Stated> > aeStated;
  uint64_t state;
};

/** \brief Daemon capable of increase an value.
 */
class StickyBarItem : public zbe::Daemon {
public:
  StickyBarItem(std::shared_ptr<zbe::AvatarEntity<zbe::Stated> > aeStated, std::shared_ptr<zbe::TimeEventGenerator> teg, int64_t time, int64_t state): aeStated(aeStated), teg(teg), time(time), state(state) {}
  void run(){
    zbe::Stated* s;
    aeStated->assignAvatar(&s);
    int64_t oldState= s->getState();
    if(oldState!=state) {
      s->setState(state);
      std::shared_ptr<zbe::TimeHandler> th = std::make_shared<zbe::DaemonTimeHandler>(std::make_shared<UnStickyBar>(aeStated, oldState));
      teg->addTimer(th, zbe::SysTime::getInstance().getEventTime() + time);
    }
  }

private:
  std::shared_ptr<zbe::AvatarEntity<zbe::Stated> > aeStated;
  std::shared_ptr<zbe::TimeEventGenerator> teg;
  int64_t time;
  int64_t state;
};

}  // namespace zombienoid

#endif // ZBE_MAIN_ZMBIENOID_DAEMONS_ITEMS_STICKYBARITEM
