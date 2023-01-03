/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Erase.h
 * @since 2017-11-05
 * @date 2018-02-25
 * @author Degryll Ludo Batis
 * @brief Erase given avatar.
 */

#ifndef ZBE_BEHAVIORS_BEHAVIORS_H_
#define ZBE_BEHAVIORS_BEHAVIORS_H_

#include <array>
#include <memory>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/avatars/Avatar.h"

#include "ZBE/core/system/system.h"
#include "ZBE/factories/Factory.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/factories/genericFactoryConstants.h"
#include "ZBE/JSON/JSONFactory.h"

namespace zbe {

template<typename T>
class ValueSetterFixedBvr : virtual public Behavior<T> {
public:
  void apply(std::shared_ptr<SAvatar<T>> avatar) {
    auto vv = avatar->get();
    vv->set(val);
  }

  void setValue(T val) {
    this->val = val;
  }

private:
  T val;
};

template<typename T>
class ValueSetterFixedBvrFtry : public Factory {
public:
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<ValueSetterFixedBvr<T>> vsfb = std::shared_ptr<ValueSetterFixedBvr<T>>(new ValueSetterFixedBvr<T>);
    behaviorRsrc.insert("Behavior."s + name, vsfb);
    vsfbRsrc.insert("ValueSetterFixedBvr."s + name, vsfb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto tdb = vsfbRsrc.get("ValueSetterFixedBvr."s + name);

      auto value = JSONFactory::loadParamCfgDict<T>(tDict, j, "value"s, "ValueSetterFixedBvrFtry"s);
      if(!value) {
        return;
      }

      tdb->setValue(*value);
    } else {
        SysError::setError("ValueSetterFixedBvrFtry config for "s + name + " not found."s);
    }
  }

private:

  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcDictionary<T>& tDict = RsrcDictionary<T>::getInstance();
  RsrcStore<Behavior<T> >& behaviorRsrc = RsrcStore<Behavior<T> >::getInstance();
  RsrcStore<ValueSetterFixedBvr<T>>& vsfbRsrc = RsrcStore<ValueSetterFixedBvr<T>>::getInstance();
};

class TicketActivatorBvr : virtual public Behavior<void> {
public:

    virtual ~TicketActivatorBvr() {}

    void apply(std::shared_ptr<Avatar> avatar) {
        for(auto& t : list ) {
            avatar->setACTIVE(t);
        }
    }

    void setTicketList(std::forward_list<uint64_t> list) {
        this->list = list;
    }

private:
    std::forward_list<uint64_t> list;
};

class TicketDeactivatorBvr : virtual public Behavior<void> {
public:

    virtual ~TicketDeactivatorBvr() {}

    void apply(std::shared_ptr<Avatar> avatar) {
        for(auto& t : list ) {
            avatar->setINACTIVE(t);
        }
    }

    void setTicketList(std::forward_list<uint64_t> list) {
        this->list = list;
    }

private:
    std::forward_list<uint64_t> list;
};

// TODO: buscar la forma de hacer un toggler.

class TicketActivatorBvrFtry : public Factory {
public:
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<TicketActivatorBvr> teb = std::shared_ptr<TicketActivatorBvr>(new TicketActivatorBvr);
    behaviorRsrc.insert("Behavior."s + name, teb);
    tebRsrc.insert("TicketActivatorBvr."s + name, teb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
        auto j = *cfg;

        auto teb = tebRsrc.get("TicketActivatorBvr."s + name);

        std::optional<std::forward_list<uint64_t>> list = JSONFactory::loadLiteralList<uint64_t>(uintDict, j["tickets"], "tickets", "TicketActivatorBvrFtry");
        if(!list) {
            return;
        }

        teb->setTicketList(*list);
    } else {
        SysError::setError("TicketActivatorBvrFtry config for "s + name + " not found."s);
    }
  }

private:

  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();
  RsrcStore<Behavior<void> >& behaviorRsrc = RsrcStore<Behavior<void> >::getInstance();
  RsrcStore<TicketActivatorBvr>& tebRsrc = RsrcStore<TicketActivatorBvr>::getInstance();
};

class TicketDeactivatorBvrFtry : public Factory {
public:
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<TicketDeactivatorBvr> tdb = std::shared_ptr<TicketDeactivatorBvr>(new TicketDeactivatorBvr);
    behaviorRsrc.insert("Behavior."s + name, tdb);
    tdbRsrc.insert("TicketDeactivatorBvr."s + name, tdb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
        auto j = *cfg;

        auto tdb = tdbRsrc.get("TicketDeactivatorBvr."s + name);

        std::optional<std::forward_list<uint64_t>> list = JSONFactory::loadLiteralList<uint64_t>(uintDict, j["tickets"], "tickets", "TicketDeactivatorBvrFtry");
        if(!list) {
            return;
        }

        tdb->setTicketList(*list);
    } else {
        SysError::setError("TicketDeactivatorBvrFtry config for "s + name + " not found."s);
    }
  }

private:

  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();
  RsrcStore<Behavior<void> >& behaviorRsrc = RsrcStore<Behavior<void> >::getInstance();
  RsrcStore<TicketDeactivatorBvr>& tdbRsrc = RsrcStore<TicketDeactivatorBvr>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_BEHAVIORS_BEHAVIORS_H_
