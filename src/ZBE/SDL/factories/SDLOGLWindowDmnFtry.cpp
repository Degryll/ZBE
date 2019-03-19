/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SDLOGLWindowDmnFtry.cpp
 * @since 2018-09-19
 * @date 2018-09-19
 * @author Ludo Degryll Batis
 * @brief Factory for Main Loop.
 */

#include "ZBE/SDL/factories/SDLOGLWindowDmnFtry.h"

namespace zbe {

void SDLOGLWindowDmnFtry::create(std::string name, uint64_t) {
//  using namespace std::string_literals;
//
//  auto ml = std::make_shared<MainLoopExit>();
//  uint64_t id = SysIdGenerator::getId();
//  daemonRsrc.insert(id, ml);
//  dict.insert("Daemon."s + name, id);
//  id = SysIdGenerator::getId();
//  mainLoopExitRsrc.insert(id, ml);
//  dict.insert("MainLoopExit."s + name, id);
}

void SDLOGLWindowDmnFtry::setup(std::string name, uint64_t cfgId) {
//  using namespace std::string_literals;
//  using namespace nlohmann;
//  std::shared_ptr<json> cfg = configRsrc.get(cfgId);
//
//  if(cfg) {
//    auto j = *cfg;
//    json mainloopName = j["mainloop"];
//    json valueHolderName = j["valueHolder"];
//    json outValue = j["outValue"];
//    if(!mainloopName.is_string()) {
//      SysError::setError("Bad config for SDLOGLWindowDmnFtry - mainloop."s + name);
//      return;
//    }
//    if(!valueHolderName.is_string()) {
//      SysError::setError("Bad config for SDLOGLWindowDmnFtry - valueHolder."s + name);
//      return;
//    }
//    if(!outValue.is_number()) {
//      SysError::setError("Bad config for SDLOGLWindowDmnFtry - outValue."s + name);
//      return;
//    }
//    auto mle = mainLoopExitRsrc.get("MainLoopExit."s + name);
//    auto ml = mainLoopRsrc.get("MainLoop."s + mainloopName.get<std::string>());
//    auto valueHolder = valueRsrc.get("ValueI."s + valueHolderName.get<std::string>());
//    uint64_t value = outValue.get<uint64_t>();
//    mle->setMainLoop(ml);
//    mle->setValue(valueHolder);
//    mle->setExitValue(value);
//  } else {
//    SysError::setError("SDLOGLWindowDmnFtry config for "s + name + " not found."s);
//  }
}

}  // namespace zbe
