/**
 * Copyright 2012 Batis Degryll Ludo
 * @file RsrcLoaderDmnFtry.cpp
 * @since 2019-04-21
 * @date 2019-04-21
 * @author Ludo Degryll Batis
 * @brief Factory for RsrcLoaderDmn.
 */


#include "ZBE/factories/implementations/daemons/RsrcLoaderDmnFtry.h"

namespace zbe {

void RsrcLoaderDmnFtry::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  auto rld = std::make_shared<RsrcLoaderDmn>();
  uint64_t id = SysIdGenerator::getId();
  daemonRsrc.insert(id, rld);
  dict.insert("Daemon."s + name, id);
  id = SysIdGenerator::getId();
  rsrcLoaderDmnRsrc.insert(id, rld);
  dict.insert("RsrcLoaderDmn."s + name, id);
}

void RsrcLoaderDmnFtry::setup(std::string name, uint64_t cfgId) {
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

}  // namespace zbe
