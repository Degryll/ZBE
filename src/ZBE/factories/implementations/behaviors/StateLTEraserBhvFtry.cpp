/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StateLTEraserBhvFtry.cpp
 * @since 2018-11-05
 * @date 2018-11-05
 * @author Ludo Degryll Batis
 * @brief Factory for State less than Eraser Behavior.
 */

#include "ZBE/factories/implementations/behaviors/StateLTEraserBhvFtry.h"

namespace zbe {

void StateLTEraserBhvFtry::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  std::shared_ptr<StateLTEraser> seb = std::make_shared<StateLTEraser>();
  behaviorRsrc.insert("Behavior."s + name, seb);
  StateLTEraserRsrc.insert("StateLTEraser."s + name, seb);
}

void StateLTEraserBhvFtry::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    if (j["limit"].is_string()) {
      std::string cname = j["limit"].get<std::string>();
      uint64_t limit = (uint64_t)intStore.get(cname);

      auto ss = StateLTEraserRsrc.get("StateLTEraser."s + name);
      ss->setLimit(limit);

    } else {
      SysError::setError("StateLTEraserBhvFtry config for "s + j["limit"].get<std::string>() + ": must be a string."s);
    }
  } else {
    SysError::setError("StateLTEraserBhvFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe
