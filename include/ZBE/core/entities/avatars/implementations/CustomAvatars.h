/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CustomAvatars.h
 * @since 2021-01-25
 * @date 2021-01-25
 * @author Ludo Batis Degryll
 * @brief Custom implementations of avatar.
 */

#ifndef ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_CUSTOMAVATARS_H_
#define ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_CUSTOMAVATARS_H_

#include <cstdint>
#include <memory>
#include <nlohmann/json.hpp>

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"

#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/Implementations/BaseAvatar.h"

#include "ZBE/core/system/system.h"

#include "ZBE/factories/Factory.h"

namespace zbe{

//Nombre para el avatar!!! (que towardsAvatar, observerAvatar, lookatAvatar, )
// Convierte de una entidad con lookAt a un avatar de posicion y velocidad.

class TargetToDirAvt : public MAvatar<Vector3D, Vector3D, Vector3D>, AvatarImp {
public:
//TODO el avatar hace lo que tiene que hacer, ahora es el comportamiento el que tiene que hacer la magia
//TODO añadir un vector UP
//TODO comportamiento será el encargado de coger los datos de este este avatar y hacer transformaciones de espacios vectoriales
  /** \brief
   */
   void setupEntity(std::shared_ptr<Entity> entity, uint64_t positionidx, uint64_t targetidx, uint64_t upwardsidx, uint64_t scaleidx) {
     AvatarImp::setupEntity(entity);
     _Avatar<1, Vector3D>::setup(&getPosition, &setPosition, (void*)this);
     _Avatar<2, Vector3D>::setup(&getVelocity, &setVelocity, (void*)this);
     _Avatar<3, Vector3D>::setup(&getUpwards, &setUpwards, (void*)this);
     position = entity->getVector3D(positionidx);
     target = entity->getVector3D(targetidx);
     upwards = entity->getVector3D(upwardsidx);
     scale = entity->getFloat(scaleidx);
   }

   static std::shared_ptr<Value<Vector3D> > getPosition(void *instance) {
     return ((TargetToDirAvt*)instance)->position;
   }

   static std::shared_ptr<Value<Vector3D> > getVelocity(void *instance) {
     auto& position = ((TargetToDirAvt*)instance)->position;
     auto& target =   ((TargetToDirAvt*)instance)->target;
     auto& scale =    ((TargetToDirAvt*)instance)->scale;
     auto p = position->get();
     auto t = target->get();
     auto s = scale->get();
     auto v = (t - p).normalize();// * s;
     auto r = std::make_shared<SimpleValue<Vector3D> >();
     r->set(v);
     return r;
   }

   static std::shared_ptr<Value<Vector3D> > getUpwards(void *instance) {
     auto u = normalize(((TargetToDirAvt*)instance)->upwards->get());
     auto r = std::make_shared<SimpleValue<Vector3D> >();
     r->set(u);
     return r;
   }

   static void setPosition(void *instance, Vector3D position) {
     auto& _position = ((TargetToDirAvt*)instance)->position;
     auto& _target =  ((TargetToDirAvt*)instance)->target;

     auto p = _position->get();
     auto t = _target->get();
     auto offset = t - p;

     _position->set(position);
     _target->set(position + offset);
   }

   static void setVelocity(void*, Vector3D) {
     // TODO completar haciendo que al modificar la velocidad modifique la orientación de Target
     // para que apunte donde dice la velocidad
     // y hacemos que scale valga el modulo de la velocidad.
   }

   static void setUpwards(void* instance, Vector3D upwards) {
     ((TargetToDirAvt*)instance)->upwards->set(upwards);
   }

