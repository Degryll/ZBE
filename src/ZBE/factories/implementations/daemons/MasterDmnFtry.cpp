/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MasterDmnFtry.cpp
 * @since 2018-09-19
 * @date 2018-09-19
 * @author Ludo Degryll Batis
 * @brief Factory for behavior daemons.
 */

#include "ZBE/factories/implementations/daemons/MasterDmnFtry.h"

namespace zbe {

void MasterDmnFtry::build(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    json daemons = j["daemons"];
    std::shared_ptr<DaemonMaster> dm = std::make_shared<DaemonMaster>();
    for (auto daemon : daemons) {
      if (daemon.type() == json::value_t::string) {
        uint64_t dId = dict.get("Daemon."s + daemon.get<std::string>());
        dm->addDaemon(daemonRsrc.get(dId));
      } else {
        SysError::setError("MasterDmnFtry config for "s + name + " not found."s);
      }
    }
    uint64_t id = SysIdGenerator::getId();
    daemonRsrc.insert(id, dm);
    dict.insert("Daemon."s + name, id);
  } else {
    SysError::setError("MasterDmnFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe
