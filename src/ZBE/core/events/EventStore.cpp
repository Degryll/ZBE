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

  void EventStore::storeEvent(Event* e) {
    if(e->getTime()==bettertime){
      store.push_front(e);
    } else if (e->getTime()<=bettertime){
      bettertime = e->getTime();
      store.clear();
      store.push_front(e);
    }
  }

  void EventStore::clearStore() {
      store.clear();
  }

  const std::forward_list<Event*> & EventStore::getEvents() {
    return store;
  }

}
