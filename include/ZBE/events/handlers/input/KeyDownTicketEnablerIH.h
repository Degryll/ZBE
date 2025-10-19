/**
 * Copyright 2012 Batis Degryll Ludo
 * @file KeyDownTicketEnablerIH.h
 * @since 2017-07-05
 * @date 2017-07-05
 * @author Batis Degrill Ludo
 * @brief Handler that stores input value to a Value<double>
 */

#ifndef ZBE_EVENTS_HANDLERS_KEYDOWNTICKETENABLERIH_H_
#define ZBE_EVENTS_HANDLERS_KEYDOWNTICKETENABLERIH_H_

#include <cstdio>
#include <cstdlib>
#include <memory>
#include <nlohmann/json.hpp>

#include "ZBE/factories/Factory.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/Ticket.h"

#include "ZBE/core/events/generators/InputEventGenerator.h"
#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/io/Input.h"

#include "ZBE/core/system/system.h"
#include "ZBE/core/system/SysError.h"

namespace zbe {

class KeyDownTicketEnablerIHFtry;

/** \brief Handler that stores input value to a Value<double>
 */
class KeyDownTicketEnablerIH : public InputHandler {
public:
  friend class KeyDownTicketEnablerIHFtry;

  /** brief Parametrized constructor
    * param value where to store input.
   */
  explicit KeyDownTicketEnablerIH(std::shared_ptr<Ticket> ticket) : ticket(ticket) {}

  /** \brief Set Value<double> where input will be stored.
   *  \param value where input will be stored.
   */
  void setTicket(std::shared_ptr<Ticket> ticket) {
    this->ticket = ticket;
  }

  /** brief stores input value to the value.
    * param status value from input.
   */
  void run(uint32_t, float status) override {
    if (status < 0.5f) {
      ticket->setINACTIVE();
    } else {
      ticket->setACTIVE();
    }

  }

private:
DISABLE_DLL_WARN
  KeyDownTicketEnablerIH() : ticket(nullptr) {}
  std::shared_ptr<Ticket> ticket;
DISABLE_WARNING_POP()
};

class KeyDownTicketEnablerIHFtry : public Factory {

  /** \brief Builds a SDLWindow.
   *  \param name Name for the created SDLWindow.
   *  \param cfgId SDLWindow's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    std::shared_ptr<KeyDownTicketEnablerIH> ih(new KeyDownTicketEnablerIH);
    ihRsrc.insert("InputHandler."s + name, ih);
    ttihRsrc.insert("KeyDownTicketEnablerIH."s + name, ih);
  }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      if (!j["ticket"].is_string()) {
        SysError::setError("KeyDownTicketEnablerIHFtry config for ticket: "s + j["ticket"].get<std::string>() + ": must be a ticket name."s);
        return;
      }

      std::string ticketName = j["ticket"].get<std::string>();
      if(!ticketStore.contains(ticketName)) {
        SysError::setError("KeyDownTicketEnablerIHFtry config for ticket: "s + ticketName + " is not a ticket name."s);
        return;
      }

      if (!j["inputEventGenerator"].is_string()) {
        SysError::setError("KeyDownTicketEnablerIHFtry config for inputEventGenerator: "s + j["inputEventGenerator"].get<std::string>() + ": must be an inputEventGenerator name."s);
        return;
      }

      std::string inputEventGeneratorName = j["inputEventGenerator"].get<std::string>();
      if(!iegStore.contains("InputEventGenerator."s + inputEventGeneratorName)) {
        SysError::setError("KeyDownTicketEnablerIHFtry config for inputEventGenerator: "s + inputEventGeneratorName + " is not an inputEventGenerator name."s);
        return;
      }

      if (!j["key"].is_string()) {
        SysError::setError("KeyDownTicketEnablerIHFtry config for key: "s + j["key"].get<std::string>() + ": must be a key name."s);
        return;
      }

      std::string keyName = j["key"].get<std::string>();
      if(!keyStore.contains(keyName)) {
        SysError::setError("KeyDownTicketEnablerIHFtry config for key: "s + keyName + " is not a key name."s);
        return;
      }

      auto ticket = ticketStore.get(ticketName);
      auto ieg    = iegStore.get("InputEventGenerator."s + inputEventGeneratorName);
      auto key    = keyStore.get(keyName);
      auto ih     = ttihRsrc.get("KeyDownTicketEnablerIH."s + name);

      ih->setTicket(ticket);
      ieg->addHandler(key, ih);

    } else {
      SysError::setError("KeyDownTicketEnablerIHFtry config for "s + name + " not found."s);
    }
  }


private:
  RsrcStore<nlohmann::json> &configRsrc    = RsrcStore<nlohmann::json>::getInstance();
  RsrcDictionary<ZBE_K>& keyStore          = RsrcDictionary<ZBE_K>::getInstance();
  RsrcStore<KeyDownTicketEnablerIH>& ttihRsrc     = RsrcStore<KeyDownTicketEnablerIH>::getInstance();
  RsrcStore<InputHandler>& ihRsrc          = RsrcStore<InputHandler>::getInstance();
  RsrcStore<Ticket>& ticketStore           = RsrcStore<Ticket>::getInstance();
  RsrcStore<InputEventGenerator>& iegStore = RsrcStore<InputEventGenerator>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_KEYDOWNTICKETENABLERIH_H_
