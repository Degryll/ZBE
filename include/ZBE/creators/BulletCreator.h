/**
 * Copyright 2011 Batis Degryll Ludo
 * @file BulletCreator.h
 * @since 2021/03/11
 * @date 2021/03/11
 * @author Degryll Batis Ludo
 * @brief A class that creates bullets.
 */

#ifndef ZBE_CREATORS_BULLETCREATOR_H_
#define ZBE_CREATORS_BULLETCREATOR_H_

#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "ZBE/events/handlers/time/EntityEraser.h"
#include "ZBE/core/tools/time/ContextTime.h"

namespace zbe {

  // BulletCreator
  //   Recibirá en ejecución:
  //     Vec3D posición
  //     Vec3D dirección
  //   Recibirá en configuración:
  //     Vec3D velocidad
  //     uint64_t gráficos
  //     uint64_t indices values
  //     Ids de listas: Gráficos, Comportamientos.
  //     Ids de values de la entidad.
  //   Creará:
  //     Entidad
  //     Avatar pintado
  //     Avatar MRU
  //   Configurará
  //     Avatar pintado en lista de Gráficos dada
  //     Avatar MRU en lista de Comportamientos dada

class BulletCreatorFtry;

class BulletCreator {
public:
  friend class BulletCreatorFtry;

  BulletCreator() : speed(),
    speedIdx(),
    gid(),
    gidIdx(),
    rotation(),
    rotationIdx(),
    scale(),
    scaleIdx(),
    positionIdx(),
    directionIdx(),
    graphicList(),
    behaviorList(),
    graphicListStore(RsrcStore<GraphicList>::getInstance()),
    behaviorListStore(RsrcStore<BehaviorList>::getInstance()),
    teg(),
    time(),
    ticketId(),
    cTime() {}

  void operator()(Vector3D position, Vector3D direction) {
      using namespace std::string_literals;
      std::shared_ptr<Entity> e = std::make_shared<Entity>();

      e->set<uint64_t>(gidIdx, std::make_shared<SimpleValue<uint64_t>>(SimpleValue<uint64_t>(gid)));
      e->set<double>(scaleIdx, std::make_shared<SimpleValue<double>>(SimpleValue<double>(scale)));
      e->set<double>(rotationIdx, std::make_shared<SimpleValue<double>>(SimpleValue<double>(rotation)));
      e->set<Vector3D>(directionIdx, std::make_shared<SimpleValue<Vector3D>>(SimpleValue<Vector3D>(direction.normalize()*speed)));
      e->set<Vector3D>(positionIdx, std::make_shared<SimpleValue<Vector3D>>(SimpleValue<Vector3D>(position)));

      std::shared_ptr<MBaseAvatar<uint64_t, double,  double, Vector3D, Vector3D> > drawAvt = std::make_shared<MBaseAvatar<uint64_t, double,  double, Vector3D, Vector3D> >();

      std::array<uint64_t, 5> gidxArr = {gidIdx, scaleIdx, rotationIdx, directionIdx, positionIdx};

      drawAvt->setupEntity(e, gidxArr);

      for (auto listref : graphicList) {
        auto list = graphicListStore.get("List."s + listref.first);
        auto ticket = list->push_front(drawAvt);
        e->addTicket(listref.second, ticket);
      }

      std::shared_ptr<MBaseAvatar<Vector3D, Vector3D> > bhvAvt = std::make_shared<MBaseAvatar<Vector3D, Vector3D> >();

      std::array<uint64_t, 2> bidxArr = {directionIdx, positionIdx};

      bhvAvt->setupEntity(e, bidxArr);

      for (auto listref : behaviorList) {
        auto list = behaviorListStore.get("List."s + listref.first);
        auto ticket = list->push_front(bhvAvt);
        e->addTicket(listref.second, ticket);
      }
      std::shared_ptr<EntityEraserTH> ee = std::make_shared<EntityEraserTH>(e);
      auto ticket = teg->addRelativeTimer(ee, time);
      e->addTicket(ticketId, ticket);
      e->setContextTime(cTime);
  }

  void setSpeed(double speed, uint64_t idx) {
    this->speed = speed;
    speedIdx = idx;
  }

  void setGid(uint64_t gid, uint64_t idx) {
    this->gid = gid;
    gidIdx = idx;
  }

  void setRotation(double rotation, uint64_t idx) {
    this->rotation = rotation;
    rotationIdx = idx;
  }

