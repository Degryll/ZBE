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
#include <string>
#include <list>
#include <vector>
#include <unordered_map>
#include <nlohmann/json.hpp>

#include "ZBE/core/io/InputBuffer.h"
#include "ZBE/core/io/InputTextBuffer.h"
#include "ZBE/core/io/InputStatus.h"
#include "ZBE/core/io/InputText.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/events/handlers/TextHandler.h"
#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/InputEvent.h"
#include "ZBE/core/events/TextEvent.h"
#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/system/system.h"

#include "ZBE/factories/Factory.h"


namespace zbe {

using HandlerList = std::list<std::shared_ptr<InputHandler> >;
using HandlerTicket = HandlerList::iterator;

class ZBEAPI InputStatusManager {
public:

  virtual ~InputStatusManager() {}

  /** \brief Generate events if the InputStatus match some condition.
   *  Implementation dependant.
   *  \param is InputStatus to check
   */
  virtual void generate(const InputStatus& is) = 0;
protected:
  template <typename IteratorA, typename IteratorB, typename IteratorC>
  inline bool range_contains(IteratorA from, const IteratorB& end, const IteratorC& candidate) {
      while (from != end)
          if (&*from++ == &*candidate)
              return true;
      return false;
  }

  template <typename List, typename Iterator>
  inline bool list_contains(List& l, const Iterator& candidate) {
    return range_contains(l.begin(), l.end(), candidate);
  }

  struct Handlers {
    HandlerList active;
    HandlerList inactive;
  };

};

class ZBEAPI MappedInputStatusManager : public InputStatusManager {
public:

  MappedInputStatusManager() : eventId(), store(EventStore::getInstance()), handlers() {}
  MappedInputStatusManager(int eventId) : eventId(eventId), store(EventStore::getInstance()), handlers() {}
  virtual ~MappedInputStatusManager() = default;

  /** Add a handler to an input event.
   * \param id Id of the key
   * \param handler Handler to run when key pressed
   */
  inline HandlerTicket addHandler(uint32_t inputId, std::shared_ptr<InputHandler> handler) {
    ensureListExists(inputId);
    handlers[inputId].active.push_front(handler);
    return handlers[inputId].active.begin();
  }

  /** Remove a handler from an input event.
   * \param id Id of the key
   */
  inline void removeHandler(uint32_t inputId, HandlerTicket ticket) {
    if (list_contains(handlers[inputId].active, ticket)) {
      handlers[inputId].active.erase(ticket);
    } else if (list_contains(handlers[inputId].inactive, ticket)) {
      handlers[inputId].inactive.erase(ticket);
    } else {
      SysError::setError("ERROR: Handler cant be erased, handler not found (wrong key?).");
    }
  }

  /** Remove a handler from an input event.
   * \param id Id of the key
   */
  inline void disableHandler(uint32_t inputId, HandlerTicket ticket) {
    if (list_contains(handlers[inputId].active, ticket)) {
      handlers[inputId].active.splice(ticket, handlers[inputId].inactive);
    } else if (!list_contains(handlers[inputId].inactive, ticket)) {
      SysError::setError("ERROR: Handler cant be disabled, handler not found (wrong key?).");
    }
  }

  /** Remove a handler from an input event.
   * \param id Id of the key
   */
  inline void enableHandler(uint32_t inputId, HandlerTicket ticket) {
    if (list_contains(handlers[inputId].inactive, ticket)) {
      handlers[inputId].inactive.splice(ticket, handlers[inputId].active);
    } else if (!list_contains(handlers[inputId].active, ticket)) {
      SysError::setError("ERROR: Handler cant be enabled, handler not found (wrong key?).");
    }
  }

  /** Remove a handler from an input event.
   * \param id Id of the key
   */
  inline void moveHandler(uint32_t srcInputId, uint32_t dstInputId, HandlerTicket ticket) {
    if (list_contains(handlers[srcInputId].active, ticket)) {
      ensureListExists(dstInputId);
      handlers[srcInputId].active.splice(ticket, handlers[dstInputId].active);
    } else if (list_contains(handlers[srcInputId].inactive, ticket)) {
      ensureListExists(dstInputId);
      handlers[srcInputId].inactive.splice(ticket, handlers[dstInputId].inactive);
    } else {
      SysError::setError("ERROR: Handler cant be moved, handler not found (wrong key?).");
    }
  }

  void generate(const InputStatus& is) {
    auto hit = handlers.find(is.getId());
    if (hit != handlers.end()) {
        for(auto& h : hit->second.active) {
          InputEvent* e = new InputEvent(eventId, is.getTime(), is.getId(), is.getStatus(), h.get()); // TODO repensar ese shared_ptr reconvertido a puntero
          store.storeEvent(e);
        }
    }
  }

  inline void setEventID(int eventId) {
    this->eventId = eventId;
  }

private:
  void ensureListExists(uint32_t inputId) {
    // TODO en c++20 sustituir por contains
    auto hit = handlers.find(inputId);
    if (hit == handlers.end()) {
      handlers[inputId] = Handlers{};
    }
  }

