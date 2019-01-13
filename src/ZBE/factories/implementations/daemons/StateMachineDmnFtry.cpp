/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StateMachineDmnFtry.cpp
 * @since 2018-09-05
 * @date 2018-09-05
 * @author Ludo Degryll Batis
 * @brief
 */

#include "ZBE/factories/implementations/daemons/StateMachineDmnFtry.h"

namespace zbe {

void StateMachineDmnFtry::create(std::string name, uint64_t) {
  using namespace std::string_literals;
  std::shared_ptr<StateMachineDaemon> smd = std::make_shared<StateMachineDaemon>();

  uint64_t id = SysIdGenerator::getId();
  daemonRsrc.insert(id, smd);
  dict.insert("Daemon."s + name, id);
  id = SysIdGenerator::getId();
  stateMachinedaemonRsrc.insert(id, smd);
  dict.insert("StateMachineDaemon."s + name, id);
}

void StateMachineDmnFtry::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    json state = j["state"];
    std::string stateName;
    if(state.is_string()){
       stateName = state.get<std::string>();
    } else {
      SysError::setError("StateMachineDmnFtry state for "s + name + " is invalid or not present."s);
      return;
    }
    json daemons = j["daemons"];
    uint64_t stateId = dict.get("Valuei."s + stateName);
    std::shared_ptr<Value<int64_t> > stateVal = valueRsrc.get(stateId);
    auto smd = stateMachinedaemonRsrc.get("StateMachineDaemon."s + name);
    smd->setStateValue(stateVal);
    for (auto dmn : daemons) {
      if (dmn[0].is_string() && dmn[1].is_string()) {
        std::string dname = dmn[0].get<std::string>();
        std::string sname = dmn[1].get<std::string>();
        uint64_t stateno = dict.get("State."s + sname);
        uint64_t dId = dict.get("Daemon."s + dname);
        smd->setDaemon(stateno, daemonRsrc.get(dId));
      } else {
        SysError::setError("StateMachineDmnFtry config for "s + dmn[0].get<std::string>() + ": state is not an integer."s);
      }
    }

  } else {
    SysError::setError("StateMachineDmnFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe
