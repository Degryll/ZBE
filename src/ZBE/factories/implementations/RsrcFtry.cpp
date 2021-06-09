/**
 * Copyright 2012 Batis Degryll Ludo
 * @file RsrcFolderLoaderDmnFtry.cpp
 * @since 2019-04-21
 * @date 2019-04-21
 * @author Ludo Degryll Batis
 * @brief Factory for RsrcLoaderDmn.
 */


#include "ZBE/factories/implementations/RsrcFtry.h"

namespace zbe {

void RsrcFtry::create(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    json loaderName = j["loader"];
    json url = j["url"];
    if(!loaderName.is_string()) {
      SysError::setError("Bad config for RsrcFtry - loaderName. "s + name);
      return;
    }
    if(!url.is_string()) {
      SysError::setError("Bad config for RsrcFolderLoaderDmnFtry - url. "s + name);
      return;
    }
    auto rl = rsrcLoaderRsrc.get("RsrcLoader."s + loaderName.get<std::string>());
    RsrcFolderLoader rsrcfl(rl);

    rsrcfl.load(url);
  } else {
    SysError::setError("RsrcFtry config for "s + name + " not found."s);
  }

}

void RsrcFtry::setup(std::string, uint64_t) {}

}  // namespace zbe