   std::shared_ptr<Entity> getEntity() {
     assert(false);
   }
//TODO hacer factoría y probar (un cachopo)
//TODO Usar el UniformLinearMotion (no fixed) para mover la cámara
//TODO girar cámara con ratón

private:
  std::shared_ptr<Value<Vector3D> > position;
  std::shared_ptr<Value<Vector3D> > target;
  std::shared_ptr<Value<Vector3D> > upwards;
  std::shared_ptr<Value<float> > scale;
};

class TargetToDirAvtFtry : public Factory {
  /** \brief Builds a TargetToDirAvt.
   *  \param name Name for the created TargetToDirAvt.
   *  \param cfgId TargetToDirAvt's configuration id.
   */
  void create(std::string name, uint64_t){
    using namespace std::string_literals;

    auto ttdavt = std::make_shared<TargetToDirAvt>();
    ttdavtRsrc.insert("TargetToDirAvt."s + name, ttdavt);
  }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId){
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      if (!j["entity"].is_string()) {
        SysError::setError("TargetToDirAvtFtry " + name + " config for entity must be a string."s);
        return;
      }
      if (!j["lists"].is_object()) {
        SysError::setError("TargetToDirAvtFtry " + name + " config for lists must be an object. But is "s + j["lists"].type_name());
        return;
      }
      if (!j["positionIdx"].is_string()) {
        SysError::setError("TargetToDirAvtFtry " + name + " config for positionIdx must be a string."s);
        return;
      }
      if (!j["targetIdx"].is_string()) {
        SysError::setError("TargetToDirAvtFtry " + name + " config for targetIdx must be a string."s);
        return;
      }
      if (!j["upwardsIdx"].is_string()) {
        SysError::setError("TargetToDirAvtFtry " + name + " config for upwardsIdx must be a string."s);
        return;
      }
      if (!j["scaleIdx"].is_string()) {
        SysError::setError("TargetToDirAvtFtry " + name + " config for scaleIdx must be a string."s);
        return;
      }

      std::string entityName = j["entity"].get<std::string>();
      if(!entityRsrc.contains("Entity."s + entityName)) {
        SysError::setError("TargetToDirAvtFtry config for entity: "s + entityName + " is not an entity name."s);
        return;
      }

// TODO coger datos de la entidad y no de stores. Patanes!
std::shared_ptr<Entity> ent = entityRsrc.get("Entity."s + entityName);

      std::string positionIdxName = j["positionIdx"].get<std::string>();
      if(!dict.contains(positionIdxName)) {
        SysError::setError("TargetToDirAvtFtry config for positionIdx: "s + positionIdxName + " is not an positionIdx name."s);
        return;
      }
      std::string targetIdxName = j["targetIdx"].get<std::string>();
      if(!dict.contains(targetIdxName)) {
        SysError::setError("TargetToDirAvtFtry config for targetIdx: "s + targetIdxName + " is not an targetIdx name."s);
        return;
      }
      std::string upwardsIdxName = j["upwardsIdx"].get<std::string>();
      if(!dict.contains(upwardsIdxName)) {
        SysError::setError("TargetToDirAvtFtry config for upwardsIdx: "s + upwardsIdxName + " is not an upwardsIdx name."s);
        return;
      }
      std::string scaleIdxName = j["scaleIdx"].get<std::string>();
      if(!dict.contains(scaleIdxName)) {
        SysError::setError("TargetToDirAvtFtry config for scaleIdx: "s + scaleIdxName + " is not an scaleIdx name."s);
        return;
      }

      uint64_t positionIdx = dict.get(positionIdxName);
      uint64_t targetIdx = dict.get(targetIdxName);
      uint64_t upwardsIdx = dict.get(upwardsIdxName);
      uint64_t scaleIdx = dict.get(scaleIdxName);

      std::shared_ptr<TargetToDirAvt> avt = ttdavtRsrc.get("TargetToDirAvt."s + name);

      avt->setupEntity(ent, positionIdx, targetIdx, upwardsIdx, scaleIdx);

      auto listsCfg = j["lists"];
      for (auto& listCfg : listsCfg.items()) {
printf("1\n");fflush(stdout);
        if (!listCfg.value().is_string()) {
          SysError::setError("TargetToDirAvt " + name + " config for lists must contain strings. But is "s + listCfg.value().type_name());
          return;
        }
        printf("2: %s : %s\n",listCfg.key().c_str(), listCfg.value().get<std::string>().c_str());fflush(stdout);
        auto list = listStore.get("List." + listCfg.key());
        printf("3\n");fflush(stdout);
        auto ticket = list->push_front(avt);
printf("4\n");fflush(stdout);
        ent->addTicket(dict.get(listCfg.value().get<std::string>()), ticket);
      }
printf("5\n");fflush(stdout);
      ttdavtRsrc.remove("TargetToDirAvt."s + name);
    } else {
      SysError::setError("Avatar config for "s + name + " not found."s);
    }
  }

private:
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc    = RsrcStore<nlohmann::json>::getInstance();
  RsrcDictionary<std::string>& strStore    = RsrcDictionary<std::string>::getInstance();
  RsrcStore<Vector3D>& v3dStore            = RsrcStore<Vector3D>::getInstance();
  RsrcStore<TargetToDirAvt>& ttdavtRsrc    = RsrcStore<TargetToDirAvt>::getInstance();
  RsrcStore<Entity>& entityRsrc            = RsrcStore<Entity>::getInstance();
  RsrcStore<TicketedForwardList<MAvatar<Vector3D, Vector3D, Vector3D> > >& listStore = RsrcStore<TicketedForwardList<MAvatar<Vector3D, Vector3D, Vector3D> > >::getInstance();
};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_CUSTOMAVATARS_H_
