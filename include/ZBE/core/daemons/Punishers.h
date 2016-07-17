#ifndef CORE_DAEMONS_PUNISHERS_H_INCLUDED
#define CORE_DAEMONS_PUNISHERS_H_INCLUDED

#include "ZBE/core/daemons/PunisherDaemon.h"
#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/drawers/Drawer.h"

namespace zbe{

  template<typename L, typename E>
  using BehaviorDaemon = PunisherDaemon<Behavior<E>, L, E>;

  template<typename L, typename E>
  using DrawerDaemon = PunisherDaemon<Drawer<E>, L, E>;
}

#endif // CORE_DAEMONS_PUNISHERS_H_INCLUDED
