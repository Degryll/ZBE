/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ActivatorIH.cpp
 * @since 2017-07-05
 * @date 2017-07-05
 * @author Batis Degrill Ludo
 * @brief Handler that stores input value to a Value<double>
 */

#include "ZBE/events/handlers/input/ActivatorIH.h"

 namespace zbe {

 void ActivatorIHFtry::create(std::string name, uint64_t) {
   using namespace std::string_literals;

   auto ih = std::shared_ptr<ActivatorIH>(new ActivatorIH);
   ihStore.insert("InputHandler."s + name, ih);
   paihStore.insert("ActivatorIH."s + name, ih);
 }

 void ActivatorIHFtry::setup(std::string name, uint64_t cfgId) {
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

 } // namespace zbe
