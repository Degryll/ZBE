/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseAvatarFtry.h
 * @since 2020-04-14
 * @date 2020-04-14
 * @author Ludo Degryll Batis
 * @brief Generic Factory.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_ENTITIES_AVATARS_BASEAVATARFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_ENTITIES_AVATARS_BASEAVATARFTRY_H_

#include <string>
#include <nlohmann/json.hpp>

#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/system/system.h"

#include "ZBE/factories/Factory.h"



namespace zbe {

/** \brief Generic BaseAvatarFtry Factory.
 */
template<typename T, typename... Ts>
class BaseAvatarFtry : virtual public Factory {
public:

  /** \brief Creates a BaseAvatar from a file.
   *  \param name Name for the created BaseAvatar.
   *  \param cfgId item's configuration id.
   */
  void create(std::string name, uint64_t);

  /** \brief Set-up a BaseAvatar.
   *  \param name Name for the created item.
   *  \param cfgId item's configuration id.
   */
  void setup(std::string, uint64_t);

private:
  static const int expectedIndexes = sizeof...(Ts) + 1;
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<Entity>& entStore = RsrcStore<Entity>::getInstance();
  RsrcStore<MBaseAvatar<T, Ts...> >& baseAvatarStore = RsrcStore<MBaseAvatar<T, Ts...> >::getInstance();
  RsrcStore<TicketedForwardList<MAvatar<T, Ts...> > >& listStore = RsrcStore<TicketedForwardList<MAvatar<T, Ts...> > >::getInstance();
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
};

/** \brief Generic BaseAvatarFtry Factory.
 */
template<typename T>
class BaseAvatarFtry<T> : virtual public Factory {
public:

  /** \brief Creates a BaseAvatar from a file.
   *  \param name Name for the created BaseAvatar.
   *  \param cfgId item's configuration id.
   */
  void create(std::string name, uint64_t);

  /** \brief Set-up a BaseAvatar.
   *  \param name Name for the created item.
   *  \param cfgId item's configuration id.
   */
  void setup(std::string, uint64_t);

private:
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<Entity>& entStore = RsrcStore<Entity>::getInstance();
  RsrcStore<SBaseAvatar<T> >& baseAvatarStore = RsrcStore<SBaseAvatar<T> >::getInstance();
  RsrcStore<TicketedForwardList<SAvatar<T> > >& listStore = RsrcStore<TicketedForwardList<SAvatar<T> > >::getInstance();
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
};


template<typename T, typename... Ts>
void BaseAvatarFtry<T, Ts...>::create(std::string name, uint64_t) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<MBaseAvatar<T, Ts...> > avt = std::make_shared<MBaseAvatar<T, Ts...> >();
  baseAvatarStore.insert("BaseAvatar."s + name, avt);
}

template<typename T>
void BaseAvatarFtry<T>::create(std::string name, uint64_t) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<SBaseAvatar<T> > avt = std::make_shared<SBaseAvatar<T> >();
  baseAvatarStore.insert("BaseAvatar."s + name, avt);
}


template<typename T, typename... Ts>
void BaseAvatarFtry<T, Ts...>::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  auto cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    if (!j["entity"].is_string()) {
      SysError::setError("Avatar " + name + " config for entity must be a string."s);
      return;
    }
    if (!j["lists"].is_object()) {
      SysError::setError("Avatar " + name + " config for lists must be an object. But is "s + j["lists"].type_name());
      return;
    }
    if (!j["attribIndexes"].is_array()) {
      SysError::setError("Avatar " + name + " config for attribIndexes must be an array."s);
      return;
    }

    std::string entityName = j["entity"].get<std::string>();
    auto ent = entStore.get("Entity." + entityName);

    auto idxCfg = j["attribIndexes"];

    if(idxCfg.size() != expectedIndexes) {
      SysError::setError("Avatar " + name + " config for attribIndexes must have "s + std::to_string(expectedIndexes) + " elements");
      return;
    }

    std::array<uint64_t, expectedIndexes> idxArr;
    int i = 0;
    for (auto& idxName : idxCfg.items()) {
      idxArr[i] = dict.get(idxName.value().get<std::string>());
      i++;
    }

    auto avt = baseAvatarStore.get("BaseAvatar."s + name);

    avt->setupEntity(ent, idxArr);

    auto listsCfg = j["lists"];
    for (auto& listCfg : listsCfg.items()) {

      if (!listCfg.value().is_string()) {
        SysError::setError("Avatar " + name + " config for lists must contain strings. But is "s + listCfg.value().type_name());
        return;
      }
      auto list = listStore.get("List." + listCfg.key());
      auto ticket = list->push_front(avt);
      ent->addTicket(dict.get(listCfg.value().get<std::string>()), ticket);
    }
    baseAvatarStore.remove("BaseAvatar."s + name);
  } else {
    SysError::setError("Avatar config for "s + name + " not found."s);
  }
}

template<typename T>
void BaseAvatarFtry<T>::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  auto cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    if (!j["entity"].is_string()) {
      SysError::setError("Avatar " + name + " config for entity must be a string."s);
      return;
    }
    if (!j["lists"].is_object()) {
      SysError::setError("Avatar " + name + " config for lists must be an object. But is "s + j["lists"].type_name());
      return;
    }
    if (!j["attribIndexes"].is_array()) {
      SysError::setError("Avatar " + name + " config for attribIndexes must be an array."s);
      return;
    }

    std::string entityName = j["entity"].get<std::string>();
    auto ent = entStore.get("Entity."+entityName);

    auto idxCfg = j["attribIndexes"];

    if(idxCfg.size() != 1) {
      SysError::setError("Avatar " + name + " config for attribIndexes must have a single element");
      return;
    }

//    std::array<uint64_t, 1> idxArr;
//    idxArr[0] = dict.get(idxCfg[0].get<std::string>());

    auto avt = baseAvatarStore.get("BaseAvatar."s + name);

    avt->setupEntity(ent, dict.get(idxCfg[0].get<std::string>()));

    auto listsCfg = j["lists"];
    for (auto& listCfg : listsCfg.items()) {

      if (!listCfg.value().is_string()) {
        SysError::setError("Avatar " + name + " config for lists must contain strings. But is "s + listCfg.value().type_name());
        return;
      }
      auto list = listStore.get("List." + listCfg.key());
      auto ticket = list->push_front(avt);
      ent->addTicket(dict.get(listCfg.value().get<std::string>()), ticket);
    }
    baseAvatarStore.remove("BaseAvatar."s + name);
  } else {
    SysError::setError("Avatar config for "s + name + " not found."s);
  }
}

} // namespace ZBE

#endif // ZBE_FACTORIES_IMPLEMENTATIONS_ENTITIES_AVATARS_BASEAVATARFTRY_H_
