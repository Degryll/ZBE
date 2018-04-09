/**
 * Copyright 2015 Batis Degryll Ludo
 * @file Punishers.h
 * @since 2015-05-04
 * @date 2018-02-25
 * @author Degryll Ludo
 * @brief Common Punishers definitions.
 */

#ifndef ZBE_CORE_DAEMONS_PUNISHERS_H
#define ZBE_CORE_DAEMONS_PUNISHERS_H

#include "ZBE/core/daemons/PunisherDaemon.h"
#include "ZBE/core/behaviors/Behavior.h"

namespace zbe{

/** \brief Punishers that applies Behaviors over a list of entities.
*/
template<typename L, typename ...E>
using BehaviorDaemon = PunisherDaemon<Behavior<E...>, L>;

}  // namespace zbe

#endif  // ZBE_CORE_DAEMONS_PUNISHERS_H
