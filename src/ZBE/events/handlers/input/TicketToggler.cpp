/**
 * Copyright 2012 Batis Degryll Ludo
 * @file TicketTogglerIH.cpp
 * @since 2017-07-05
 * @date 2017-07-05
 * @author Batis Degrill Ludo
 * @brief Handler that stores input value to a Value<double>
 */

#include "ZBE/events/handlers/input/TicketTogglerIH.h"

 namespace zbe {

 void TicketTogglerIHFtry::create(std::string name, uint64_t) {
   using namespace std::string_literals;

   auto ih = std::shared_ptr<TicketTogglerIH>(new TicketTogglerIH);
   ihRsrc.insert("InputHandler."s + name, ih);
   ttihRsrc.insert("TicketTogglerIH."s + name, ih);
 }

 void TicketTogglerIHFtry::setup(std::string name, uint64_t cfgId) {
   using namespace std::string_literals;
   using namespace nlohmann;
   std::shared_ptr<json> cfg = configRsrc.get(cfgId);

   if(cfg) {
     auto j = *cfg;
     if (!j["ticket"].is_string()) {
       SysError::setError("TicketTogglerIHFtry config for ticket: "s + j["ticket"].get<std::string>() + ": must be a ticket name."s);
       return;
     }

     std::string ticketName = j["ticket"].get<std::string>();
     if(!ticketStore.contains(ticketName)) {
       SysError::setError("TicketTogglerIHFtry config for ticket: "s + ticketName + " is not a ticket name."s);
       return;
     }

     if (!j["inputEventGenerator"].is_string()) {
       SysError::setError("TicketTogglerIHFtry config for inputEventGenerator: "s + j["inputEventGenerator"].get<std::string>() + ": must be an inputEventGenerator name."s);
       return;
     }

     std::string inputEventGeneratorName = j["inputEventGenerator"].get<std::string>();
     if(!iegStore.contains("InputEventGenerator."s + inputEventGeneratorName)) {
       SysError::setError("TicketTogglerIHFtry config for inputEventGenerator: "s + inputEventGeneratorName + " is not an inputEventGenerator name."s);
       return;
     }

     if (!j["key"].is_string()) {
       SysError::setError("TicketTogglerIHFtry config for key: "s + j["key"].get<std::string>() + ": must be a key name."s);
       return;
     }

     std::string keyName = j["key"].get<std::string>();
     if(!keyStore.contains(keyName)) {
       SysError::setError("TicketTogglerIHFtry config for key: "s + keyName + " is not a key name."s);
       return;
     }

     auto ticket = ticketStore.get(ticketName);
     auto ieg    = iegStore.get("InputEventGenerator."s + inputEventGeneratorName);
     auto key    = keyStore.get(keyName);
     auto ih     = ttihRsrc.get("TicketTogglerIH."s + name);

     ih->setTicket(ticket);
     ieg->addHandler(key, ih);

   } else {
     SysError::setError("TicketTogglerIHFtry config for "s + name + " not found."s);
   }
 }

 } // namespace zbe
