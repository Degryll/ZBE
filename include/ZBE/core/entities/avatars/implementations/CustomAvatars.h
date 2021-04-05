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
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"

#include "ZBE/core/system/system.h"

#include "ZBE/factories/Factory.h"

namespace zbe{

// Convierte de una entidad con lookAt a un avatar de posicion y velocidad.
// TODO: copiar TargetToDirAvt y quitarle el up
// TODO: pero antes probar si podemos usar el de tres vectores
class TargetToDirAvt : public MAvatar<Vector3D, Vector3D, Vector3D>, AvatarImp {
public:

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
     scale = entity->getFloat(scaleidx); //TODO sobra scale? borrar en toda la clase?
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

class PosTargetToPosDirAvt : public MAvatar<Vector3D, Vector3D>, AvatarImp {
public:

  /** \brief
   */
   void setupEntity(std::shared_ptr<Entity> entity, uint64_t positionidx, uint64_t targetidx) {
     AvatarImp::setupEntity(entity);
     _Avatar<1, Vector3D>::setup(&getPosition, &setPosition, (void*)this);
     _Avatar<2, Vector3D>::setup(&getDirection, &setDirection, (void*)this);
     position = entity->getVector3D(positionidx);
     target = entity->getVector3D(targetidx);
   }

   static std::shared_ptr<Value<Vector3D> > getPosition(void *instance) {
     return ((PosTargetToPosDirAvt*)instance)->position;
   }

   static std::shared_ptr<Value<Vector3D> > getDirection(void *instance) {
     auto& position = ((PosTargetToPosDirAvt*)instance)->position;
     auto& target =   ((PosTargetToPosDirAvt*)instance)->target;
     auto p = position->get();
     auto t = target->get();
     auto v = (t - p).normalize();// * s;
     auto r = std::make_shared<SimpleValue<Vector3D> >();
     r->set(v);
     return r;
   }

   static void setPosition(void *instance, Vector3D position) {
     auto& _position = ((PosTargetToPosDirAvt*)instance)->position;
     auto& _target =  ((PosTargetToPosDirAvt*)instance)->target;
     auto p = _position->get();
     auto t = _target->get();
     auto offset = t - p;
     _position->set(position);
     _target->set(position + offset);
   }

   static void setDirection(void*, Vector3D) {
     assert(false);
   }

   std::shared_ptr<Entity> getEntity() {
     assert(false);
   }


private:
  std::shared_ptr<Value<Vector3D> > position;
  std::shared_ptr<Value<Vector3D> > target;
};


class LookAtToPitchAvt : public MAvatar<Vector3D, Vector3D>, AvatarImp {
public:

  /** \brief
   */
   void setupEntity(std::shared_ptr<Entity> entity, uint64_t positionidx, uint64_t targetidx, uint64_t upwardsidx) {
     AvatarImp::setupEntity(entity);
     _Avatar<1, Vector3D>::setup(&getTarget, &setTarget, (void*)this);
     _Avatar<2, Vector3D>::setup(&getRotation, &setRotation, (void*)this);
     position = entity->getVector3D(positionidx);
     target = entity->getVector3D(targetidx);
     upwards = entity->getVector3D(upwardsidx);
   }

   static std::shared_ptr<Value<Vector3D> > getTarget(void *instance) {
     auto& position = ((LookAtToPitchAvt*)instance)->position;
     auto& target =   ((LookAtToPitchAvt*)instance)->target;
     auto p = position->get();
     auto t = target->get();
     auto r = std::make_shared<SimpleValue<Vector3D> >();
     r->set(t - p);
     return r;
   }

   static std::shared_ptr<Value<Vector3D> > getRotation(void *instance) {
     auto& position = ((LookAtToPitchAvt*)instance)->position;
     auto& target =   ((LookAtToPitchAvt*)instance)->target;
     auto& upwards =    ((LookAtToPitchAvt*)instance)->upwards;
     auto& _dxu =    ((LookAtToPitchAvt*)instance)->dxu;
     auto d = target->get() - position->get();
     auto u = upwards->get();
     _dxu = cross(d, u);
     auto r = std::make_shared<SimpleValue<Vector3D> >();
     r->set(_dxu);
     return r;
   }

