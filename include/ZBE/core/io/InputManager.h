/**
 * Copyright 2016 Batis Degryll Ludo
 * @file InputReader.h
 * @since 2016-04-06
 * @date 2016-04-06
 * @author Ludo
 * @brief Imput manager.
 */

#ifndef CORE_IO_INPUTMANAGER_H
#define CORE_IO_INPUTMANAGER_H

#include <cstdint>
#include <list>

namespace zbe {

/** \brief This class will search for input event occurred between two given times and send it to the EventStore.
 */
class InputManager {
  public:
    /** \brief Default constructor.
     */
    virtual InputManager(InputReader * inputEvent):InputReader(inputReader) {};

    /** \brief Empty destructor.
     */
    virtual ~InputManager() {};

    /** Will search for input event occurred between initTime and finalTime and send it to the EventStore.
     */
    virtual void run(uint64_t initTime, uint64_t finalTime);

  private:
    InputReader * inputReader;
};
} // namespace zbe

#endif // CORE_IO_INPUTMANAGER_H
