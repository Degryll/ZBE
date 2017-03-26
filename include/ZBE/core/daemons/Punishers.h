#ifndef CORE_DAEMONS_PUNISHERS_H_INCLUDED
#define CORE_DAEMONS_PUNISHERS_H_INCLUDED

#include "ZBE/core/daemons/PunisherDaemon.h"
#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/drawers/Drawer.h"

namespace zbe{

  template<typename E, typename L>
  using BehaviorDaemon = TimedPunisherDaemon<Behavior<E>, L>;

  template<typename E, typename L>
  using DrawerDaemon = PunisherDaemon<Drawer<E>, L>;
}

#endif // CORE_DAEMONS_PUNISHERS_H_INCLUDED
