/**
 * Copyright 2012 Batis Degryll Ludo
 * @file RsrcLoaderDmnFtry.h
 * @since 2019-04-21
 * @date 2019-04-21
 * @author Ludo Degryll Batis
 * @brief Factory for RsrcLoaderDmn.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_DAEMONS_RSRCLOADERDMNFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_DAEMONS_RSRCLOADERDMNFTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"
#include "ZBE/core/system/SysTime.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/system/system.h"

#include "ZBE/daemons/RsrcLoaderDmn.h"

#include "ZBE/factories/Factory.h"


namespace zbe {

/** \brief Factory for RsrcLoaderDmn.
 */
class RsrcLoaderDmnFtry : virtual public Factory {
public:

  /** \brief Builds a RsrcLoaderDmn.
   *  \param name Name for the created RsrcLoaderDmn.
   *  \param cfgId RsrcLoaderDmn's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    auto rld = std::make_shared<RsrcLoaderDmn>();
    uint64_t id = SysIdGenerator::getId();
    daemonRsrc.insert(id, rld);
    dict.insert("Daemon."s + name, id);
    id = SysIdGenerator::getId();
    rsrcLoaderDmnRsrc.insert(id, rld);
    dict.insert("RsrcLoaderDmn."s + name, id);
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
      json rsrcLoaderName = j["rsrcLoader"];
      json url = j["url"];
      if(!rsrcLoaderName.is_string()) {
        SysError::setError("Bad config for RsrcLoaderDmnFtry - rsrcLoader. "s + name);
        return;
      }
      if(!url.is_string()) {
        SysError::setError("Bad config for RsrcLoaderDmnFtry - url. "s + name);
        return;
      }
      auto rld = rsrcLoaderDmnRsrc.get("RsrcLoaderDmn."s + name);
      auto rl = rsrcLoaderRsrc.get("RsrcLoader."s + rsrcLoaderName.get<std::string>());

      rld->setRsrcLoader(rl);
      rld->setUrl(url);
    } else {
      SysError::setError("RsrcLoaderDmnFtry config for "s + name + " not found."s);
    }
  }

private:
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon> &daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<RsrcLoaderDmn> &rsrcLoaderDmnRsrc = RsrcStore<RsrcLoaderDmn>::getInstance();
  RsrcStore<RsrcLoader> &rsrcLoaderRsrc = RsrcStore<RsrcLoader>::getInstance();

};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_DAEMONS_RSRCLOADERDMNFTRY_H_
