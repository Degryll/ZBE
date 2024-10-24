/**
 * Copyright 2012 Batis Degryll Ludo
 * @file RsrcFolderLoaderDmnFtry.h
 * @since 2019-04-21
 * @date 2019-04-21
 * @author Ludo Degryll Batis
 * @brief Factory for RsrcLoaderDmn.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_DAEMONS_RSRCFOLDERLOADERDMNFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_DAEMONS_RSRCFOLDERLOADERDMNFTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"
#include "ZBE/core/system/SysTime.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/system/system.h"

#include "ZBE/daemons/RsrcFolderLoaderDmn.h"

#include "ZBE/factories/Factory.h"


namespace zbe {

/** \brief Factory for RsrcLoaderDmn.
 */
class ZBEAPI RsrcFolderLoaderDmnFtry : virtual public Factory {
public:

  /** \brief Builds a RsrcFolderLoaderDmn.
   *  \param name Name for the created RsrcLoaderDmn.
   *  \param cfgId RsrcLoaderDmn's configuration id.
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
  RsrcStore<Daemon> &daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<RsrcFolderLoaderDmn> &rsrcFolderLoaderDmnRsrc = RsrcStore<RsrcFolderLoaderDmn>::getInstance();
  RsrcStore<RsrcLoader> &rsrcLoaderRsrc = RsrcStore<RsrcLoader>::getInstance();

};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_DAEMONS_RSRCFOLDERLOADERDMNFTRY_H_
