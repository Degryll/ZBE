/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleMainLoopFtry.h .h
 * @since 2018-09-24
 * @date 2018-09-24
 * @author Ludo Degryll Batis
 * @brief Factory for Main Loop Daemons.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_DAEMONS_SIMPLEMAINLOOPFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_DAEMONS_SIMPLEMAINLOOPFTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"
#include "ZBE/core/system/SysTime.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

#include "ZBE/core/events/EventStore.h"

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for Main Loop.
 */
class SimpleMainLoopFtry : virtual public Factory {
public:

  /** \brief Builds a SimpleMainLoop.
   *  \param name Name for the created SimpleMainLoopFtry.
   *  \param cfgId SimpleMainLoopFtry's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;

    auto ml = std::make_shared<SimpleMainLoop>();
    daemonRsrc.insert("Daemon."s + name, ml);
    mainLoopRsrc.insert("SimpleMainLoop."s + name, ml);
  }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override {
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
        ctxTime  = timeRsrc.get("ContextTime."s + cTime.get<std::string>());

        auto ml = mainLoopRsrc.get("SimpleMainLoop."s + name);

        ml->setPre(preDm);
        ml->setPost(postDm);
        ml->setEvent(eventDm);
        ml->setCommon(commonDm);
        ml->setReact(reactDm);
        ml->setDraw(drawDm);
        ml->setContextTime(ctxTime);
        ml->setEventStore(&eventStore);

      } else {
        SysError::setError("Bad config for SimpleMainLoopFtry."s);
      }   // if pre, event, common, react, draw, post
    } else {
      SysError::setError("SimpleMainLoopFtry config for "s + name + " not found."s);
    }
  }

private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon> &daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<SimpleMainLoop> &mainLoopRsrc = RsrcStore<SimpleMainLoop>::getInstance();
  RsrcStore<ContextTime> &timeRsrc = RsrcStore<ContextTime>::getInstance();
  EventStore &eventStore = EventStore::getInstance();
};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_DAEMONS_SIMPLEMAINLOOPFTRY_H_
