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
  daemonRsrc.insert("Daemon."s + name, smd);
  stateMachinedaemonRsrc.insert("StateMachineDaemon."s + name, smd);
}

void StateMachineDmnFtry::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    // json state = j["value"];
    // std::string stateName;
    // if(state.is_string()){
    //    stateName = state.get<std::string>();
    // } else {
    //   SysError::setError("StateMachineDmnFtry state for "s + name + " is invalid or not present."s);
    //   return;
    // }
    // json daemons = j["states"];
    // uint64_t stateId = dict.get(stateName);
    // std::shared_ptr<Value<int64_t> > stateVal = valueRsrc.get(stateId);
    // auto smd = stateMachinedaemonRsrc.get("StateMachineDaemon."s + name);
    // smd->setStateValue(stateVal);
    // for (auto dmn : daemons) {
    //   if (dmn[0].is_string() && dmn[1].is_string()) {
    //     std::string dname = dmn[0].get<std::string>();
    //     std::string sname = dmn[1].get<std::string>();
    //     uint64_t stateno = dict.get("State."s + sname);
    //     uint64_t dId = dict.get("Daemon."s + dname);
    //     smd->setDaemon(stateno, daemonRsrc.get(dId));
    //   } else {
    //     SysError::setError("StateMachineDmnFtry config for "s + dmn[0].get<std::string>() + ": state is not an integer."s);
    //   }
    // }

    auto smd = stateMachinedaemonRsrc.get("StateMachineDaemon."s + name);
    auto statesCfg = j["states"];
    for (auto& stateCfg : statesCfg.items()) {

      if (!stateCfg.value().is_string()) {
        SysError::setError("StateMachineDmnFtry " + name + " config for states must contain strings. But is "s + stateCfg.value().type_name());
        return;
      }
      uint64_t state = uDict.get(stateCfg.key());

      if(auto dmn = JSONFactory::loadParamStrStore<Daemon>(daemonRsrc, zbe::factories::daemonName_ + stateCfg.value().get<std::string>() , "StateMachineDaemonFtry"s)) {
        smd->setDaemon(state, *dmn);
      } else {
        SysError::setError("StateMachineDaemonFtry value for "s +  stateCfg.key() + " is not a daemon name");
        return;
      }
    }

  } else {
    SysError::setError("StateMachineDmnFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe
