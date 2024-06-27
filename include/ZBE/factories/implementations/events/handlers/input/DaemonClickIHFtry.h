/**
 * Copyright 2012 Batis Degryll Ludo
 * @file DaemonClickIHFtry.h
 * @since 2019-01-24
 * @date 2019-01-24
 * @author Ludo Degryll Batis
 * @brief Factory for DaemonClickIH.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_INPUT_DAEMONCLICKIHFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_INPUT_DAEMONCLICKIHFTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/events/handlers/InputHandler.h"

#include "ZBE/events/handlers/input/DaemonClickIH.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for DaemonClickIH.
 */
class ZBEAPI DaemonClickIHFtry : virtual public Factory {
public:

/** \brief Create the desired tool, probably incomplete.
 *  \param name Name for the created tool.
 *  \param cfgId Tool's configuration id.
 */
  void create(std::string name, uint64_t) override;

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId);

private:
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<InputHandler> &inputRsrc = RsrcStore<InputHandler>::getInstance();
  RsrcStore<DaemonClickIH> &dcihRsrc = RsrcStore<DaemonClickIH>::getInstance();
  RsrcStore<Daemon> &daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<Value<double> > &valueDRsrc = RsrcStore<Value<double> >::getInstance();
};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_INPUT_DAEMONCLICKIHFTRY_H_
