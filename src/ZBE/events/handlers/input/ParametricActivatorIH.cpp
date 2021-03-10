/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ParametricActivatorIH.cpp
 * @since 2017-07-05
 * @date 2017-07-05
 * @author Batis Degrill Ludo
 * @brief Handler that stores input value to a Value<double>
 */

#include "ZBE/events/handlers/input/ParametricActivatorIH.h"

 namespace zbe {

 void ParametricActivatorIHFtry::create(std::string name, uint64_t) {
   using namespace std::string_literals;

   auto ih = std::shared_ptr<ParametricActivatorIH>(new ParametricActivatorIH);
   ihStore.insert("InputHandler."s + name, ih);
   paihStore.insert("ParametricActivatorIH."s + name, ih);
 }

 void ParametricActivatorIHFtry::setup(std::string name, uint64_t cfgId) {
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
     ieg->addHandler(key, ih);

   } else {
     SysError::setError("ParametricActivatorIHFtry config for "s + name + " not found."s);
   }
 }

 } // namespace zbe
