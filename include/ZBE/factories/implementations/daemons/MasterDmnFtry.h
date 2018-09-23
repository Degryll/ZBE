/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MasterDmnFtry.h
 * @since 2018-09-05
 * @date 2018-09-05
 * @author Ludo Degryll Batis
 * @brief Factory for Daemon Masters.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_MASTERDMNFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_MASTERDMNFTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/daemons/DaemonMaster.h"

#include "ZBE/factories/Factory.h"

namespace zbe {

/** \brief Factory for Master Daemons.
 */
class MasterDmnFtry : public Factory {
public:

  /** \brief Builds a MasterDmnFtry.
   *  \param name Name for the created MasterDmnFtry.
   *  \param cfgId MasterDmnFtry's configuration id.
   */
  void build(std::string name, uint64_t cfgId);

private:
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon> &daemonRsrc = RsrcStore<Daemon>::getInstance();

};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_MASTERDMNFTRY_H_
