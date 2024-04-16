/**
 * Copyright 2012 Batis Degryll Ludo
 * @file TicketEraserFtry.h
 * @since 2018-12-24
 * @date 2018-12-24
 * @author Ludo Degryll Batis
 * @brief Factory for TicketEraser.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_TIME_TICKETERASERFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_TIME_TICKETERASERFTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/tools/containers/Ticket.h"

#include "ZBE/core/events/handlers/TimeHandler.h"

#include "ZBE/events/handlers/time/TicketEraser.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for TicketEraser.
 */
class ZBEAPI TicketEraserFtry : virtual public Factory {
public:

/** \brief Create the desired tool, probably incomplete.
 *  \param name Name for the created tool.
 *  \param cfgId Tool's configuration id.
 */
  void create(std::string name, uint64_t);

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId);

private:
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Ticket> &ticketRsrc = RsrcStore<Ticket>::getInstance();
  RsrcStore<TimeHandler> &timeRsrc = RsrcStore<TimeHandler>::getInstance();
  RsrcStore<TicketEraser> &timeEraserRsrc = RsrcStore<TicketEraser>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_TIME_TICKETERASERFTRY_H_
