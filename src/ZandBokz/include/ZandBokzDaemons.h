/**
 * Copyright 2022 Batis Degryll Ludo
 * @file ZandBokzDaemons.h
 * @since 2022-12-06
 * @date 2022-12-06
 * @author Ludo Degryll Batis
 * @brief ZandBokz Daemons
 */

 #ifndef ZANDBOKZ_ZANDBOKZDAEMONS_H_
 #define ZANDBOKZ_ZANDBOKZDAEMONS_H_

#include <cstdio>

#include <cstdint>
#include <memory>

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/tools.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

#include "ZBE/JSON/JSONFactory.h"

namespace zandbokz {

template<typename T>
class FixedValueSetterDmn : virtual public zbe::Daemon {
  public:
    FixedValueSetterDmn() : list(), fixed() {};
    virtual ~FixedValueSetterDmn() = default;

    void addValue(std::shared_ptr<zbe::Value<T>> val) {
      list.push_front(val);
    }

    void setFixedValue(T fixed) {
      this->fixed = fixed;
    }

    void run() {
      // for(auto it = list.begin(); it != list.end(); ++it) {
      //   (*it)->run();
      // }
      for (auto v : list) {
       v->set(fixed);
      }
    }

  private:
    std::forward_list< std::shared_ptr<zbe::Value<T>>> list;
    T fixed;
};

template<typename T>
class FixedValueSetterDmnFtry : virtual public zbe::Factory {
public:

  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    std::shared_ptr<FixedValueSetterDmn<T>> fvsd = std::make_shared<FixedValueSetterDmn<T>>();
    daemonRsrc.insert("Daemon."s + name, fvsd);
    fvsdRsrc.insert("FixedValueSetterDmn."s + name, fvsd);
  }

  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;
        
      auto fvsd = fvsdRsrc.get("FixedValueSetterDmn."s + name);
      zbe::JSONFactory::loadAll<zbe::Value<T>>(valueRsrc, j, "values"s, "FixedValueSetterDmnFtry"s,
        [&](std::shared_ptr<zbe::Value<T>> val) {
          fvsd->addValue(val);
          return true;
        }
      );

      auto fixed = zbe::JSONFactory::loadParamCfgDict<T>(tDic, j, "fixedvalue"s, "FixedValueSetterDmnFtry"s);
      if(!fixed) {
        return;
      }
        
      fvsd->setFixedValue(*fixed);
    } else {
      zbe::SysError::setError("FixedValueSetterDmnFtry config for "s + name + " not found."s);
    }
  }

private:

  zbe::RsrcStore<nlohmann::json>& configRsrc = zbe::RsrcStore<nlohmann::json>::getInstance();
  zbe::RsrcDictionary<T>& tDic = zbe::RsrcDictionary<T>::getInstance();
  zbe::RsrcStore<zbe::Value<T> > &valueRsrc = zbe::RsrcStore<zbe::Value<T> >::getInstance();
  zbe::RsrcStore<zbe::Daemon>& daemonRsrc = zbe::RsrcStore<zbe::Daemon>::getInstance();
  zbe::RsrcStore<FixedValueSetterDmn<T>>& fvsdRsrc = zbe::RsrcStore<FixedValueSetterDmn<T>>::getInstance();
};

} // namespace zandbokz

#endif  // ZANDBOKZ_ZANDBOKZDAEMONS_H_
