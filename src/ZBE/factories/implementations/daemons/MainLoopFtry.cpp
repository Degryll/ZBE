/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MainLoopFtry.cpp
 * @since 2018-09-19
 * @date 2018-09-19
 * @author Ludo Degryll Batis
 * @brief Factory for Main Loop.
 */

#include "ZBE/factories/implementations/daemons/MainLoopFtry.h"

namespace zbe {

void MainLoopFtry::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  auto ml = std::make_shared<MainLoop>();
  uint64_t id = SysIdGenerator::getId();
  daemonRsrc.insert(id, ml);
  dict.insert("Daemon."s + name, id);
  id = SysIdGenerator::getId();
  mainLoopRsrc.insert(id, ml);
  dict.insert("MainLoop."s + name, id);
}

void MainLoopFtry::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    json pre = j["preDaemon"];
    json event = j["eventDaemon"];
    json common = j["commonDaemon"];
    json react = j["reactDaemon"];
    json draw = j["drawDaemon"];
    json post = j["postDaemon"];
    json cTime = j["contextTime"];

    std::shared_ptr<Daemon> preDm, postDm, eventDm, commonDm, reactDm, drawDm;
    std::shared_ptr<ContextTime> ctxTime;

    if ((pre.is_string())
    &&  (event.is_string())
    &&  (common.is_string())
    &&  (react.is_string())
    &&  (draw.is_string())
    &&  (post.is_string())
    &&  (cTime.is_string())) {

      preDm    = daemonRsrc.get("Daemon."s + pre.get<std::string>());
      eventDm  = daemonRsrc.get("Daemon."s + event.get<std::string>());
      commonDm = daemonRsrc.get("Daemon."s + common.get<std::string>());
      reactDm  = daemonRsrc.get("Daemon."s + react.get<std::string>());
      drawDm   = daemonRsrc.get("Daemon."s + draw.get<std::string>());
      postDm   = daemonRsrc.get("Daemon."s + post.get<std::string>());
      ctxTime  = timeRsrc.get("Time."s + cTime.get<std::string>());

      auto ml = mainLoopRsrc.get("MainLoop."s + name);

      ml->setPre(preDm);
      ml->setPost(postDm);
      ml->setEvent(eventDm);
      ml->setCommon(commonDm);
      ml->setReact(reactDm);
      ml->setDraw(drawDm);
      ml->setContextTime(ctxTime);

    } else {
      SysError::setError("Bad config for MainLoopFtry."s);
    }   // if pre, event, common, react, draw, post
  } else {
    SysError::setError("MainLoopFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe
