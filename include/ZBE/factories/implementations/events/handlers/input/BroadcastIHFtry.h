/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BroadcastIHFtry.h
 * @since 2019-01-14
 * @date 2019-01-14
 * @author Ludo Degryll Batis
 * @brief Factory for BroadcastIH.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_INPUT_BROADCASTIHFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_INPUT_BROADCASTIHFTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/events/generators/InputEventGenerator.h"

#include "ZBE/events/handlers/input/BroadcastIH.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"
#include "ZBE/core/io/Input.h"

#include "ZBE/JSON/JSONFactory.h"

namespace zbe {

/** \brief Factory for BroadcastIH.
 */
class ZBEAPI BroadcastIHFtry : virtual public Factory {
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
  RsrcStore<InputHandler> &inputRsrc = RsrcStore<InputHandler>::getInstance();
  RsrcStore<BroadcastIH> &bihRsrc = RsrcStore<BroadcastIH>::getInstance();
  RsrcDictionary<ZBE_K> &keyDict           = RsrcDictionary<ZBE_K>::getInstance();
  RsrcStore<InputEventGenerator>& iegStore = RsrcStore<InputEventGenerator>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_INPUT_BROADCASTIHFTRY_H_
