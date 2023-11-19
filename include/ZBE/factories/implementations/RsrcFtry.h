/**
 * Copyright 2012 Batis Degryll Ludo
 * @file RsrcFtry.h
 * @since 2019-04-21
 * @date 2019-04-21
 * @author Ludo Degryll Batis
 * @brief Factory that executes a resource loader over a directory.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_RSRCFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_RSRCFTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"
#include "ZBE/core/system/SysTime.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/system/system.h"

#include "ZBE/resources/loaders/RsrcLoader.h"
#include "ZBE/resources/loaders/RsrcFolderLoader.h"

#include "ZBE/factories/Factory.h"


namespace zbe {

/** \brief Factory for RsrcLoaderDmn.
 */
class ZBEAPI RsrcFtry : virtual public Factory {
public:

  /** \brief Builds a RsrcFtry.
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
  RsrcStore<RsrcLoader> &rsrcLoaderRsrc = RsrcStore<RsrcLoader>::getInstance();

};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_RSRCFTRY_H_
