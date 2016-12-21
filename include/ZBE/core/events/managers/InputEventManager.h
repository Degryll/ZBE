/**
 * Copyright 2012 Batis Degryll Ludo
 * @file InputEventManager.h
 * @since 2016-12-21
 * @date 2016-12-21
 * @author Batis
 * @brief Manage input events.
 */

#ifndef CORE_EVENTS_INPUTEVENTHANDLER_H
#define CORE_EVENTS_INPUTEVENTHANDLER_H

#include <cstdint>
#include <map>

#include "ZBE/core/handlers/InputHandler.h"
#include "ZBE/core/events/EventDispatcher.h"

namespace zbe {

/** \brief Manage input events.
 */
class InputEventManager {
  public:
      InputEventManager(InputEventManager const&)  = delete;  //!< Needed for singleton.
      void operator=(InputEventManager const&)    = delete;  //!< Needed for singleton.

       /** \brief Singleton implementation.
       *   \return The unique instance of the InputEventManager.
       */
      static InputEventManager& getInstance() {
        static InputEventManager instance;
        return (instance);
      }

    /** Add a handler to an input event.
     * \param id Id of the key
     * \param handler Handler to run when key pressed
     */
    inline void addHandler(uint32_t id, InputHandler* handler) {handlers[id] = handler;}

     /** Remove a handler from an input event.
     * \param id Id of the key
     */
    inline void removeHandler(uint32_t id) {handlers.erase(id);}

    /** Run the handler associated to the Key.
     * \param id Timer id
     */
    void run(InputEvent *event) {
      uint32_t id = event->getKey();
      handlers[id]->run(event->getState());
      delete event;
    }

  private:
    /** \brief Empty Constructor.
     */
    InputEventManager() : handlers() {};

    std::map<uint32_t, InputHandler*> handlers;
};

}  // namespace zbe

#endif // CORE_EVENTS_INPUTEVENTHANDLER_H
