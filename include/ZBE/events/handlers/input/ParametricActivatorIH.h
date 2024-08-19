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
  void run(uint32_t, float status) {
    ticket->setACTIVE();
    parametric->set(status);
  }

private:
  ParametricActivatorIH() : ticket(nullptr), parametric(nullptr) {}
  std::shared_ptr<Ticket> ticket;
  std::shared_ptr<Parametric<float> > parametric;
};

class ZBEAPI ParametricActivatorIHFtry : public Factory {


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
  RsrcStore<ParametricActivatorIH>& paihStore    = RsrcStore<ParametricActivatorIH>::getInstance();
  RsrcStore<InputHandler>& ihStore               = RsrcStore<InputHandler>::getInstance();
  RsrcStore<Ticket>& ticketStore                 = RsrcStore<Ticket>::getInstance();
  RsrcStore<InputEventGenerator>& iegStore       = RsrcStore<InputEventGenerator>::getInstance();
  RsrcStore<Parametric<float> >& parametricStore = RsrcStore<Parametric<float> >::getInstance();
};

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_PARAMETRICACTIVATORIH_H_
