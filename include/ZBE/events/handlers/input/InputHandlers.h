/**
 * Copyright 2012 Batis Degryll Ludo
 * @file InputHandlers.h
 * @since 2017-07-05
 * @date 2017-07-05
 * @author Batis Degrill Ludo
 * @brief Handler that stores input value to a Value<double>
 */

#ifndef ZBE_EVENTS_HANDLERS_INPUTHANDLERS_H_
#define ZBE_EVENTS_HANDLERS_INPUTHANDLERS_H_

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <nlohmann/json.hpp>

#include "ZBE/factories/Factory.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/Ticket.h"

#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/core/events/generators/InputEventGenerator.h"
#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/io/Input.h"

#include "ZBE/core/system/system.h"
#include "ZBE/core/system/SysError.h"
#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/JSON/JSONFactory.h"

namespace zbe {

template<unsigned dim>
class AddVelIH : public InputHandler {
public:

  AddVelIH(std::shared_ptr<MAvatar<Vector<dim>, Vector<dim>, Vector<dim>>> avt) : avt(avt) {}

  void run(uint32_t, float status) override {
    double intiMult = -1.0;
    if ((status < 0.5 && !down) || (status >= 0.5 && down)) {
      intiMult = 1.0;
    }
    auto vOri = AvtUtil::get<3, Vector<dim> >(avt);
    auto vVel = AvtUtil::get<2, Vector<dim> >(avt);
    auto vVelSrc = AvtUtil::get<1, Vector<dim> >(avt);

    Vector<dim> ori = vOri->get();
    Vector<dim> orinorm =  normalize(ori);
    //double rads = arcsin(.x);
    double v11 = orinorm.x;
    double v12 = orinorm.y;
    double v21 = -orinorm.y;
    double v22 = orinorm.x;

    Vector<dim> vel = vVel->get();
    Vector<dim> velSrc = vVelSrc->get();

    Vector<dim> velSrcRotated{velSrc.x*v11 + velSrc.y*v12, velSrc.x*v21 + velSrc.y*v22};
    vel = vel + velSrcRotated * multiplier * intiMult;
    if(vel.getModule() < tolerance) {
      velSrc.setZeros();
    }
    vVel->set(vel);
  }

  void setConfig(bool down, double multiplier, double tolerance) {
    this->down = down;
    this->multiplier = multiplier;
    this->tolerance = tolerance;
  }

private:
  std::shared_ptr<MAvatar<Vector<dim>, Vector<dim>, Vector<dim>>> avt{};
  bool down{};
  double multiplier{};
  double tolerance{};
};

template<unsigned dim>
class AddVelIHBldr : public Funct<void, std::shared_ptr<Entity>> {
public:
  void operator()(std::shared_ptr<Entity> ent) override {
    auto avt = std::make_shared<MBaseAvatar<Vector<dim>, Vector<dim>, Vector<dim>>>();
    avt->setupEntity(ent, idxs);
    std::shared_ptr<AddVelIH<dim>> ih = std::make_shared<AddVelIH<dim>>(avt);
    ih->setConfig(down, multiplier, tolerance);

    ieg->addHandler(key, ih);
  }

  void setupIdx(std::array<uint64_t, 3> idxs) {
    this->idxs = idxs;
  }

  void setConfig(bool down, double multiplier, double tolerance, ZBE_K key) {
    this->down = down;
    this->multiplier = multiplier;
    this->tolerance = tolerance;
    this->key = key;
  }

  void setIEG(std::shared_ptr<InputEventGenerator> ieg) {
    this->ieg = ieg;
  }

private:
  std::array<uint64_t, 3> idxs{};
  bool down{};
  double multiplier{};
  double tolerance{};
  std::shared_ptr<InputEventGenerator> ieg{};
  ZBE_K key;
};



template<unsigned dim>
class AddVelIHBldrFtry : public Factory {

  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    std::shared_ptr<AddVelIHBldr<dim>> avihb = std::make_shared<AddVelIHBldr<dim>>();
    mainRsrc.insert(zbe::factories::functionName_ + name, avihb);
    specificRsrc.insert("AddVelIHBldr."s + name, avihb);
  }

  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<nlohmann::json> cfg = configRsrc.get(cfgId);