   static void setTarget(void *instance, Vector3D target) {
     auto& _position = ((LookAtToPitchAvt*)instance)->position;
     auto& _target =  ((LookAtToPitchAvt*)instance)->target;
     auto& _upwards =    ((LookAtToPitchAvt*)instance)->upwards;
     auto& _dxu =    ((LookAtToPitchAvt*)instance)->dxu;
     auto newd = target;
     auto u = cross(_dxu, newd).normalize();
     _target->set(target + _position->get());
     _upwards->set(u);
   }

   static void setRotation(void*, Vector3D) {
     // TODO Repensar si tiene sentido realizar alguna conversión en este punto o incluir asserts para evitar que sea llamado.
   }

   std::shared_ptr<Entity> getEntity() {
     assert(false);
   }

private:

  std::shared_ptr<Value<Vector3D> > position;
  std::shared_ptr<Value<Vector3D> > target;
  std::shared_ptr<Value<Vector3D> > upwards;
  Vector3D dxu;
};

class LookAtToYawAvt : public MAvatar<Vector3D, Vector3D>, AvatarImp {
public:

  /** \brief
   */
   void setupEntity(std::shared_ptr<Entity> entity, uint64_t positionidx, uint64_t targetidx, uint64_t upwardsidx) {
     AvatarImp::setupEntity(entity);
     _Avatar<1, Vector3D>::setup(&getTarget, &setTarget, (void*)this);
     _Avatar<2, Vector3D>::setup(&getRotation, &setRotation, (void*)this);
     position = entity->getVector3D(positionidx);
     target = entity->getVector3D(targetidx);
     upwards = entity->getVector3D(upwardsidx);
   }

   static std::shared_ptr<Value<Vector3D> > getTarget(void *instance) {
     auto& position = ((LookAtToYawAvt*)instance)->position;
     auto& target =   ((LookAtToYawAvt*)instance)->target;
     auto p = position->get();
     auto t = target->get();
     auto r = std::make_shared<SimpleValue<Vector3D> >();
     r->set(t - p);
     return r;
   }

   static std::shared_ptr<Value<Vector3D> > getRotation(void *instance) {
     return ((LookAtToYawAvt*)instance)->upwards;
   }

   static void setTarget(void *instance, Vector3D target) {
     auto& _target =  ((LookAtToYawAvt*)instance)->target;
     _target->set(target);
   }

   static void setRotation(void*, Vector3D) {
     // TODO Repensar si tiene sentido realizar alguna conversión en este punto o incluir asserts para evitar que sea llamado.
   }

   std::shared_ptr<Entity> getEntity() {
     assert(false);
   }

private:

  std::shared_ptr<Value<Vector3D> > position;
  std::shared_ptr<Value<Vector3D> > target;
  std::shared_ptr<Value<Vector3D> > upwards;
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
        if (!listCfg.value().is_string()) {
          SysError::setError("TargetToDirAvt " + name + " config for lists must contain strings. But is "s + listCfg.value().type_name());
          return;
        }
        auto list = listStore.get("List." + listCfg.key());
        auto ticket = list->push_front(avt);
        ent->addTicket(dict.get(listCfg.value().get<std::string>()), ticket);
      }
      ttdavtRsrc.remove("TargetToDirAvt."s + name);
    } else {
      SysError::setError("Avatar config for "s + name + " not found."s);
    }
  }

private:
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc    = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<TargetToDirAvt>& ttdavtRsrc    = RsrcStore<TargetToDirAvt>::getInstance();
  RsrcStore<Entity>& entityRsrc            = RsrcStore<Entity>::getInstance();
  RsrcStore<TicketedForwardList<MAvatar<Vector3D, Vector3D, Vector3D> > >& listStore = RsrcStore<TicketedForwardList<MAvatar<Vector3D, Vector3D, Vector3D> > >::getInstance();
};

