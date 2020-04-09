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
#include <vector>
#include <unordered_map>

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/io/InputBuffer.h"
#include "ZBE/core/io/InputTextBuffer.h"
#include "ZBE/core/io/InputStatus.h"
#include "ZBE/core/io/InputText.h"
#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/events/handlers/TextHandler.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/InputEvent.h"
#include "ZBE/core/events/TextEvent.h"
#include "ZBE/core/events/generators/util/InputStatusManager.h"

#include "ZBE/core/system/system.h"

namespace zbe {

  /** \brief This class ZBEAPI will search for input event occurred between two given times and send it to the EventStore.
   */
  class ZBEAPI InputEventGenerator : virtual public Daemon {
    public:
      InputEventGenerator(const InputEventGenerator&) = delete;  //!< Deleted copy constructor.
      void operator=(const InputEventGenerator&) = delete;  //!< Deleted operator.

      /** \brief Default constructor.
       */
      InputEventGenerator(std::shared_ptr<InputBuffer> inputBuffer, std::shared_ptr<InputTextBuffer> inputTextBuffer = nullptr, int eventId = 0, std::shared_ptr<TextHandler> handler = nullptr) : inputBuffer(inputBuffer), inputTextBuffer(inputTextBuffer), managers(), eventId(eventId), store(EventStore::getInstance()), handler(handler), contextTime(zbe::SysTime::getInstance()) {}

      /** \brief Empty destructor.
       */
      ~InputEventGenerator() {}

      void addManager(std::shared_ptr<InputStatusManager> manager) {managers.push_back(manager);}

      /** Will search for input events occurred between initTime and finalTime and send it to the EventStore.
       * \param initTime Time from which events are generated
       * \param endTime Time until the events are generated
       */
      void run();

    private:
      std::shared_ptr<InputBuffer> inputBuffer;
      std::shared_ptr<InputTextBuffer> inputTextBuffer;
      std::vector<std::shared_ptr<InputStatusManager> > managers;
      uint64_t eventId;
      EventStore &store;
      std::shared_ptr<TextHandler> handler;
      std::shared_ptr<ContextTime> contextTime;
  };

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_GENERATORS_INPUTEVENTGENERATOR_H