    if(!cfg) {
      SysError::setError("Add2DVelIHBldrFtry config for "s + name + " not found."s);
      return;
    }

    auto j = *cfg;

    auto avihb = specificRsrc.get("AddVelIHBldr."s + name);

    auto orientation2DIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "orientation2DIdx"s, "Add2DVelIHBldrFtry"s);
    if(!orientation2DIdx) {
      SysError::setError("Add2DVelIHBldrFtry config for orientation2DIdx is invalid"s);
      return;
    }

    auto velocity2DIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "velocity2DIdx"s, "Add2DVelIHBldrFtry"s);
    if(!velocity2DIdx) {
      SysError::setError("Add2DVelIHBldrFtry config for velocity2DIdx is invalid"s);
      return;
    }

    auto velocity2DsrcIds = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "velocity2DsrcIds"s, "Add2DVelIHBldrFtry"s);
    if(!velocity2DsrcIds) {
      SysError::setError("Add2DVelIHBldrFtry config for velocity2DsrcIds is invalid"s);
      return;
    }

    auto ieg = JSONFactory::loadParamCfgStoreP<InputEventGenerator>(iegStore, j, "InputEventGenerator"s, "inputEventGenerator"s, "Add2DVelIHBldrFtry"s);
    if(!ieg) {
      SysError::setError("Add2DVelIHBldrFtry config for inputEventGenerator is invalid"s);
      return;
    }

    auto key = JSONFactory::loadParamCfgDict<ZBE_K>(keyStore, j, "key"s, "Add2DVelIHBldrFtry"s);
    if(!key) {
      SysError::setError("Add2DVelIHBldrFtry config for key is invalid"s);
      return;
    }

    auto multiplier = JSONFactory::loadParamCfgDict<double>(doubleDict, j, "multiplier"s, "Add2DVelIHBldrFtry"s);
    if(!multiplier) {
      SysError::setError("Add2DVelIHBldrFtry config for multiplier is invalid"s);
      return;
    }

    auto tolerance = JSONFactory::loadParamCfgDict<double>(doubleDict, j, "tolerance"s, "Add2DVelIHBldrFtry"s);
    if(!tolerance) {
      SysError::setError("Add2DVelIHBldrFtry config for tolerance is invalid"s);
      return;
    }

    if(!j.contains("down")) {
      SysError::setError("Add2DVelIHBldrFtry config for down is invalid"s);
    }
    auto down = j["down"];

    if(!down.is_boolean()) {
      SysError::setError("Add2DVelIHBldrFtry config for down  is invalid"s);
      return;
    }

    auto isdown = down.get<bool>();
    std::array<uint64_t, 3> idx{*orientation2DIdx, *velocity2DIdx, *velocity2DsrcIds};

    avihb->setupIdx(idx);
    avihb->setConfig(isdown, *multiplier, *tolerance, *key);
    avihb->setIEG(*ieg);

  }

private:
  using FunctionType = Funct<void, std::shared_ptr<Entity>>;
  RsrcStore<nlohmann::json> &configRsrc      = RsrcStore<nlohmann::json>::getInstance();
  RsrcDictionary<uint64_t>& uintDict         = RsrcDictionary<uint64_t>::getInstance();
  RsrcDictionary<double>& doubleDict         = RsrcDictionary<double>::getInstance();
  RsrcStore<AddVelIHBldr<dim>>& specificRsrc = RsrcStore<AddVelIHBldr<dim>>::getInstance();
  RsrcStore<FunctionType>& mainRsrc          = RsrcStore<FunctionType>::getInstance();
  RsrcStore<InputHandler>& ihRsrc            = RsrcStore<InputHandler>::getInstance();
  RsrcStore<InputEventGenerator>& iegStore   = RsrcStore<InputEventGenerator>::getInstance();
  RsrcDictionary<ZBE_K>& keyStore            = RsrcDictionary<ZBE_K>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_INPUTHANDLERS_H_