class PosTargetToPosDirAvtFtry : public Factory {
  /** \brief Builds a TargetToDirAvt.
   *  \param name Name for the created TargetToDirAvt.
   *  \param cfgId TargetToDirAvt's configuration id.
   */
  void create(std::string name, uint64_t){
    using namespace std::string_literals;

    auto ttdavt = std::make_shared<PosTargetToPosDirAvt>();
    pttpdavtStore.insert("PosTargetToPosDirAvt."s + name, ttdavt);
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
        SysError::setError("PosTargetToPosDirAvtFtry " + name + " config for entity must be a string."s);
        return;
      }
      if (!j["lists"].is_object()) {
        SysError::setError("PosTargetToPosDirAvtFtry " + name + " config for lists must be an object. But is "s + j["lists"].type_name());
        return;
      }
      if (!j["positionIdx"].is_string()) {
        SysError::setError("PosTargetToPosDirAvtFtry " + name + " config for positionIdx must be a string."s);
        return;
      }
      if (!j["targetIdx"].is_string()) {
        SysError::setError("PosTargetToPosDirAvtFtry " + name + " config for targetIdx must be a string."s);
        return;
      }

      std::string entityName = j["entity"].get<std::string>();
      if(!entityRsrc.contains("Entity."s + entityName)) {
        SysError::setError("PosTargetToPosDirAvtFtry config for entity: "s + entityName + " is not an entity name."s);
        return;
      }

      std::shared_ptr<Entity> ent = entityRsrc.get("Entity."s + entityName);

      std::string positionIdxName = j["positionIdx"].get<std::string>();
      if(!dict.contains(positionIdxName)) {
        SysError::setError("PosTargetToPosDirAvtFtry config for positionIdx: "s + positionIdxName + " is not an positionIdx name."s);
        return;
      }
      std::string targetIdxName = j["targetIdx"].get<std::string>();
      if(!dict.contains(targetIdxName)) {
        SysError::setError("PosTargetToPosDirAvtFtry config for targetIdx: "s + targetIdxName + " is not an targetIdx name."s);
        return;
      }

      uint64_t positionIdx = dict.get(positionIdxName);
      uint64_t targetIdx = dict.get(targetIdxName);

      std::shared_ptr<PosTargetToPosDirAvt> avt = pttpdavtStore.get("PosTargetToPosDirAvt."s + name);

      avt->setupEntity(ent, positionIdx, targetIdx);

      auto listsCfg = j["lists"];
      for (auto& listCfg : listsCfg.items()) {
        if (!listCfg.value().is_string()) {
          SysError::setError("PosTargetToPosDirAvt " + name + " config for lists must contain strings. But is "s + listCfg.value().type_name());
          return;
        }
        auto list = listStore.get("List." + listCfg.key());
        auto ticket = list->push_front(avt);
        ent->addTicket(dict.get(listCfg.value().get<std::string>()), ticket);
      }
      pttpdavtStore.remove("PosTargetToPosDirAvt."s + name);
    } else {
      SysError::setError("Avatar config for "s + name + " not found."s);
    }
  }

private:
  NameRsrcDictionary &dict                                                 = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc                                    = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<PosTargetToPosDirAvt>& pttpdavtStore                            = RsrcStore<PosTargetToPosDirAvt>::getInstance();
  RsrcStore<Entity>& entityRsrc                                            = RsrcStore<Entity>::getInstance();
  RsrcStore<TicketedForwardList<MAvatar<Vector3D, Vector3D> > >& listStore = RsrcStore<TicketedForwardList<MAvatar<Vector3D, Vector3D> > >::getInstance();
};

