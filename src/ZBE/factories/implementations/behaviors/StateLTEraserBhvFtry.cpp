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

void StateLTEraserBhvFtry::create(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    int64_t limit = j["limit"];
    std::shared_ptr<StateLTEraser> seb = std::make_shared<StateLTEraser>(limit);
    uint64_t id = SysIdGenerator::getId();
    behaviorRsrc.insert(id, seb);
    dict.insert("Behavior."s + name, id);
    id = SysIdGenerator::getId();
    StateLTEraserRsrc.insert(id, seb);
    dict.insert("StateLTEraser."s + name, id);
  } else {
    SysError::setError("StateLTEraserBhvFtry config for "s + name + " not found."s);
  }
}

void StateLTEraserBhvFtry::setup(std::string, uint64_t) {}

}  // namespace zbe
