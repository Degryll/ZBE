/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MainLoopFtry.cpp
 * @since 2018-09-19
 * @date 2018-09-19
 * @author Ludo Degryll Batis
 * @brief Factory for Main Loop.
 */

#include "ZBE/factories/implementations/daemons/MainLoopExitFtry.h"

namespace zbe {

void MainLoopExitFtry::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  auto ml = std::make_shared<MainLoopExit>();
  uint64_t id = SysIdGenerator::getId();
  daemonRsrc.insert(id, ml);
  dict.insert("Daemon."s + name, id);
  id = SysIdGenerator::getId();
  mainLoopExitRsrc.insert(id, ml);
  dict.insert("MainLoopExit."s + name, id);
}

void MainLoopExitFtry::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    json mainloopName = j["mainloop"];
    json valueHolderName = j["valueHolder"];
    json outValueName = j["outValue"];
    if(!mainloopName.is_string()) {
      SysError::setError("Bad config for MainLoopExitFtry - mainloop."s + name);
      return;
    }
    if(!valueHolderName.is_string()) {
      SysError::setError("Bad config for MainLoopExitFtry - valueHolder."s + name);
      return;
    }
    //TODO allow to use numbers or strings
    // if(!outValue.is_number()) {
    //   SysError::setError("Bad config for MainLoopExitFtry - outValue."s + name);
    //   return;
    // }
    if(!outValueName.is_string()) {
      SysError::setError("Bad config for MainLoopExitFtry - outValue."s + name);
      return;
    }
    auto mle = mainLoopExitRsrc.get("MainLoopExit."s + name);
    auto ml = mainLoopRsrc.get("MainLoop."s + mainloopName.get<std::string>());
    auto valueHolder = valueRsrc.get(valueHolderName.get<std::string>());
    uint64_t value = uintStore.get(outValueName.get<std::string>());
    mle->setMainLoop(ml);
    mle->setValue(valueHolder);
    mle->setExitValue(static_cast<int64_t>(value));
  } else {
    SysError::setError("MainLoopExitFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe
