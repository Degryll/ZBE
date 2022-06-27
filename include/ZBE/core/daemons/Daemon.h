/**
 * Copyright 2015 Batis Degryll Ludo
 * @file Daemon.h
 * @since 2015-05-04
 * @date 2018-02-25
 * @author Ludo Degryll Batis
 * @brief Define the minimal functions of demons.
 */

#ifndef ZBE_CORE_DAEMONS_DAEMON_H
#define ZBE_CORE_DAEMONS_DAEMON_H

#include <nlohmann/json.hpp>

#include "ZBE/core/system/system.h"
#include "ZBE/factories/Factory.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/factories/genericFactoryConstants.h"
#include "ZBE/JSON/JSONFactory.h"

namespace zbe {

/** \brief Interface for all daemons. Daemons are responsible for execute automated processes. Basically Daemons rules the world.
 */
class Daemon {
public:

  /** \brief Do the actual Daemon job.
   */
  virtual void run() = 0;

  /** \brief Destructor.
   */
  virtual ~Daemon(){};
};

template<typename F, typename L>
class FunctOverAvtListDmn : public Daemon {
public:
  void run() {
    for(auto avt : *l) {
      (*f)(avt);
    }
  }

  void setFunct(std::shared_ptr<F> f) {
    this->f = f;
  }

  void setList(std::shared_ptr<L> l) {
    this->l = l;
  }

private:
  std::shared_ptr<F> f;
  std::shared_ptr<L> l;
};

template<typename F, typename L>
class FunctOverAvtListDmnFtry : public Factory {
public:
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<FunctOverAvtListDmn<F,L>> foald = std::make_shared<FunctOverAvtListDmn<F,L>>();
    mainRsrc.insert("Daemon."s + name, foald);
    specificRsrc.insert("FunctOverAvtListDmn."s + name, foald);
  }
  void setup(std::string name, uint64_t cfgId){
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<nlohmann::json> cfg = configRsrc.get(cfgId);

    if(!cfg) {
      SysError::setError("FunctOverAvtListDmnFtry config for "s + name + " not found."s);
      return;
    }
    auto foald = specificRsrc.get("FunctOverAvtListDmn."s + name);
    auto j = *cfg;

    if(auto funct = JSONFactory::loadParamCfgStoreP<F>(functRsrc, j, zbe::factories::functionName, "function", "FunctOverAvtListDmnFtry"s)) {
      foald->setFunct(*funct);
    } else {
      SysError::setError("FunctOverAvtListDmnFtry config for function is not an adecuate function name. Either it doesn't exist or type doesn't match"s);
      return;
    }

    if(auto list = JSONFactory::loadParamCfgStoreP<L>(listRsrc, j, zbe::factories::listName, "list", "FunctOverAvtListDmnFtry"s)) {
      foald->setList(*list);
    } else {
      SysError::setError("FunctOverAvtListDmnFtry config for list is not an adecuate list name. Either it doesn't exist or type doesn't match"s);
      return;
    }
  }
private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon>& mainRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<FunctOverAvtListDmn<F,L>>& specificRsrc = RsrcStore<FunctOverAvtListDmn<F,L>>::getInstance();
  RsrcStore<L>& listRsrc = RsrcStore<L>::getInstance();
  RsrcStore<F>& functRsrc = RsrcStore<F>::getInstance();

  //RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_CORE_DAEMONS_DAEMON_H
