#include "ZBE/factories/implementations/events/generators/TimeEventGnFtry.h"

namespace zbe{

  void TimeEventGnFtry::create(std::string name, uint64_t) {
    using namespace std::string_literals;

    auto teg = std::make_shared<TimeEventGenerator>();
    dmnRsrc.insert("Daemon."s + name, teg);
    tegRsrc.insert("TimeEventGenerator."s + name, teg);
  }

  void TimeEventGnFtry::setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;
  //TimeEventGenerator(int eventId, std::shared_ptr<ContextTime> contextTime = SysTime::getInstance())

      if (!(j["eventId"].type() ==json::value_t::string)){
        SysError::setError("TimeEventDaemonFtry config for "s + name + " must contain a valid string for eventId."s);
        return;
      }
      if (!(j["contextTime"].type() ==json::value_t::string)){
        SysError::setError("TimeEventDaemonFtry config for "s + name + " must contain a valid string for contexttTime."s);
        return;
      }
      std::string ename = j["eventId"].get<std::string>();
      std::string ctname = j["contextTime"].get<std::string>();

      int eId = intStore.get(ename);
      auto cTime = cxTimeStore.get("ContextTime."s + ctname);

      auto teg = tegRsrc.get("TimeEventGenerator."s + name);
      teg->setEventId(eId);
      teg->setContextTime(cTime);

    } else {
      SysError::setError("TimeEventDaemonFtry config for "s + name + " not found."s);
    }
  }

}
