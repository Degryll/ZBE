/**
 * Copyright 2012 Batis Degryll Ludo
 * @file EventStore.cpp
 * @since 2016-03-26
 * @date 2016-03-26
 * @author Ludo
 * @brief A container to store events. It will store only the sooner event (or events) and will discard every other.
 */

#include "ZBE/core/events/EventStore.h"

namespace zbe {


static bool deleteAll(Event* e) {
  delete e;
  return true;
}

void EventStore::clearStore() {
  store.remove_if(deleteAll);
  bettertime = UINT64_MAX;
}


void EventStore::storeEvent(Event* e) {
  if(e->getTime() == bettertime){
    store.push_front(e);
  } else if (e->getTime() < bettertime){
    clearStore();
    bettertime = e->getTime();
    store.push_front(e);
  }
}

void EventStore::manageCurrent() {
  for(auto e : store){
    e->manage();
  }
  clearStore();
}

uint64_t EventStore::getTime() {
  return (bettertime);
}

}
