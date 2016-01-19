#ifndef CORE_DAEMONS_PUNISHERS_H_INCLUDED
#define CORE_DAEMONS_PUNISHERS_H_INCLUDED

#include "./PunisherDaemon.h"
#include "../behaviors/Behavior.h"

namespace zbe{

  template<typename L, typename E>
  using BehaviorDaemon = PunisherDaemon<Behavior<E>, L, E>;

}

#endif // CORE_DAEMONS_PUNISHERS_H_INCLUDED
