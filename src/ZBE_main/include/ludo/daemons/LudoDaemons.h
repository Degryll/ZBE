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

#include "ZBE/core/tools/containers/ListManager.h"
#include "ZBE/core/daemons/Daemon.h"

#include "ludo/entities/LudoEntities.h"

namespace ludo {

template<typename T>
class ListEraser : virtual public zbe::Daemon {
public:
  ListEraser(uint64_t listId): id(listId), lmT(zbe::ListManager<zbe::TicketedForwardList<T> >::getInstance()){}
  void run(){
    lmT.get(id)->clear();
  }
private:
  uint64_t id;
  zbe::ListManager<zbe::TicketedForwardList<T> >& lmT;
};

} // namespace

#endif //ZBE_MAIN_LUDO_DAEMONS_LUDODAEMONS