  void setScale(double scale, uint64_t idx) {
    this->scale = scale;
    scaleIdx = idx;
  }

  void setPositionId(uint64_t idx) {
    positionIdx = idx;
  }

  void setDirectionId(uint64_t idx) {
    directionIdx = idx;
  }

  void setGraphicList(std::vector<std::pair<std::string, uint64_t>> graphicList) {
    this->graphicList = graphicList;
  }

  void setBehaviorList(std::vector<std::pair<std::string, uint64_t>> behaviorList) {
    this->behaviorList = behaviorList;
  }

  void setTeg(std::shared_ptr<TimeEventGenerator> teg, uint64_t time, uint64_t ticketId) {
    this->teg = teg;
    this->time = time;
    this->ticketId = ticketId;
  }

  void setContextTime(std::shared_ptr<ContextTime> cTime) {
    this->cTime = cTime;
  }

private:
  using GraphicList = TicketedForwardList<MAvatar<uint64_t, double, double, Vector3D, Vector3D> >;
  using BehaviorList = TicketedForwardList<MAvatar<Vector3D, Vector3D> >;
  double speed;
  uint64_t speedIdx;
  uint64_t gid;
  uint64_t gidIdx;
  double rotation;
  uint64_t rotationIdx;
  double scale;
  uint64_t scaleIdx;
  uint64_t positionIdx;
  uint64_t directionIdx;
  std::vector<std::pair<std::string, uint64_t>> graphicList;
  std::vector<std::pair<std::string, uint64_t>> behaviorList;
  RsrcStore<GraphicList> &graphicListStore = RsrcStore<GraphicList>::getInstance();
  RsrcStore<BehaviorList> &behaviorListStore = RsrcStore<BehaviorList>::getInstance();
  std::shared_ptr<TimeEventGenerator> teg;
  uint64_t time;
  uint64_t ticketId;
  std::shared_ptr<ContextTime> cTime;
};

class BulletCreatorFtry : virtual public Factory {
public:
  void create(std::string name, uint64_t cfgId){
    using namespace std::string_literals;
    std::shared_ptr<BulletCreator> bc = std::shared_ptr<BulletCreator>(new BulletCreator);  // std::make_shared<SineOscillator>();
    bulletCreatorStore.insert("BulletCreator."s + name, bc);
  }

