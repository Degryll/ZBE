/**
 * Copyright 2012 Batis Degryll Ludo
 * @file TicketEraserFtry.cpp
 * @since 2018-12-24
 * @date 2018-12-24
 * @author Ludo Degryll Batis
 * @brief Factory for TicketEraser.
 */

#include "ZBE/factories/implementations/events/handlers/time/TicketEraserFtry.h"

namespace zbe {

void TicketEraserFtry::create(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    if (j["ticket"].is_string()) {
      std::string tname = j["ticket"].get<std::string>();
      uint64_t tId = dict.get("Ticket."s + tname);
      std::shared_ptr<Ticket> ticket = ticketRsrc.get(tId);
      std::shared_ptr<TicketEraser> te = std::make_shared<TicketEraser>(ticket);
      timeRsrc.insert("TimeHandler."s + name, te);
      timeEraserRsrc.insert("TicketEraser."s + name, te);
    } else {
      SysError::setError("TicketEraserFtry config for "s + j["ticket"].get<std::string>() + ": must be a string."s);
    }
  } else {
    SysError::setError("TicketEraserFtry config for "s + name + " not found."s);
  }
}

void TicketEraserFtry::setup(std::string, uint64_t) {}

}  // namespace zbe
