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

void StateSetterBhvFtry::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  std::shared_ptr<StateSetter> ss = std::make_shared<StateSetter>();
  behaviorRsrc.insert("Behavior."s + name, ss);
  StateSetterRsrc.insert("StateSetter."s + name, ss);
}

void StateSetterBhvFtry::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    if (j["state"].is_string()) {
      std::string cname = j["state"].get<std::string>();
      int64_t state = intStore.get(cname);

      auto ss = StateSetterRsrc.get("StateSetter."s + name);
      ss->setState(state);

    } else {
      SysError::setError("StateSetterBhvFtry config for "s + j["state"].get<std::string>() + ": must be a string."s);
    }
  } else {
    SysError::setError("StateSetterBhvFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe
