/**
 * Copyright 2016 Batis Degryll Ludo
 * @file InputEventGenerator.h
 * @since 2016-04-06
 * @date 2018-03-15
 * @author Ludo
 * @brief Input event generator.
 */

#ifndef ZBE_CORE_EVENTS_GENERATORS_INPUTEVENTGENERATOR_H
#define ZBE_CORE_EVENTS_GENERATORS_INPUTEVENTGENERATOR_H

#include <cstdint>
#include <memory>
#include <map>

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/io/InputBuffer.h"
#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/InputEvent.h"

namespace zbe {

  /** \brief This class will search for input event occurred between two given times and send it to the EventStore.
   */
  class InputEventGenerator : virtual public Daemon {
    public:
      InputEventGenerator(const InputEventGenerator&) = delete;  //!< Deleted copy constructor.
      void operator=(const InputEventGenerator&) = delete;  //!< Deleted operator.

      /** \brief Default constructor.
       */
      InputEventGenerator(std::shared_ptr<InputBuffer> inputBuffer, int eventId) : inputBuffer(inputBuffer), eventId(eventId), store(EventStore::getInstance()), handlers(), sysTime(zbe::SysTime::getInstance()) {};

      /** \brief Empty destructor.
       */
      ~InputEventGenerator() {};

      /** Will search for input events occurred between initTime and finalTime and send it to the EventStore.
       * \param initTime Time from which events are generated
       * \param endTime Time until the events are generated
       */
      void run();

      /** Add a handler to an input event.
       * \param id Id of the key
       * \param handler Handler to run when key pressed
       */
      inline void addHandler(uint32_t id, InputHandler* handler) {handlers[id] = handler;}

      /** Remove a handler from an input event.
       * \param id Id of the key
       */
      inline void removeHandler(uint32_t id) {handlers.erase(id);}

    private:
      std::shared_ptr<InputBuffer> inputBuffer;
      int eventId;
      EventStore &store;
      std::map<uint32_t, InputHandler*> handlers;
      zbe::SysTime &sysTime;
  };

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_GENERATORS_INPUTEVENTGENERATOR_H
