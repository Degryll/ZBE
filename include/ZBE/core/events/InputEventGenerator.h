/**
 * Copyright 2016 Batis Degryll Ludo
 * @file InputEventGenerator.h
 * @since 2016-04-06
 * @date 2016-04-10
 * @author Ludo
 * @brief Input event generator, implementation file.
 */

#ifndef CORE_IO_INPUT_EVENT_GENERATOR_H
#define CORE_IO_INPUT_EVENT_GENERATOR_H

#include <cstdint>

#include "ZBE/core/io/InputReader.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/InputEvent.h"

namespace zbe {

  /** \brief This class will search for input event occurred between two given times and send it to the EventStore.
   */
  class InputEventGenerator {
    public:
      /** \brief Default constructor.
       */
      InputEventGenerator(InputReader * inputReader, int eventId):inputReader(inputReader),eventId(eventId) {};

      /** \brief Empty destructor.
       */
      ~InputEventGenerator() {};

      /** Will search for input events occurred between initTime and finalTime and send it to the EventStore.
       * \param initTime Time from which events are generated
       * \param endTime Time until the events are generated
       */
      void generate(uint64_t initTime, uint64_t endTime);

    private:
      InputReader * inputReader;
      int eventId;
  };
} // namespace zbe

#endif // CORE_IO_INPUT_EVENT_GENERATOR_H