class LookAtToPitchAvtFtry : public Factory {
  /** \brief Builds a LookAtToPitchAvt.
   *  \param name Name for the created LookAtToPitchAvt.
   *  \param cfgId LookAtToPitchAvt's configuration id.
   */
  void create(std::string name, uint64_t){
    using namespace std::string_literals;

    auto latpavt = std::make_shared<LookAtToPitchAvt>();
    latpAvtStore.insert("LookAtToPitchAvt."s + name, latpavt);
  }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId){
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configStore.get(cfgId);
    if(cfg) {
      auto j = *cfg;
      if (!j["entity"].is_string()) {
        SysError::setError("LookAtToPitchAvtFtry " + name + " config for entity must be a string."s);
        return;
      }
      if (!j["lists"].is_object()) {
        SysError::setError("LookAtToPitchAvtFtry " + name + " config for lists must be an object. But is "s + j["lists"].type_name());
        return;
      }
      if (!j["positionIdx"].is_string()) {
        SysError::setError("LookAtToPitchAvtFtry " + name + " config for positionIdx must be a string."s);
        return;
      }
      if (!j["targetIdx"].is_string()) {
        SysError::setError("LookAtToPitchAvtFtry " + name + " config for targetIdx must be a string."s);
        return;
      }
      if (!j["upwardsIdx"].is_string()) {
        SysError::setError("LookAtToPitchAvtFtry " + name + " config for upwardsIdx must be a string."s);
        return;
      }

      std::string entityName = j["entity"].get<std::string>();
      if(!entityStore.contains("Entity."s + entityName)) {
        SysError::setError("LookAtToPitchAvtFtry config for entity: "s + entityName + " is not an entity name."s);
        return;
      }

      std::shared_ptr<Entity> ent = entityStore.get("Entity."s + entityName);

      std::string positionIdxName = j["positionIdx"].get<std::string>();
      if(!dict.contains(positionIdxName)) {
        SysError::setError("LookAtToPitchAvtFtry config for positionIdx: "s + positionIdxName + " is not an positionIdx name."s);
        return;
      }
      std::string targetIdxName = j["targetIdx"].get<std::string>();
      if(!dict.contains(targetIdxName)) {
        SysError::setError("LookAtToPitchAvtFtry config for targetIdx: "s + targetIdxName + " is not an targetIdx name."s);
        return;
      }
      std::string upwardsIdxName = j["upwardsIdx"].get<std::string>();
      if(!dict.contains(upwardsIdxName)) {
        SysError::setError("LookAtToPitchAvtFtry config for upwardsIdx: "s + upwardsIdxName + " is not an upwardsIdx name."s);
        return;
      }

      uint64_t positionIdx = dict.get(positionIdxName);
      uint64_t targetIdx = dict.get(targetIdxName);
      uint64_t upwardsIdx = dict.get(upwardsIdxName);

      std::shared_ptr<LookAtToPitchAvt> avt = latpAvtStore.get("LookAtToPitchAvt."s + name);

      avt->setupEntity(ent, positionIdx, targetIdx, upwardsIdx);

      auto listsCfg = j["lists"];
      for (auto& listCfg : listsCfg.items()) {
        if (!listCfg.value().is_string()) {
          SysError::setError("LookAtToPitchAvt " + name + " config for lists must contain strings. But is "s + listCfg.value().type_name());
          return;
        }
        auto list = listStore.get("List." + listCfg.key());
        auto ticket = list->push_front(avt);
        ent->addTicket(dict.get(listCfg.value().get<std::string>()), ticket);
      }
      latpAvtStore.remove("LookAtToPitchAvt."s + name);
    } else {
      SysError::setError("Avatar config for "s + name + " not found."s);
    }
  }

private:
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configStore    = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<LookAtToPitchAvt>& latpAvtStore    = RsrcStore<LookAtToPitchAvt>::getInstance();
  RsrcStore<Entity>& entityStore            = RsrcStore<Entity>::getInstance();
  RsrcStore<TicketedForwardList<MAvatar<Vector3D, Vector3D> > >& listStore = RsrcStore<TicketedForwardList<MAvatar<Vector3D, Vector3D> > >::getInstance();
};

