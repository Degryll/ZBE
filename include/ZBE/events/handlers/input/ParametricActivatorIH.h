/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ParametricActivatorIH.h
 * @since 2017-07-05
 * @date 2017-07-05
 * @author Batis Degrill Ludo
 * @brief Handler that stores input value to a Value<double>
 */

#ifndef ZBE_EVENTS_HANDLERS_PARAMETRICACTIVATORIH_H_
#define ZBE_EVENTS_HANDLERS_PARAMETRICACTIVATORIH_H_

#include <cstdio>
#include <cstdlib>
#include <memory>
#include <nlohmann/json.hpp>

#include "ZBE/factories/Factory.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/Ticket.h"
#include "ZBE/core/tools/Parametric.h"

#include "ZBE/core/events/generators/InputEventGenerator.h"
#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/io/Input.h"

#include "ZBE/core/system/system.h"
#include "ZBE/core/system/SysError.h"

namespace zbe {

class ParametricActivatorIHFtry;

/** \brief Handler that stores input value to a Value<double>
 */
class ParametricActivatorIH : public InputHandler {
public:
  friend class ParametricActivatorIHFtry;

  /** brief Parametrized constructor
    * param value where to store input.
   */
  ParametricActivatorIH(std::shared_ptr<Ticket> ticket, std::shared_ptr<Parametric<float> > parametric) : ticket(ticket), parametric(parametric) {}

  /** \brief Set Value<double> where input will be stored.
   *  \param ticket ticket to be activated
   */
  void setTicket(std::shared_ptr<Ticket> ticket) {
    this->ticket = ticket;
  }

  /** \brief Set Value<double> where input will be stored.
   *  \param parametric parametric to be set
   */
  void setParametric(std::shared_ptr<Parametric<float> > parametric) {
    this->parametric = parametric;
  }

  /** brief stores input value to the value.
    * param status value from input.
   */
  void run(uint32_t, float status) override {
    ticket->setACTIVE();
    parametric->set(status);
  }

private:
DISABLE_DLL_WARN
  ParametricActivatorIH() : ticket(nullptr), parametric(nullptr) {}
  std::shared_ptr<Ticket> ticket;
  std::shared_ptr<Parametric<float> > parametric;
DISABLE_WARNING_POP()
};

class ParametricActivatorIHFtry : public Factory {


  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    std::shared_ptr<ParametricActivatorIH> ih(new ParametricActivatorIH);
    ihStore.insert("InputHandler."s + name, ih);
    paihStore.insert("ParametricActivatorIH."s + name, ih);
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
        SysError::setError("ParametricActivatorIHFtry config for ticket: "s + j["ticket"].get<std::string>() + ": must be a ticket name."s);
        return;
      }
      std::string ticketName = j["ticket"].get<std::string>();
      if(!ticketStore.contains(ticketName)) {
        SysError::setError("ParametricActivatorIHFtry config for ticket: "s + ticketName + " is not a ticket name."s);
        return;
      }
      if (!j["parametric"].is_string()) {
        SysError::setError("ParametricActivatorIHFtry config for parametric: "s + j["parametric"].get<std::string>() + ": must be a ticket name."s);
        return;
      }

      std::string parametricName = j["parametric"].get<std::string>();
      if(!parametricStore.contains("Parametric."s + parametricName)) {
        SysError::setError("ParametricActivatorIHFtry config for parametric: "s + parametricName + " is not a ticket name."s);
        return;
      }

      if (!j["inputEventGenerator"].is_string()) {
        SysError::setError("ParametricActivatorIHFtry config for inputEventGenerator: "s + j["inputEventGenerator"].get<std::string>() + ": must be an inputEventGenerator name."s);
        return;
      }

      std::string inputEventGeneratorName = j["inputEventGenerator"].get<std::string>();
      if(!iegStore.contains("InputEventGenerator."s + inputEventGeneratorName)) {
        SysError::setError("ParametricActivatorIHFtry config for inputEventGenerator: "s + inputEventGeneratorName + " is not an inputEventGenerator name."s);
        return;
      }

      if (!j["key"].is_string()) {
        SysError::setError("ParametricActivatorIHFtry config for key: "s + j["key"].get<std::string>() + ": must be a key name."s);
        return;
      }

      std::string keyName = j["key"].get<std::string>();
      if(!keyDict.contains(keyName)) {
        SysError::setError("ParametricActivatorIHFtry config for key: "s + keyName + " is not a key name."s);
        return;
      }

      // TODO Asegurar que se guardar el comportamiento como parametrico.
      auto ticket = ticketStore.get(ticketName);
      auto parametric = parametricStore.get("Parametric."s + parametricName);
      auto ieg    = iegStore.get("InputEventGenerator."s + inputEventGeneratorName);
      auto key    = keyDict.get(keyName);
      auto ih     = paihStore.get("ParametricActivatorIH."s + name);

      ih->setTicket(ticket);
      ih->setParametric(parametric);
      auto handlerTicket = ieg->addHandler(key, ih);
      SysError::setDebug("ParametricActivatorIH HandlerTicket."s +name + " created and configured."s, false);
      handlerTicketStore.insert("HandlerTicket."s + name, handlerTicket);
    } else {
      SysError::setError("ParametricActivatorIHFtry config for "s + name + " not found."s);
    }
  }

private:
  RsrcStore<nlohmann::json> &configStore         = RsrcStore<nlohmann::json>::getInstance();
  RsrcDictionary<ZBE_K>& keyDict                 = RsrcDictionary<ZBE_K>::getInstance();
  RsrcStore<ParametricActivatorIH>& paihStore    = RsrcStore<ParametricActivatorIH>::getInstance();
  RsrcStore<InputHandler>& ihStore               = RsrcStore<InputHandler>::getInstance();
  RsrcStore<Ticket>& ticketStore                 = RsrcStore<Ticket>::getInstance();
  RsrcStore<InputEventGenerator>& iegStore       = RsrcStore<InputEventGenerator>::getInstance();
  RsrcStore<Parametric<float> >& parametricStore = RsrcStore<Parametric<float> >::getInstance();
  RsrcStore<HandlerTicket>& handlerTicketStore = RsrcStore<HandlerTicket>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_PARAMETRICACTIVATORIH_H_
