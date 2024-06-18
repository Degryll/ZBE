/**
 * Copyright 2022 Batis Degryll Ludo
 * @file ZandBokzBuilders.h
 * @since 2022-12-06
 * @date 2022-12-06
 * @author Ludo Degryll Batis
 * @brief ZandBokz Behaviors
 */

 #ifndef ZANDBOKZ_ZANDBOKZBUILDERS_H_
 #define ZANDBOKZ_ZANDBOKZBUILDERS_H__

#include <cstdint>
#include <memory>

#include <string>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/tools.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/system/system.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/JSON/JSONFactory.h"

namespace zandbokz {

class Triangle3Dto2DCacheBldr : public zbe::Funct<void, std::shared_ptr<zbe::Entity>> {
public:
 void operator()(std::shared_ptr<zbe::Entity> entity) {
    float baseScale = static_cast<float>(entity->getDouble(sizeIdx)->get());
    // Calculate plane
    glm::mat4 mat(1.0);
    glm::vec3 glPos(0.0, 0.0, 0.0);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glPos);
    glm::mat4 m     = glm::scale(glm::mat4(1.0f), glm::vec3(baseScale)) * translate;
    glm::vec3 a = m * glm::vec4(baseT.a.x, baseT.a.y, baseT.a.z, 1.0);
    glm::vec3 b = m * glm::vec4(baseT.b.x, baseT.b.y, baseT.b.z, 1.0);
    glm::vec3 c = m * glm::vec4(baseT.c.x, baseT.c.y, baseT.c.z, 1.0);

    zbe::Point3D pa{a.x, a.y, a.z};
    zbe::Point3D pb{b.x, b.y, b.z};
    zbe::Point3D pc{c.x, c.y, c.z};

    zbe::Point3D origin = pa;
    zbe::Vector3D e1 = (pb - origin).normalize();
    zbe::Vector3D aux = (pc - origin);
    zbe::Vector3D norm = cross(aux, e1);
    zbe::Vector3D e2 = cross(e1, norm).normalize();

    auto aaux = transformPointCoords(a, e1, e2, norm);
    auto baux = transformPointCoords(b, e1, e2, norm);
    auto caux = transformPointCoords(c, e1, e2, norm);

    entity->setVector2D(aIdx, aaux);
    entity->setVector2D(bIdx, baux);
    entity->setVector2D(cIdx, caux);

    auto vaaux = aaux->get();
    auto vbaux = baux->get();
    auto vcaux = caux->get();
  }

  std::shared_ptr<zbe::Value<zbe::Vector2D>> transformPointCoords(glm::vec3 p, zbe::Vector3D bx, zbe::Vector3D by, zbe::Vector3D bz) {

    auto diff = zbe::Vector3D{p.x, p.y, p.z};

    double x = diff * zbe::Vector3D{bx.x, bx.y, bx.z};
    double y = diff * zbe::Vector3D{by.x, by.y, by.z};

    zbe::Vector2D newPos2D{x, y};
    return std::make_shared<zbe::SimpleValue<zbe::Vector2D>>(newPos2D);
  }

  void setIdxs(uint64_t aIdx, uint64_t bIdx, uint64_t cIdx, uint64_t sizeIdx) {
    this->aIdx = aIdx;
    this->bIdx = bIdx;
    this->cIdx = cIdx;
    this->sizeIdx = sizeIdx;
  }

  void setBaseTriangle(zbe::Triangle3D baseT) {
    this->baseT = baseT;
  }

private:
  uint64_t aIdx {};
  uint64_t bIdx {};
  uint64_t cIdx {};
  uint64_t sizeIdx {};
  zbe::Triangle3D baseT{};
};

class Triangle3Dto2DCacheBldrFtry : public zbe::Factory {
  void create(std::string name, uint64_t) {
    using namespace std::string_literals;
    std::shared_ptr<Triangle3Dto2DCacheBldr> t3dt2dcb = std::make_shared<Triangle3Dto2DCacheBldr>();
    mainRsrc.insert(zbe::factories::functionName_ + name, t3dt2dcb);
    specificRsrc.insert("Triangle3Dto2DCacheBldr."s + name, t3dt2dcb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<nlohmann::json> cfg = configRsrc.get(cfgId);
    if(!cfg) {
      zbe::SysError::setError("Triangle3Dto2DCacheBldrFtry config for "s + name + " not found."s);
      return;
    }
    auto t3dt2dcb = specificRsrc.get("Triangle3Dto2DCacheBldr."s + name);
    auto j = *cfg;

    auto aIdx = zbe::JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "aIdx"s, "Triangle3Dto2DCacheBldrFtry"s);
    if(!aIdx) {
      return;
    }

    auto bIdx = zbe::JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "bIdx"s, "Triangle3Dto2DCacheBldrFtry"s);
    if(!bIdx) {
      return;
    }

    auto cIdx = zbe::JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "cIdx"s, "Triangle3Dto2DCacheBldrFtry"s);
    if(!cIdx) {
      return;
    }

    auto sizeIdx = zbe::JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "sizeIdx"s, "Triangle3Dto2DCacheBldrFtry"s);
    if(!sizeIdx) {
      return;
    }

    auto triangleList = zbe::JSONFactory::loadParamCfgStoreP<std::forward_list<zbe::Triangle3D>>(triangle3DListRsrc, j, "TriangleList"s, "triangle"s, "Triangle3Dto2DCacheBldrFtry"s);
    if(!triangleList) {
      zbe::SysError::setError("Triangle3Dto2DCacheBldrFtry config for contextTime is invalid"s);
      return;
    }

    t3dt2dcb->setIdxs(*aIdx, *bIdx, *cIdx, *sizeIdx);
    t3dt2dcb->setBaseTriangle((*triangleList)->front());
  }
private:
  zbe::RsrcStore<nlohmann::json>& configRsrc = zbe::RsrcStore<nlohmann::json>::getInstance();
  zbe::RsrcStore<zbe::Funct<void, std::shared_ptr<zbe::Entity>>>& mainRsrc = zbe::RsrcStore<zbe::Funct<void, std::shared_ptr<zbe::Entity>>>::getInstance();
  zbe::RsrcStore<Triangle3Dto2DCacheBldr>& specificRsrc = zbe::RsrcStore<Triangle3Dto2DCacheBldr>::getInstance();
  zbe::RsrcDictionary<uint64_t>& uintDict = zbe::RsrcDictionary<uint64_t>::getInstance();
  zbe::RsrcStore<std::forward_list<zbe::Triangle3D>> &triangle3DListRsrc = zbe::RsrcStore<std::forward_list<zbe::Triangle3D>>::getInstance();
};

} // namespace zandbokz

#endif  // ZANDBOKZ_ZANDBOKZBUILDERS_H__
