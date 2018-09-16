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

void StateMachineDmnFtry::build(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    json state = j["state"];
    std::string stateName;
    if(state.type() == json::value_t::string){
       stateName = state.get<std::string>();
    } else {
      SysError::setError("StateMachineDmnFtry state for "s + name + " is invalid or not present."s);
      return;
    }
    json daemons = j["daemons"];
    uint64_t stateId = dict.get("Valueu."s + stateName);
    std::shared_ptr<Value<int64_t> > stateVal = valueRsrc.get(stateId);
    std::shared_ptr<StateMachineDaemon> smd = std::make_shared<StateMachineDaemon>(stateVal);
    for (auto dmn : daemons) {
      if (dmn[1].type() == json::value_t::number_integer) {
        std::string dname = dmn[0].get<std::string>();
        int stateno = dmn[1].get<int>();
        uint64_t dId = dict.get("Daemon."s + dname);
        smd->setDaemon(stateno, daemonRsrc.get(dId));
      } else {
        SysError::setError("StateMachineDmnFtry config for "s + dmn[0].get<std::string>() + ": state is not an integer."s);
      }
    }

    uint64_t id = SysIdGenerator::getId();
    daemonRsrc.insert(id, smd);
    dict.insert("Daemon."s + name, id);
  } else {
    SysError::setError("StateMachineDmnFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe
