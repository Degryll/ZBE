/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ActivatorIH.h
 * @since 2017-07-05
 * @date 2017-07-05
 * @author Batis Degrill Ludo
 * @brief Handler that stores input value to a Value<double>
 */

#ifndef ZBE_EVENTS_HANDLERS_ACTIVATORIH_H_
#define ZBE_EVENTS_HANDLERS_ACTIVATORIH_H_

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

class ActivatorIHFtry;

/** \brief Handler that stores input value to a Value<double>
 */
class ActivatorIH : public InputHandler {
public:
  friend class ActivatorIHFtry;

  /** brief Parametrized constructor
    * param value where to store input.
   */
  explicit ActivatorIH(std::shared_ptr<Ticket> ticket) : ticket(ticket) {}

  /** \brief Set Value<double> where input will be stored.
   *  \param ticket ticket to be activated
   */
  void setTicket(std::shared_ptr<Ticket> ticket) {
    this->ticket = ticket;
  }

  /** brief stores input value to the value.
    * param status value from input.
   */
  void run(uint32_t, float status) override {
    if (status==0.0f) {
      ticket->setACTIVE();
    }
  }

private:
DISABLE_DLL_WARN
  ActivatorIH() : ticket(nullptr) {}
  std::shared_ptr<Ticket> ticket;
DISABLE_WARNING_POP()
};

class ActivatorIHFtry : public Factory {


  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    std::shared_ptr<ActivatorIH> ih(new ActivatorIH);
    ihStore.insert("InputHandler."s + name, ih);
    paihStore.insert("ActivatorIH."s + name, ih);
  }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configStore.get(cfgId);
    if(cfg) {
      auto j = *cfg;
      if (!j["ticket"].is_string()) {
        SysError::setError("ActivatorIHFtry config for ticket: "s + j["ticket"].get<std::string>() + ": must be a ticket name."s);
        return;
      }
      std::string ticketName = j["ticket"].get<std::string>();
      if(!ticketStore.contains(ticketName)) {
        SysError::setError("ActivatorIHFtry config for ticket: "s + ticketName + " is not a ticket name."s);
        return;
      }

      if (!j["inputEventGenerator"].is_string()) {
        SysError::setError("ActivatorIHFtry config for inputEventGenerator: "s + j["inputEventGenerator"].get<std::string>() + ": must be an inputEventGenerator name."s);
        return;
      }

      std::string inputEventGeneratorName = j["inputEventGenerator"].get<std::string>();
      if(!iegStore.contains("InputEventGenerator."s + inputEventGeneratorName)) {
        SysError::setError("ActivatorIHFtry config for inputEventGenerator: "s + inputEventGeneratorName + " is not an inputEventGenerator name."s);
        return;
      }

      if (!j["key"].is_string()) {
        SysError::setError("ActivatorIHFtry config for key: "s + j["key"].get<std::string>() + ": must be a key name."s);
        return;
      }

      std::string keyName = j["key"].get<std::string>();
      if(!keyDict.contains(keyName)) {
        SysError::setError("ActivatorIHFtry config for key: "s + keyName + " is not a key name."s);
        return;
      }

      auto ticket = ticketStore.get(ticketName);
      auto ieg    = iegStore.get("InputEventGenerator."s + inputEventGeneratorName);
      auto key    = keyDict.get(keyName);
      auto ih     = paihStore.get("ActivatorIH."s + name);

      ih->setTicket(ticket);
      ieg->addHandler(key, ih);

    } else {
      SysError::setError("ActivatorIHFtry config for "s + name + " not found."s);
    }
  }

private:
  RsrcStore<nlohmann::json> &configStore         = RsrcStore<nlohmann::json>::getInstance();
  RsrcDictionary<ZBE_K>& keyDict                 = RsrcDictionary<ZBE_K>::getInstance();
  RsrcStore<ActivatorIH>& paihStore              = RsrcStore<ActivatorIH>::getInstance();
  RsrcStore<InputHandler>& ihStore               = RsrcStore<InputHandler>::getInstance();
  RsrcStore<Ticket>& ticketStore                 = RsrcStore<Ticket>::getInstance();
  RsrcStore<InputEventGenerator>& iegStore       = RsrcStore<InputEventGenerator>::getInstance();
};

//TODO Si una clase está siendo referenciada desde algún cpp su factoría no puede estar en el mismo .h en el que se declara la clase 

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_ACTIVATORIH_H_
