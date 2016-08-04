/**
 * Copyright 2012 Batis Degryll Ludo
 * @file EventStore.h
 * @since 2016-03-26
 * @date 2016-08-04
 * @author Ludo
 * @brief A container to store events. It will store only the sooner event (or events) and will discard every other.
 */

#ifndef CORE_EVENTS_EVENTSTORE_H
#define CORE_EVENTS_EVENTSTORE_H

#include <cstdint>
#include <forward_list>
#include "ZBE/core/events/Event.h"

namespace zbe {
  /** \brief A container to store events. It will store only the sooner event (or events) and will discard every other.
   */
  class EventStore {
    public:
      EventStore(EventStore const&)    = delete;  //!< Needed for singleton.
      void operator=(EventStore const&) = delete;  //!< Needed for singleton.

      /** \brief Singleton implementation.
       *  \return The unique instance of the EventStore.
       */
      static EventStore& getInstance() {
        static EventStore instance;
        return (instance);
      }
      ~EventStore() {};  //!< Empty destructor.

      /** \brief Store an event if the event time is the same of the current
       *  stored ones. If its worst it will be ignored. If its better, all
       *  current event will be wiped and only this one will be saved.
       * \param e The event to be stored
       */
      void storeEvent(Event* e);

      /** \brief Erase all contained events.
       */
      void clearStore() {store.clear();}

      /** \brief Get the current event collection.
       *  \return A constant event list.
       */
      const std::forward_list<Event*> & getEvents() {return (store);}

    private:
      EventStore() :store(), bettertime(UINT64_MAX) {}
      std::forward_list<Event*> store;
      uint64_t bettertime;
  };
} //namespace zbe
#endif //CORE_EVENTS_EVENTSTORE_H
