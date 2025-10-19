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
class RsrcFolderLoaderDmnFtry : virtual public Factory {
public:

  /** \brief Builds a RsrcFolderLoaderDmn.
   *  \param name Name for the created RsrcLoaderDmn.
   *  \param cfgId RsrcLoaderDmn's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    auto rfld = std::make_shared<RsrcFolderLoaderDmn>();
    uint64_t id = SysIdGenerator::getId();
    daemonRsrc.insert(id, rfld);
    dict.insert("Daemon."s + name, id);
    id = SysIdGenerator::getId();
    rsrcFolderLoaderDmnRsrc.insert(id, rfld);
    dict.insert("RsrcFolderLoaderDmn."s + name, id);
  }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      json loaderName = j["loader"];
      json url = j["url"];
      if(!loaderName.is_string()) {
        SysError::setError("Bad config for RsrcFolderLoaderDmnFtry - loaderName. "s + name);
        return;
      }
      if(!url.is_string()) {
        SysError::setError("Bad config for RsrcFolderLoaderDmnFtry - url. "s + name);
        return;
      }
      auto rfld = rsrcFolderLoaderDmnRsrc.get("RsrcFolderLoaderDmn."s + name);
      auto rl = rsrcLoaderRsrc.get("RsrcLoader."s + loaderName.get<std::string>());
      auto rsrcfl = std::make_shared<zbe::RsrcFolderLoader>(rl);
      rsrcfl->setRsrcLoader(rl);
      rfld->setRsrcFolderLoader(rsrcfl);
      rfld->setUrl(url);
    } else {
      SysError::setError("RsrcLoaderDmnFtry config for "s + name + " not found."s);
    }
  }

private:
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon> &daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<RsrcFolderLoaderDmn> &rsrcFolderLoaderDmnRsrc = RsrcStore<RsrcFolderLoaderDmn>::getInstance();
  RsrcStore<RsrcLoader> &rsrcLoaderRsrc = RsrcStore<RsrcLoader>::getInstance();

};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_DAEMONS_RSRCFOLDERLOADERDMNFTRY_H_