class LookAtToYawAvtFtry : public Factory {
  /** \brief Builds a LookAtToYawAvt.
   *  \param name Name for the created LookAtToYawAvt.
   *  \param cfgId LookAtToYawAvt's configuration id.
   */
  void create(std::string name, uint64_t){
    using namespace std::string_literals;

    auto latpavt = std::make_shared<LookAtToYawAvt>();
    latpAvtStore.insert("LookAtToYawAvt."s + name, latpavt);
  }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId){
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configStore.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      if (!j["entity"].is_string()) {
        SysError::setError("LookAtToYawAvtFtry " + name + " config for entity must be a string."s);
        return;
      }
      if (!j["lists"].is_object()) {
        SysError::setError("LookAtToYawAvtFtry " + name + " config for lists must be an object. But is "s + j["lists"].type_name());
        return;
      }
      if (!j["positionIdx"].is_string()) {
        SysError::setError("LookAtToYawAvtFtry " + name + " config for positionIdx must be a string."s);
        return;
      }
      if (!j["targetIdx"].is_string()) {
        SysError::setError("LookAtToYawAvtFtry " + name + " config for targetIdx must be a string."s);
        return;
      }
      if (!j["upwardsIdx"].is_string()) {
        SysError::setError("LookAtToYawAvtFtry " + name + " config for upwardsIdx must be a string."s);
        return;
      }

      std::string entityName = j["entity"].get<std::string>();
      if(!entityStore.contains("Entity."s + entityName)) {
        SysError::setError("LookAtToYawAvtFtry config for entity: "s + entityName + " is not an entity name."s);
        return;
      }

      std::shared_ptr<Entity> ent = entityStore.get("Entity."s + entityName);

      std::string positionIdxName = j["positionIdx"].get<std::string>();
      if(!dict.contains(positionIdxName)) {
        SysError::setError("LookAtToYawAvtFtry config for positionIdx: "s + positionIdxName + " is not an positionIdx name."s);
        return;
      }
      std::string targetIdxName = j["targetIdx"].get<std::string>();
      if(!dict.contains(targetIdxName)) {
        SysError::setError("LookAtToYawAvtFtry config for targetIdx: "s + targetIdxName + " is not an targetIdx name."s);
        return;
      }
      std::string upwardsIdxName = j["upwardsIdx"].get<std::string>();
      if(!dict.contains(upwardsIdxName)) {
        SysError::setError("LookAtToYawAvtFtry config for upwardsIdx: "s + upwardsIdxName + " is not an upwardsIdx name."s);
        return;
      }

      uint64_t positionIdx = dict.get(positionIdxName);
      uint64_t targetIdx = dict.get(targetIdxName);
      uint64_t upwardsIdx = dict.get(upwardsIdxName);

      std::shared_ptr<LookAtToYawAvt> avt = latpAvtStore.get("LookAtToYawAvt."s + name);

      avt->setupEntity(ent, positionIdx, targetIdx, upwardsIdx);

      auto listsCfg = j["lists"];
      for (auto& listCfg : listsCfg.items()) {
        if (!listCfg.value().is_string()) {
          SysError::setError("LookAtToYawAvt " + name + " config for lists must contain strings. But is "s + listCfg.value().type_name());
          return;
        }
        auto list = listStore.get("List." + listCfg.key());
        auto ticket = list->push_front(avt);
        ent->addTicket(dict.get(listCfg.value().get<std::string>()), ticket);
      }
      latpAvtStore.remove("LookAtToYawAvt."s + name);
    } else {
      SysError::setError("Avatar config for "s + name + " not found."s);
    }
  }

private:
  NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configStore    = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<LookAtToYawAvt>& latpAvtStore    = RsrcStore<LookAtToYawAvt>::getInstance();
  RsrcStore<Entity>& entityStore            = RsrcStore<Entity>::getInstance();
  RsrcStore<TicketedForwardList<MAvatar<Vector3D, Vector3D> > >& listStore = RsrcStore<TicketedForwardList<MAvatar<Vector3D, Vector3D> > >::getInstance();
};


}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_AVATARS_IMPLEMENTATIONS_CUSTOMAVATARS_H_
