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

class CopyVectorResizedBvr : virtual public Behavior<Vector3D, Vector3D, double> {
public:
  void apply(std::shared_ptr<MAvatar<Vector3D, Vector3D, double>> avatar) {
    auto vsize = avatar->get<1, double>();
    auto vsrc  = avatar->get<2, Vector3D>();

    auto src = vsrc->get();
    auto size = vsize->get();


    avatar->set<3, Vector3D>(src.normalize() * size);
  }
};

template<typename T>
class BoundedAddBvr : virtual public Behavior<T, T, T, T> {
public:
  void apply(std::shared_ptr<MAvatar<T, T, T, T>> avatar) {
    auto vcurrent = AvtUtil::get<1, T>(avatar);
    auto vincrement = AvtUtil::get<2, T>(avatar);
    auto vmin = AvtUtil::get<3, T>(avatar);
    auto vmax = AvtUtil::get<4, T>(avatar);

    auto current = vcurrent->get();
    auto increment = vincrement->get();
    auto min = vmin->get();
    auto max = vmax->get();

    //printf("current %ld increment %ld min %ld max %ld \n", current, increment, min, max);fflush(stdout);
    current = current + increment;
    //printf("current %ld\n", current);fflush(stdout);
    if(current>max) {
      current = max;
    }

    if(current<min) {
      current = min;
    }
    vcurrent->set(current);
  }
};

template<typename T>
class SimpleIncrementBvr : virtual public Behavior<T> {
public:
  void apply(std::shared_ptr<SAvatar<T>> avatar) {
    auto vv = avatar->get();
    auto v = vv->get(); 
    v++;
    vv->set(v);
  }
};

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
  T val {};
};

template<typename T>
class BoundedAddTriggerBvr : virtual public Behavior<T, T, T, T, T> {
public:
  void apply(std::shared_ptr<MAvatar<T, T, T, T, T>> avatar) {
    auto vcurrent = AvtUtil::get<1, T>(avatar);
    auto vincrement = AvtUtil::get<2, T>(avatar);
    auto vmin = AvtUtil::get<3, T>(avatar);
    auto vmax = AvtUtil::get<4, T>(avatar);
    auto vtrigger = AvtUtil::get<5, T>(avatar);

    auto current = vcurrent->get();
    auto increment = vincrement->get();
    auto min = vmin->get();
    auto max = vmax->get();
    auto trigger = vtrigger->get();
    auto newval = current;

    //printf("current %ld increment %ld min %ld max %ld \n", current, increment, min, max);fflush(stdout);
    newval = newval + increment;
    //printf("current %ld\n", current);fflush(stdout);
    if(newval>max) {
      newval = max;
    }

    if(newval<min) {
      newval = min;
    }

    vcurrent->set(newval);

    if(newval != current && newval == trigger) {
      dmn->run();
    }
  }

  void setDaemon(std::shared_ptr<Daemon> dmn) {
    this->dmn = dmn;
  }

private:
  std::shared_ptr<Daemon> dmn;
};



template<typename T>
class BoundedAddTriggerBvrFtry : public Factory {
public:
  void create(std::string name, uint64_t) {
    using namespace std::string_literals;
    std::shared_ptr<BoundedAddTriggerBvr<T>> batb = std::shared_ptr<BoundedAddTriggerBvr<T>>(new BoundedAddTriggerBvr<T>);
    behaviorRsrc.insert("Behavior."s + name, batb);
    specificRsrc.insert("BoundedAddTriggerBvr."s + name, batb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto batb = specificRsrc.get("BoundedAddTriggerBvr."s + name);

      auto daemon = JSONFactory::loadParamCfgStoreP<Daemon>(daemonRsrc, j, "Daemon"s, "daemon"s, "BoundedAddTriggerBvrFtry"s);
      if(!daemon) {
        SysError::setError("BoundedAddTriggerBvrFtry config for daemon must be a valid Daemon name."s);
        return;
      }

      batb->setDaemon(*daemon);
    } else {
        SysError::setError("BoundedAddTriggerBvrFtry config for "s + name + " not found."s);
    }
  }

private:

  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<Behavior<T,T,T,T,T>>& behaviorRsrc = RsrcStore<Behavior<T,T,T,T,T>>::getInstance();
  RsrcStore<BoundedAddTriggerBvr<T>>& specificRsrc = RsrcStore<BoundedAddTriggerBvr<T>>::getInstance();
};

template<typename T>
class ValueSetterFixedBvrFtry : public Factory {
public:
  void create(std::string name, uint64_t) {
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
  void create(std::string name, uint64_t) {
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
  void create(std::string name, uint64_t) {
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
