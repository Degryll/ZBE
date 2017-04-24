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

void EventStore::clearInstantStore() {
  clearStore(instantStore );
}

void EventStore::clearTimedStore() {
  clearStore(timedStore);
}

void EventStore::clearStore(std::forward_list<Event*>& store) {
  store.remove_if(deleteAll);
  bettertime = std::numeric_limits<int64_t>::max();
}

void EventStore::clearStore() {
  clearTimedStore();
  clearInstantStore();
}

void EventStore::storeEvent(Event* e) {
  if(e->getTime() == bettertime){
    timedStore.push_front(e);
  } else if (e->getTime() < bettertime){
    clearTimedStore();
    bettertime = e->getTime();
    timedStore.push_front(e);
  } else {
    delete e;
  }
}

void EventStore::storeInstantEvent(Event* e) {
  timedStore.push_front(e);
}

void EventStore::manageCurrent() {
  manageStore(timedStore);
  manageStore(instantStore);
}

void EventStore::manageStore(std::forward_list<Event*>& store) {
  for(auto e : store){
    e->manage();
  }
  clearStore(store);
}

int64_t EventStore::getTime() {
  return (bettertime);
}

}