  uint64_t eventId;
  EventStore &store;
  std::unordered_map<uint32_t, Handlers> handlers;

};

class ZBEAPI AnyInputStatusManager : public InputStatusManager {
public:
  virtual ~AnyInputStatusManager() {}

  virtual void generate(const InputStatus& is) = 0;

};

class ZBEAPI InputEventGeneratorFtry;

/** \brief This class ZBEAPI will search for input event occurred between two given times and send it to the EventStore.
 */
class ZBEAPI InputEventGenerator : virtual public Daemon {
  public:
    friend class InputEventGeneratorFtry;

    InputEventGenerator(const InputEventGenerator&) = delete;  //!< Deleted copy constructor.
    void operator=(const InputEventGenerator&) = delete;  //!< Deleted operator.

    /** \brief Default constructor.
     */
    InputEventGenerator(std::shared_ptr<InputBuffer> inputBuffer, std::shared_ptr<InputTextBuffer> inputTextBuffer = nullptr, int eventId = 0, std::shared_ptr<TextHandler> handler = nullptr, std::shared_ptr<ContextTime> contextTime = nullptr) : inputBuffer(inputBuffer), inputTextBuffer(inputTextBuffer), mism(eventId), eventId(eventId), store(EventStore::getInstance()), handler(handler), contextTime(contextTime) {}

    /** \brief Empty destructor.
     */
    ~InputEventGenerator() = default;

    //void addManager(std::shared_ptr<InputStatusManager> manager) {;}

    /** Will search for input events occurred between initTime and finalTime and send it to the EventStore.
     * \param initTime Time from which events are generated
     * \param endTime Time until the events are generated
     */
    void run();
    inline HandlerTicket addHandler(uint32_t inputId, std::shared_ptr<InputHandler> handler) {
      mism.addHandler(inputId, handler);
    }

    /** Remove a handler from an input event.
     * \param id Id of the key
     */
    inline void removeHandler(uint32_t inputId, HandlerTicket ticket) {
      mism.removeHandler(inputId, ticket);
    }

    /** Remove a handler from an input event.
     * \param id Id of the key
     */
    inline void disableHandler(uint32_t inputId, HandlerTicket ticket) {
      mism.disableHandler(inputId, ticket);
    }

    /** Remove a handler from an input event.
     * \param id Id of the key
     */
    inline void enableHandler(uint32_t inputId, HandlerTicket ticket) {
      mism.enableHandler(inputId, ticket);
    }

    /** Remove a handler from an input event.
     * \param id Id of the key
     */
    inline void moveHandler(uint32_t srcInputId, uint32_t dstInputId, HandlerTicket ticket) {
      mism.moveHandler(srcInputId, dstInputId, ticket);
    }

    inline void setTextHandler(std::shared_ptr<TextHandler> handler) {
      using namespace std::string_literals;
      if(handler != nullptr) {
        SysError::setError("InputEventGenerator already has a handler"s);
      }
      this->handler = handler;
    }

    inline void removeTextHandler() {
      this->handler = nullptr;
    }

    // TODO: añadir AnyInputStatusManager para teclado, raton, mando.... con sus metodos como los anteriores sin el "inputId" ¿Quizás deviceId?

  private:

    InputEventGenerator() : inputBuffer(nullptr), inputTextBuffer(nullptr), mism(), eventId(), store(EventStore::getInstance()), handler(nullptr), contextTime(nullptr) {}

    inline void setEventID(int eventId) {
      this->eventId = eventId;
      mism.setEventID(eventId);
    }

    inline void setInputBuffer(std::shared_ptr<InputBuffer> inputBuffer) {
      this->inputBuffer = inputBuffer;
    }

    inline void setInputTextBuffer(std::shared_ptr<InputTextBuffer> inputTextBuffer) {
      this->inputTextBuffer = inputTextBuffer;
    }

    inline void setContextTime(std::shared_ptr<ContextTime> contextTime) {
      this->contextTime = contextTime;
    }

    std::shared_ptr<InputBuffer> inputBuffer;
    std::shared_ptr<InputTextBuffer> inputTextBuffer;
    MappedInputStatusManager mism;
    uint64_t eventId;
    EventStore &store;
    std::shared_ptr<TextHandler> handler;
    std::shared_ptr<ContextTime> contextTime;
};

class ZBEAPI InputEventGeneratorFtry : public Factory {
public:

  /** \brief Builds a InputEventGenerator.
   *  \param name Name for the created InputEventGenerator.
   *  \param cfgId InputEventGenerator's configuration id.
   */
  void create(std::string name, uint64_t cfgId);

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId);

private:
  RsrcDictionary<uint64_t>& uintStore = RsrcDictionary<uint64_t>::getInstance();
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<InputEventGenerator>& iegRsrc = RsrcStore<InputEventGenerator>::getInstance();
  RsrcStore<ContextTime>& cTimeRsrc = RsrcStore<ContextTime>::getInstance();
  RsrcStore<InputBuffer>& ibuffRsrc = RsrcStore<InputBuffer>::getInstance();
  RsrcStore<InputTextBuffer>& itBuffRsrc = RsrcStore<InputTextBuffer>::getInstance();

};

}  // namespace zbe

#endif  // ZBE_CORE_EVENTS_GENERATORS_INPUTEVENTGENERATOR_H
