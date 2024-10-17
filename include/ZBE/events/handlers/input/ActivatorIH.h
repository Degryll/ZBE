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
  ActivatorIH(std::shared_ptr<Ticket> ticket) : ticket(ticket) {}

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
    if (!status) {
      ticket->setACTIVE();
    }
  }

private:
  ActivatorIH() : ticket(nullptr) {}
  std::shared_ptr<Ticket> ticket;
};

class ZBEAPI ActivatorIHFtry : public Factory {


  void create(std::string name, uint64_t) override;

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override;

private:
  RsrcStore<nlohmann::json> &configStore         = RsrcStore<nlohmann::json>::getInstance();
  RsrcDictionary<std::string>& strDict           = RsrcDictionary<std::string>::getInstance();
  RsrcDictionary<ZBE_K>& keyDict                 = RsrcDictionary<ZBE_K>::getInstance();
  RsrcStore<ActivatorIH>& paihStore              = RsrcStore<ActivatorIH>::getInstance();
  RsrcStore<InputHandler>& ihStore               = RsrcStore<InputHandler>::getInstance();
  RsrcStore<Ticket>& ticketStore                 = RsrcStore<Ticket>::getInstance();
  RsrcStore<InputEventGenerator>& iegStore       = RsrcStore<InputEventGenerator>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_ACTIVATORIH_H_
