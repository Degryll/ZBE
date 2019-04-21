/**
 * Copyright 2012 Batis Degryll Ludo
 * @file RsrcFolderLoaderDmnFtry.cpp
 * @since 2019-04-21
 * @date 2019-04-21
 * @author Ludo Degryll Batis
 * @brief Factory for RsrcLoaderDmn.
 */


#include "ZBE/factories/implementations/daemons/RsrcFolderLoaderDmnFtry.h"

namespace zbe {

void RsrcFolderLoaderDmnFtry::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  auto rfld = std::make_shared<RsrcFolderLoaderDmn>();
  uint64_t id = SysIdGenerator::getId();
  daemonRsrc.insert(id, rfld);
  dict.insert("Daemon."s + name, id);
  id = SysIdGenerator::getId();
  rsrcFolderLoaderDmnRsrc.insert(id, rfld);
  dict.insert("RsrcFolderLoaderDmn."s + name, id);
}

void RsrcFolderLoaderDmnFtry::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    json rsrcFolderLoaderName = j["rsrcFolderLoader"];
    json url = j["url"];
    if(!rsrcFolderLoaderName.is_string()) {
      SysError::setError("Bad config for RsrcFolderLoaderDmnFtry - rsrcLoader. "s + name);
      return;
    }
    if(!url.is_string()) {
      SysError::setError("Bad config for RsrcFolderLoaderDmnFtry - url. "s + name);
      return;
    }
    auto rfld = rsrcFolderLoaderDmnRsrc.get("RsrcFolderLoaderDmn."s + name);
    auto rfl = rsrcFolderLoaderRsrc.get("RsrcFolderLoader."s + rsrcFolderLoaderName.get<std::string>());

    rfld->setRsrcFolderLoader(rfl);
    rfld->setUrl(url);
  } else {
    SysError::setError("RsrcLoaderDmnFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe
