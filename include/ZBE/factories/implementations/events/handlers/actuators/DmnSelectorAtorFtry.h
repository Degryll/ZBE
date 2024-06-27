/**
 * Copyright 2012 Batis Degryll Ludo
 * @file DmnSelectorAtorFtry.h
 * @since 2018-09-19
 * @date 2018-09-19
 * @author Ludo Degryll Batis
 * @brief Factory for DaemonSelectorAlienAtor.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_ACTUATORS_DMNSELECTORATORFCTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_ACTUATORS_DMNSELECTORATORFCTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/events/handlers/Actuator.h"

#include "ZBE/events/handlers/actuators/DaemonSelectorAtor.h"

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Factory for DaemonSelectorAlienAtor.
 */
template<typename T, typename R>
class DaemonSelectorAlienAtorFtry : virtual public Factory {
public:

/** \brief Create the desired tool, probably incomplete.
 *  \param name Name for the created tool.
 *  \param cfgId Tool's configuration id.
 */
  void create(std::string name, uint64_t) override;

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId);

private:
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon> &daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<Actuator<WeakAvatarEntityContainer<T>,R> > &atorRsrc = RsrcStore<Actuator<WeakAvatarEntityContainer<T>,R> >::getInstance();
  RsrcStore<DaemonSelectorAlienAtor<T,R> > &dsalAtorRsrc = RsrcStore<DaemonSelectorAlienAtor<T,R> >::getInstance();
};

template<typename T, typename R>
void DaemonSelectorAlienAtorFtry<T, R>::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  auto ator = std::make_shared<DaemonSelectorAlienAtor<T, R> >();
  uint64_t id = SysIdGenerator::getId();
  atorRsrc.insert(id, ator);
  dict.insert("Actuator."s + name, id);
  id = SysIdGenerator::getId();
  dsalAtorRsrc.insert(id, ator);
  dict.insert("DaemonSelectorAlienAtor."s + name, id);
}

template<typename T, typename R>
void DaemonSelectorAlienAtorFtry<T, R>::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    json daemons = j["daemons"];
    auto dsaa = dsalAtorRsrc.get("DaemonSelectorAlienAtor."s + name);
    for (auto dmn : daemons) {
      if (dmn[0].is_string() && dmn[1].is_string()) {
        std::string dname = dmn[0].get<std::string>();
        std::string sname = dmn[1].get<std::string>();
        uint64_t stateno = dict.get("State."s + sname);
        uint64_t dId = dict.get("Daemon."s + dname);
        dsaa->setDaemon(stateno, daemonRsrc.get(dId));
      } else {
        SysError::setError("DaemonSelectorAlienAtorFtry config for "s + dmn[0].get<std::string>() + ": must be a string."s);
      }
    }

    json defDaemon = j["defdmn"];
    if(defDaemon.is_string()){
      std::string dname = defDaemon.get<std::string>();
      uint64_t dId = dict.get("Daemon."s + dname);
      dsaa->setDefault(daemonRsrc.get(dId));
    } else {
      SysError::setError("DaemonSelectorAlienAtorFtry config for default daemon must be a string."s);
    }

  } else {
    SysError::setError("DaemonSelectorAlienAtorFtry config for "s + name + " not found."s);
  }
}

/** \brief Factory for DaemonSelectorSelfAtor.
 */
template<typename T, typename R>
class DaemonSelectorSelfAtorFtry : virtual public Factory {
public:

/** \brief Create the desired tool, probably incomplete.
 *  \param name Name for the created tool.
 *  \param cfgId Tool's configuration id.
 */
  void create(std::string name, uint64_t) override;

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId);

private:
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon> &daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<Actuator<WeakAvatarEntityContainer<Stated>,R> > &atorRsrc = RsrcStore<Actuator<WeakAvatarEntityContainer<Stated>,R> >::getInstance();
  RsrcStore<DaemonSelectorSelfAtor<T,R> > &dsalAtorRsrc = RsrcStore<DaemonSelectorSelfAtor<T,R> >::getInstance();
};