  void setup(std::string name, uint64_t cfgId){
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configStore.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      if (!j["speed"].is_string()) {
        SysError::setError("BulletCreatorFtry  " + name + " config for speed: "s + j["speed"].get<std::string>() + ": must be a literal double name."s);
        return;
      }

      if (!j["speedIdx"].is_string()) {
        SysError::setError("BulletCreatorFtry  " + name + " config for speedIdx: "s + j["speedIdx"].get<std::string>() + ": must be a literal uint64_t name."s);
        return;
      }

      if (!j["gid"].is_string()) {
        SysError::setError("BulletCreatorFtry  " + name + " config for gid: "s + j["gid"].get<std::string>() + ": must be a literal uint64_t name."s);
        return;
      }

      if (!j["gidIdx"].is_string()) {
        SysError::setError("BulletCreatorFtry  " + name + " config for gidIdx: "s + j["gidIdx"].get<std::string>() + ": must be a literal uint64_t name."s);
        return;
      }

      if (!j["rotation"].is_string()) {
        SysError::setError("BulletCreatorFtry  " + name + " config for rotation: "s + j["rotation"].get<std::string>() + ": must be a literal double name."s);
        return;
      }

      if (!j["rotationIdx"].is_string()) {
        SysError::setError("BulletCreatorFtry  " + name + " config for rotationIdx: "s + j["rotationIdx"].get<std::string>() + ": must be a literal uint64_t name."s);
        return;
      }

      if (!j["scale"].is_string()) {
        SysError::setError("BulletCreatorFtry  " + name + " config for scale: "s + j["scale"].get<std::string>() + ": must be a literal double name."s);
        return;
      }

      if (!j["scaleIdx"].is_string()) {
        SysError::setError("BulletCreatorFtry  " + name + " config for scaleIdx: "s + j["scaleIdx"].get<std::string>() + ": must be a literal uint64_t name."s);
        return;
      }

      if (!j["positionIdx"].is_string()) {
        SysError::setError("BulletCreatorFtry  " + name + " config for positionIdx: "s + j["positionIdx"].get<std::string>() + ": must be a literal uint64_t name."s);
        return;
      }

      if (!j["directionIdx"].is_string()) {
        SysError::setError("BulletCreatorFtry  " + name + " config for directionIdx: "s + j["directionIdx"].get<std::string>() + ": must be a literal uint64_t name."s);
        return;
      }

      if (!j["graphicList"].is_object()) {
        SysError::setError("BulletCreatorFtry  " + name + " config for graphicList must be an object."s);
        return;
      }

      if (!j["behaviorList"].is_object()) {
        SysError::setError("BulletCreatorFtry  " + name + " config for behaviorList must be an object."s);
        return;
      }

      if (!j["teg"].is_string()) {
        SysError::setError("BulletCreatorFtry config for timeEventGenerator: must be an timeEventGenerator name."s);
        return;
      }

      if (!j["time"].is_string()) {
        SysError::setError("BulletCreatorFtry config for time: must be a time name."s);
        return;
      }

      if (!j["contextTime"].is_string()) {
        SysError::setError("BulletCreatorFtry config for contextTime: must be a context time name."s);
        return;
      }

      if (!j["ticketId"].is_string()) {
        SysError::setError("BulletCreatorFtry config for ticketId: must be a ticketId name."s);
        return;
      }

      std::string speedName = j["speed"].get<std::string>();
      if(!doubleDict.contains(speedName)) {
        SysError::setError("BulletCreatorFtry  " + name + " config for speed: "s + speedName + " is not a double literal."s);
        return;
      }

      std::string speedIdxName = j["speedIdx"].get<std::string>();
      if(!uintDict.contains(speedIdxName)) {
        SysError::setError("BulletCreatorFtry  " + name + " config for speedIdx: "s + speedIdxName + " is not a uint64_t literal."s);
        return;
      }

      std::string gidName = j["gid"].get<std::string>();
      if(!uintDict.contains(gidName)) {
        SysError::setError("BulletCreatorFtry  " + name + " config for gid: "s + gidName + " is not a uint64_t literal."s);
        return;
      }

      std::string gidIdxName = j["gidIdx"].get<std::string>();
      if(!uintDict.contains(gidIdxName)) {
        SysError::setError("BulletCreatorFtry  " + name + " config for gidIdx: "s + gidIdxName + " is not a uint64_t literal."s);
        return;
      }

      std::string rotationName = j["rotation"].get<std::string>();
      if(!doubleDict.contains(rotationName)) {
        SysError::setError("BulletCreatorFtry  " + name + " config for rotation: "s + rotationName + " is not a double literal."s);
        return;
      }

      std::string rotationIdxName = j["rotationIdx"].get<std::string>();
      if(!uintDict.contains(rotationIdxName)) {
        SysError::setError("BulletCreatorFtry  " + name + " config for rotationIdx: "s + rotationIdxName + " is not a uint64_t literal."s);
        return;
      }

      std::string scaleName = j["scale"].get<std::string>();
      if(!doubleDict.contains(scaleName)) {
        SysError::setError("BulletCreatorFtry  " + name + " config for scale: "s + scaleName + " is not a double literal."s);
        return;
      }

      std::string scaleIdxName = j["scaleIdx"].get<std::string>();
      if(!uintDict.contains(scaleIdxName)) {
        SysError::setError("BulletCreatorFtry  " + name + " config for scaleIdx: "s + scaleIdxName + " is not a uint64_t literal."s);
        return;
      }

      std::string positionIdxName = j["positionIdx"].get<std::string>();
      if(!uintDict.contains(positionIdxName)) {
        SysError::setError("BulletCreatorFtry  " + name + " config for positionIdx: "s + positionIdxName + " is not a uint64_t literal."s);
        return;
      }

      std::string directionIdxName = j["directionIdx"].get<std::string>();
      if(!uintDict.contains(directionIdxName)) {
        SysError::setError("BulletCreatorFtry " + name + " config for directionIdx: "s + directionIdxName + " is not a uint64_t literal."s);
        return;
      }

      std::string timeEventGeneratorName = j["teg"].get<std::string>();
      if(!tegStore.contains("TimeEventGenerator."s + timeEventGeneratorName)) {
        SysError::setError("BulletCreatorFtry config for timeEventGenerator: "s + timeEventGeneratorName + " is not an timeEventGenerator name."s);
        return;
      }

      std::string timeName = j["time"].get<std::string>();
      if(!uintDict.contains(timeName)) {
        SysError::setError("BulletCreatorFtry config for time: "s + timeName + " is not a time name."s);
        return;
      }

      std::string cTimeName = j["contextTime"].get<std::string>();
      if(!cTimeRsrc.contains("ContextTime."s + cTimeName)) {
        SysError::setError("BulletCreatorFtry config for contextTime: "s + timeName + " is not a context time name."s);
        return;
      }

      std::string ticketIdName = j["ticketId"].get<std::string>();
      if(!uintDict.contains(ticketIdName)) {
        SysError::setError("BulletCreatorFtry config for ticketId: "s + ticketIdName + " is not a ticketId name."s);
        return;
      }

      if (j["graphicList"].empty()){
        SysError::setError("BulletCreatorFtry " + name + "  config for graphicList is empty"s);
        return;
      }

      if (j["behaviorList"].empty()){
        SysError::setError("BulletCreatorFtry  " + name + " config for behaviorList is empty"s);
        return;
      }

      auto bc = bulletCreatorStore.get("BulletCreator."s + name);

      auto speed = doubleDict.get(speedName);
      auto speedIdx = uintDict.get(speedIdxName);
      bc->setSpeed(speed, speedIdx);

      auto gid = uintDict.get(gidName);
      auto gidIdx = uintDict.get(gidIdxName);
      bc->setGid(gid, gidIdx);

      auto rotation = doubleDict.get(rotationName);
      auto rotationIdx = uintDict.get(rotationIdxName);
      bc->setRotation(rotation, rotationIdx);

      auto scale = doubleDict.get(scaleName);
      auto scaleIdx = uintDict.get(scaleIdxName);
      bc->setScale(scale, scaleIdx);

      auto positionIdx = uintDict.get(positionIdxName);
      bc->setPositionId(positionIdx);

      auto directionIdx = uintDict.get(directionIdxName);
      bc->setDirectionId(directionIdx);

      auto cTime = cTimeRsrc.get("ContextTime."s + cTimeName);
      bc->setContextTime(cTime);

      std::vector<std::pair<std::string, uint64_t>> graphicList;
      auto graphicListsCfg = j["graphicList"];
      for (auto& gListCfg : graphicListsCfg.items()) {
        if (!gListCfg.value().is_string()) {
          SysError::setError("BulletCreatorFtry " + name + " config key for graphic lists must be a string but is "s + gListCfg.value().type_name());
          return;
        }
        auto tid = uintDict.get(gListCfg.value().get<std::string>());
        graphicList.emplace_back(gListCfg.key(), tid);
      }
      bc->setGraphicList(graphicList);

      std::vector<std::pair<std::string, uint64_t>> behaviorList;
      auto behaviorListsCfg = j["behaviorList"];
      for (auto& bListCfg : behaviorListsCfg.items()) {
        if (!bListCfg.value().is_string()) {
          SysError::setError("behaviorListsCfg " + name + " config key for graphic lists must be a string but is "s + bListCfg.value().type_name());
          return;
        }
        auto tid = uintDict.get(bListCfg.value().get<std::string>());
        behaviorList.emplace_back(bListCfg.key(), tid);
      }
      bc->setBehaviorList(behaviorList);

      auto teg = tegStore.get("TimeEventGenerator."s + timeEventGeneratorName);
      auto time = uintDict.get(timeName);
      auto ticketId = uintDict.get(ticketIdName);
      bc->setTeg(teg, time, ticketId);

    } else {
      SysError::setError("BulletCreatorFtry config for "s + name + " not found."s);
    }

  }

private:
  RsrcStore<nlohmann::json> &configStore = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<BulletCreator> &bulletCreatorStore = RsrcStore<BulletCreator>::getInstance();
  RsrcDictionary<uint64_t> &uintDict = RsrcDictionary<uint64_t>::getInstance();
  RsrcStore<ContextTime>& cTimeRsrc = RsrcStore<ContextTime>::getInstance();
  RsrcDictionary<double> &doubleDict = RsrcDictionary<double>::getInstance();
  RsrcStore<TimeEventGenerator> &tegStore = RsrcStore<TimeEventGenerator>::getInstance();

};

}  // namespace zbe

#endif  // ZBE_CREATORS_BULLETCREATOR_H_
