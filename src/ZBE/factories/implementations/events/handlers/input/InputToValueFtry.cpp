/**
 * Copyright 2012 Batis Degryll Ludo
 * @file InputToValue.cpp
 * @since 2019-01-31
 * @date 2019-01-31
 * @author Ludo Degryll Batis
 * @brief Factory for InputToValue.
 */

#include "ZBE/factories/implementations/events/handlers/input/InputToValueFtry.h"

namespace zbe {

void InputToValueFtry::create(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  std::shared_ptr<InputToValue> itv = std::make_shared<InputToValue>();

  uint64_t id = SysIdGenerator::getId();
  inputRsrc.insert(id, itv);
  dict.insert("InputHandler."s + name, id);
  id = SysIdGenerator::getId();
  itvRsrc.insert(id, itv);
  dict.insert("InputToValue."s + name, id);
}

void InputToValueFtry::setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      auto itv = itvRsrc.get("InputToValue."s + name);
      json valcfg = j["value"];
      if (valcfg.is_string()){
        itv->setValue(valueDRsrc.get("ValueD."s + valcfg.get<std::string>()));
      } else {
        SysError::setError("InputToValue handler value name for "s + name + " is invalid."s);
      }

    } else {
      SysError::setError("InputToValue config for "s + name + " not found."s);
    }
}

}  // namespace zbe