template<typename T, typename R>
void DaemonSelectorSelfAtorFtry<T, R>::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  auto ator = std::make_shared<DaemonSelectorSelfAtor<T, R> >();
  uint64_t id = SysIdGenerator::getId();
  atorRsrc.insert(id, ator);
  dict.insert("Actuator."s + name, id);
  id = SysIdGenerator::getId();
  dsalAtorRsrc.insert(id, ator);
  dict.insert("DaemonSelectorSelfAtor."s + name, id);
}

template<typename T, typename R>
void DaemonSelectorSelfAtorFtry<T, R>::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    json daemons = j["daemons"];
    auto dsaa = dsalAtorRsrc.get("DaemonSelectorSelfAtor."s + name);
    for (auto dmn : daemons) {
      if (dmn[0].is_string() && dmn[1].is_string()) {
        std::string dname = dmn[0].get<std::string>();
        std::string sname = dmn[1].get<std::string>();
        uint64_t stateno = dict.get("State."s + sname);
        uint64_t dId = dict.get("Daemon."s + dname);
        dsaa->setDaemon(stateno, daemonRsrc.get(dId));
      } else {
        SysError::setError("DaemonSelectorSelfAtorFtry config for "s + dmn[0].get<std::string>() + ": must be a string."s);
      }
    }

    json defDaemon = j["defdmn"];
    if(defDaemon.is_string()){
      std::string dname = defDaemon.get<std::string>();
      uint64_t dId = dict.get("Daemon."s + dname);
      dsaa->setDefault(daemonRsrc.get(dId));
    } else {
      SysError::setError("DaemonSelectorSelfAtorFtry config for default daemon must be a string."s);
    }

  } else {
    SysError::setError("DaemonSelectorAlienAtorFtry config for "s + name + " not found."s);
  }
}

/** \brief Factory for DaemonSelectorSelfAnyAtor.
 */
template<typename R>
class DaemonSelectorSelfAnyAtorFtry : virtual public Factory {
public:

/** \brief Create the desired tool, probably incomplete.
 *  \param name Name for the created tool.
 *  \param cfgId Tool's configuration id.
 */
  void create(std::string name, uint64_t) override;

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId);

private:
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Daemon> &daemonRsrc = RsrcStore<Daemon>::getInstance();
  RsrcStore<Actuator<zbe::Stated, R> > &atorRsrc = RsrcStore<Actuator<zbe::Stated, R> >::getInstance();
  RsrcStore<DaemonSelectorSelfAnyAtor<R> > &dsalAtorRsrc = RsrcStore<DaemonSelectorSelfAnyAtor<R> >::getInstance();
};

template<typename R>
void DaemonSelectorSelfAnyAtorFtry<R>::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  auto ator = std::make_shared<DaemonSelectorSelfAnyAtor<R> >();
  uint64_t id = SysIdGenerator::getId();
  atorRsrc.insert(id, ator);
  dict.insert("Actuator."s + name, id);
  id = SysIdGenerator::getId();
  dsalAtorRsrc.insert(id, ator);
  dict.insert("DaemonSelectorSelfAnyAtor."s + name, id);
}

template<typename R>
void DaemonSelectorSelfAnyAtorFtry<R>::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    json daemons = j["daemons"];
    auto dsaa = dsalAtorRsrc.get("DaemonSelectorSelfAnyAtor."s + name);
    for (auto dmn : daemons) {
      if (dmn[0].is_string() && dmn[1].is_string()) {
        std::string dname = dmn[0].get<std::string>();
        std::string sname = dmn[1].get<std::string>();
        uint64_t stateno = dict.get("State."s + sname);
        uint64_t dId = dict.get("Daemon."s + dname);
        dsaa->setDaemon(stateno, daemonRsrc.get(dId));
      } else {
        SysError::setError("DaemonSelectorSelfAnyAtorFtry config for "s + dmn[0].get<std::string>() + ": must be a string."s);
      }
    }

    json defDaemon = j["defdmn"];
    if(defDaemon.is_string()){
      std::string dname = defDaemon.get<std::string>();
      uint64_t dId = dict.get("Daemon."s + dname);
      dsaa->setDefault(daemonRsrc.get(dId));
    } else {
      SysError::setError("DaemonSelectorSelfAtorFtry config for default daemon must be a string."s);
    }

  } else {
    SysError::setError("DaemonSelectorAlienAtorFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_EVENTS_HANDLERS_ACTUATORS_DMNSELECTORATORFCTRY_H_
