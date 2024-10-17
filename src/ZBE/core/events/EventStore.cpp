/**
 * Copyright 2012 Batis Degryll Ludo
 * @file EventStore.cpp
 * @since 2016-03-26
 * @date 2018-03-27
 * @author Ludo Batis Degryll
 * @brief A container to store events. It will store only the sooner event (or events) and will discard every other.
 */

#include <iostream>
#include "ZBE/core/events/EventStore.h"

namespace zbe {

/** \brief Used to delete (and free memory) all events in a store.
*
*/
static bool deleteAll(Event* e) {
  delete e;
  return true;
}

EventStore& EventStore::getInstance() {
  static EventStore instance;
  return (instance);
}

void EventStore::clearInstantStore() {
  clearStore(instantStore);
}

void EventStore::clearTimedStore() {
  clearStore(timedStore);
}

void EventStore::clearStore(std::forward_list<Event*>& store) {
  store.remove_if(deleteAll);
  bettertime = std::numeric_limits<uint64_t>::max();
}

void EventStore::clearStore() {
  clearTimedStore();
  clearInstantStore();
}

void EventStore::storeEvent(Event* e) {
  if(e->getTime() == static_cast<int64_t>(bettertime)) {
    timedStore.push_front(e);
  } else if (e->getTime() < static_cast<int64_t>(bettertime)) {
    clearTimedStore();
    bettertime = static_cast<uint64_t>(e->getTime());
    timedStore.push_front(e);
  } else {
    delete e;
  }
}

void EventStore::storeInstantEvent(Event* e) {
  instantStore.push_front(e);
}

void EventStore::manageCurrent() {
  manageStore(timedStore);
  manageStore(instantStore);
}

void EventStore::manageStore(std::forward_list<Event*>& store) {
  for(auto e : store) {
    e->manage();
  }
  clearStore(store);
}

uint64_t EventStore::getTime() const {
  return (bettertime);
}

}  // namespace zbe
