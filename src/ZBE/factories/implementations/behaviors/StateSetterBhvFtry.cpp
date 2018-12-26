/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StateSetterBhvFtry.cpp
 * @since 2018-12-13
 * @date 2018-12-13
 * @author Ludo Degryll Batis
 * @brief Factory for State Setter Behavior.
 */

#include "ZBE/factories/implementations/behaviors/StateSetterBhvFtry.h"

namespace zbe {

void StateSetterBhvFtry::create(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    if (j["state"].is_string()) {
      std::string cname = j["state"].get<std::string>();
      uint64_t state = dict.get(cname);
      std::shared_ptr<StateSetter> seb = std::make_shared<StateSetter>(state);
      behaviorRsrc.insert("Behavior."s + name, seb);
      StateSetterRsrc.insert("StateSetter."s + name, seb);
    } else {
      SysError::setError("StateSetterBhvFtry config for "s + j["state"].get<std::string>() + ": must be a string."s);
    }
  } else {
    SysError::setError("StateSetterBhvFtry config for "s + name + " not found."s);
  }
}

void StateSetterBhvFtry::setup(std::string, uint64_t) {}

}  // namespace zbe
