#ifndef CORE_DAEMONS_PUNISHERS_H_INCLUDED
#define CORE_DAEMONS_PUNISHERS_H_INCLUDED

#include "ZBE/core/daemons/PunisherDaemon.h"
#include "ZBE/core/behaviors/Behavior.h"

namespace zbe{

  template<typename E, typename L>
  using BehaviorDaemon = PunisherDaemon<Behavior<E>, L>;

}

#endif // CORE_DAEMONS_PUNISHERS_H_INCLUDED

//          revisar nombres
