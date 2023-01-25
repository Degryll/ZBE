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
#include <forward_list>
// TODO: hay que sacar de aqui los avatares con dependencias de terceros.
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// ----

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/math/math.h"

#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"

#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"

#include "ZBE/core/events/shapes.h"
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

class DerivedCosVelAvt : public MAvatar<Vector3D, Vector3D>, AvatarImp {
public:

  /** \brief
   */
   void setupEntity(std::shared_ptr<Entity> entity, uint64_t positionidx) {
     AvatarImp::setupEntity(entity);
     _Avatar<1, Vector3D>::setup(&getPosition, &setPosition, (void*)this);
     _Avatar<2, Vector3D>::setup(&getVelocity, &setVelocity, (void*)this);
     position = entity->getVector3D(positionidx);
     cTime = entity->getContextTime();
   }

   static std::shared_ptr<Value<Vector3D> > getPosition(void *instance) {
     return ((DerivedCosVelAvt*)instance)->position;
   }

   static std::shared_ptr<Value<Vector3D> > getVelocity(void *instance) {
     auto dcv = (DerivedCosVelAvt*)instance;
     auto& position = dcv->position;
     auto p = position->get();
     auto time = dcv->cTime->getTotalTime();
     float div = (time / (float)dcv->period) * TAU;
     float cosine = cos(div);
     float newVal = ((cosine + 1.0) / 2.0) * (dcv->max - dcv->min) + dcv->min;
     Vector3D v{0.0, 0.0, 0.0};
     v[dcv->component] = newVal / time;
     auto r = std::make_shared<SimpleValue<Vector3D> >();
     r->set(v);
     return r;
   }

   static void setPosition(void *instance, Vector3D position) {
     auto& _position = ((DerivedCosVelAvt*)instance)->position;
     auto p = _position->get();
     _position->set(position);
   }

   static void setVelocity(void*, Vector3D) {
     assert(false);
   }

   std::shared_ptr<Entity> getEntity() {
     assert(false);
   }

   void setRange(float min, float max) {this->min = min; this->max = max;}

   void setPeriod(int64_t period) {this->period = period;}

   void setComponent(int64_t component) {
     assert(component>=0 && component<=2);
     this->component = component;
   }

private:
  std::shared_ptr<Value<Vector3D> > position;
  std::shared_ptr<ContextTime> cTime;

  float min;
  float max;
  int64_t period;
  int64_t component;
};

class MovingSphereAvt : public SAvatar<MovingSphere>, public AvatarImp {
public:
  void setupEntity(std::shared_ptr<Entity> entity, uint64_t positionidx, uint64_t velocityidx, uint64_t radiusidx) {
    AvatarImp::setupEntity(entity);
    _Avatar<1, MovingSphere>::setup(&getSphere, &setSphere, (void*)this);
    position = entity->getVector3D(positionidx);
    velocity = entity->getVector3D(velocityidx);
    radius = entity->getFloat(radiusidx);
    cTime = entity->getContextTime();
  }

  static std::shared_ptr<Value<MovingSphere> > getSphere(void *instance) {
    auto  msa = (MovingSphereAvt*)instance;
    auto& position = msa->position;
    auto& velocity = msa->velocity;
    auto p = position->get();
    auto v = velocity->get();
    auto r = msa->radius->get();
    auto time = msa->cTime->getTotalTime();
    Sphere s(p.toPoint(), r);
    MovingSphere ms{s, v};
    auto out = std::make_shared<SimpleValue<MovingSphere> >();
    out->set(ms);
    return out;
  }

  static void setSphere(void *instance, MovingSphere position) {
    assert(false);
  }

  std::shared_ptr<Entity> getEntity() {
    assert(false);
  }

private:
 std::shared_ptr<Value<Vector3D> > position;
 std::shared_ptr<Value<Vector3D> > velocity;
 std::shared_ptr<Value<float> > radius;
 std::shared_ptr<ContextTime> cTime;
};

class MovingSphereAvtShapeBldr  : public Funct<std::shared_ptr<SAvatar<MovingSphere>>, std::shared_ptr<Entity>> {
public:
  using AvtBaseType = SAvatar<MovingSphere>;
  std::shared_ptr<SAvatar<MovingSphere>> operator()(std::shared_ptr<Entity> ent) {
    std::shared_ptr<MovingSphereAvt> avt = std::make_shared<MovingSphereAvt>();
    avt->setupEntity(ent, positionidx, velocityidx, radiusidx);
    return avt;
  }

  void setIdxs(uint64_t positionidx, uint64_t velocityidx, uint64_t radiusidx) {
      this->positionidx = positionidx;
      this->velocityidx = velocityidx;
      this->radiusidx = radiusidx;
  }

private:
 uint64_t positionidx;
 uint64_t velocityidx;
 uint64_t radiusidx;
};

class MovingSphereAvtShapeBldrFtry : public Factory {
// This class where c&p from DerivedPosMovingSphereAvtBldrFtry removing list managment
public:
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<MovingSphereAvtShapeBldr> msasb = std::make_shared<MovingSphereAvtShapeBldr>();
    mainRsrc.insert(zbe::factories::functionName_ + name, msasb);
    specificRsrc.insert("MovingSphereAvtShapeBldr."s + name, msasb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto msasb = specificRsrc.get("MovingSphereAvtShapeBldr."s + name);

      auto positionIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "positionIdx"s, "MovingSphereAvtShapeBldrFtry"s);
      if(!positionIdx) {
        return;
      }
      auto velocityIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "velocityIdx"s, "MovingSphereAvtShapeBldrFtry"s);
      if(!velocityIdx) {
        return;
      }
      auto radiusidx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "radiusIdx"s, "MovingSphereAvtShapeBldrFtry"s);
      if(!radiusidx) {
        return;
      }
      msasb->setIdxs(*positionIdx, *velocityIdx, *radiusidx);

    } else {
      SysError::setError("MovingSphereAvtShapeBldrFtry config for "s + name + " not found."s);
    }
  }

private:
  using FunctionType = Funct<std::shared_ptr<SAvatar<MovingSphere>>, std::shared_ptr<Entity>>;
  using ListType = TicketedForwardList<MovingSphereAvtShapeBldr::AvtBaseType>;
  RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc                          = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<MovingSphereAvtShapeBldr>& specificRsrc    = RsrcStore<MovingSphereAvtShapeBldr>::getInstance();
  RsrcStore<FunctionType>& mainRsrc = RsrcStore<FunctionType>::getInstance();
};

class MovingSphereAvtBldr : public Funct<std::shared_ptr<SAvatar<MovingSphere>>, std::shared_ptr<Entity>> {
public:
  using AvtBaseType = SAvatar<MovingSphere>;
  std::shared_ptr<SAvatar<MovingSphere>> operator()(std::shared_ptr<Entity> ent) {
    std::shared_ptr<MovingSphereAvt> avt = std::make_shared<MovingSphereAvt>();
    avt->setupEntity(ent, positionidx, velocityidx, radiusidx);
    for(auto indexNList : indexNLists) {
      auto ticket = indexNList.second->push_front(avt);
      ent->addTicket(indexNList.first, ticket);
    }
  }

  void setIdxs(uint64_t positionidx, uint64_t velocityidx, uint64_t radiusidx) {
      this->positionidx = positionidx;
      this->velocityidx = velocityidx;
      this->radiusidx = radiusidx;
  }

  void addIndexNlist(uint64_t index, std::shared_ptr<TicketedForwardList<AvtBaseType>> list) {
    indexNLists.push_back({index, list});
  }

private:
 uint64_t positionidx;
 uint64_t velocityidx;
 uint64_t radiusidx;
 std::vector<std::pair<uint64_t, std::shared_ptr<TicketedForwardList<AvtBaseType>>>> indexNLists;
};

class MovingSphereAvtBldrFtry : public Factory {
public:
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<MovingSphereAvtBldr> msab = std::make_shared<MovingSphereAvtBldr>();
    mainRsrc.insert(zbe::factories::functionName_ + name, msab);
    specificRsrc.insert("MovingSphereAvtBldr."s + name, msab);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto msab = specificRsrc.get("MovingSphereAvtBldr."s + name);

      auto positionIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "positionIdx"s, "MovingSphereAvtBldrFtry"s);
      if(!positionIdx) {
        return;
      }
      auto velocityIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "velocityIdx"s, "MovingSphereAvtBldrFtry"s);
      if(!velocityIdx) {
        return;
      }
      auto radiusidx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "radiusIdx"s, "MovingSphereAvtBldrFtry"s);
      if(!radiusidx) {
        return;
      }
      msab->setIdxs(*positionIdx, *velocityIdx, *radiusidx);

    } else {
      SysError::setError("MovingSphereAvtBldrFtry config for "s + name + " not found."s);
    }
  }

private:
  using FunctionType = Funct<std::shared_ptr<SAvatar<MovingSphere>>, std::shared_ptr<Entity>>;
  using ListType = TicketedForwardList<MovingSphereAvtBldr::AvtBaseType>;
  RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc                          = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<MovingSphereAvtBldr>& specificRsrc    = RsrcStore<MovingSphereAvtBldr>::getInstance();
  RsrcStore<FunctionType>& mainRsrc = RsrcStore<FunctionType>::getInstance();
};

class MovingTriangle3DRscAvt : public SAvatar<MovingTriangle3D>, public AvatarImp {
public:

  void setupEntity(std::shared_ptr<Entity> entity, uint64_t velocityIdx, uint64_t orientationIdx, uint64_t positionIdx, uint64_t radsIdx, uint64_t sizeIdx, uint64_t e1Idx, uint64_t e2Idx) {
    AvatarImp::setupEntity(entity);
    _Avatar<1, MovingTriangle3D>::setup(&getTriangle, &setTriangle, (void*)this);
    orientation = entity->getVector3D(orientationIdx);
    velocity = entity->getVector3D(velocityIdx);
    position = entity->getVector3D(positionIdx);
    rads = entity->getDouble(radsIdx);
    size = entity->getDouble(sizeIdx);
    cTime = entity->getContextTime();
    e1 = entity->getVector3D(e1Idx);
    e2 = entity->getVector3D(e2Idx);
  }

  static std::shared_ptr<Value<MovingTriangle3D> > getTriangle(void *instance) {
    auto  mtra = (MovingTriangle3DRscAvt*)instance;
    auto& vel = mtra->velocity->get();
    auto& ori = mtra->orientation->get();
    auto& pos = mtra->position->get();
    float angle = (float)mtra->rads->get();
    float baseScale = (float)mtra->size->get();

    glm::vec3 glPos(pos.x, pos.y, pos.z);
    glm::vec3 glDir(ori.x, ori.y, ori.z);

    glm::mat4 mat(1.0);

    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glPos);
    glm::mat4 rotate    = glm::rotate(   glm::mat4(1.0f), angle, glDir);
    glm::mat4 scale     = glm::scale(    glm::mat4(1.0f), glm::vec3(baseScale));
    glm::mat4 m = translate * scale * rotate;
    glm::vec3 a = m * glm::vec4(mtra->baseT.a.x, mtra->baseT.a.y, mtra->baseT.a.z, 1.0);
    glm::vec3 b = m * glm::vec4(mtra->baseT.b.x, mtra->baseT.b.y, mtra->baseT.b.z, 1.0);
    glm::vec3 c = m * glm::vec4(mtra->baseT.c.x, mtra->baseT.c.y, mtra->baseT.c.z, 1.0);

    Point3D pa{a.x, a.y, a.z};
    Point3D pb{b.x, b.y, b.z};
    Point3D pc{c.x, c.y, c.z};

    Triangle3D t{pa, pb, pc};
    MovingTriangle3D mt{t, vel};
    auto out = std::make_shared<SimpleValue<MovingTriangle3D> >();
    out->set(mt);
    Vector3D e1 = (pb - pa).normalize();
    Vector3D aux = (pc - pa).normalize();
    Vector3D norm = cross(e1, aux);
    Vector3D e2 = cross(norm, e1);
    
    mtra->e1->set(e1);
    mtra->e2->set(e2);
    return out;
  }

  static void setTriangle(void*, MovingTriangle3D ) {
    assert(false);
  }

  std::shared_ptr<Entity> getEntity() {
    assert(false);
  }

  void setBaseTriangle(Triangle3D baseT) {
    this->baseT = baseT;
  }

private:
 std::shared_ptr<Value<Vector3D> > position;
 std::shared_ptr<Value<Vector3D> > velocity;
 std::shared_ptr<Value<Vector3D> > orientation;
 std::shared_ptr<Value<double> >   rads;
 std::shared_ptr<Value<double> >   size;
 std::shared_ptr<Value<Vector3D> > e1;
 std::shared_ptr<Value<Vector3D> > e2;

 Triangle3D baseT;
 std::shared_ptr<ContextTime> cTime;
};

class MovingTriangle3DRscAvtShapeBldr  : public Funct<std::shared_ptr<SAvatar<MovingTriangle3D>>, std::shared_ptr<Entity>> {
public:
  using AvtBaseType = SAvatar<MovingSphere>;
  std::shared_ptr<SAvatar<MovingTriangle3D>> operator()(std::shared_ptr<Entity> ent) {
    std::shared_ptr<MovingTriangle3DRscAvt> avt = std::make_shared<MovingTriangle3DRscAvt>();
    avt->setupEntity(ent, velocityIdx, orientationIdx, positionIdx, radsIdx, sizeIdx, e1Idx, e2Idx);
    avt->setBaseTriangle(baseT);
    return avt;
  }

  void setIdxs(uint64_t velocityIdx, uint64_t orientationIdx, uint64_t positionIdx, uint64_t radsIdx, uint64_t sizeIdx, uint64_t e1Idx, uint64_t e2Idx) {
      this->velocityIdx = velocityIdx;
      this->orientationIdx = orientationIdx;
      this->positionIdx = positionIdx;
      this->radsIdx = radsIdx;
      this->sizeIdx = sizeIdx;
      this->e1Idx = e1Idx;
      this->e2Idx = e2Idx;
  }

  void setBaseTriangle(Triangle3D baseT) {
    this->baseT = baseT;
  }

private:
  uint64_t velocityIdx;
  uint64_t orientationIdx;
  uint64_t positionIdx;
  uint64_t radsIdx;
  uint64_t sizeIdx;
  uint64_t e1Idx;
  uint64_t e2Idx;
  Triangle3D baseT;
};

class MovingTriangle3DRscAvtShapeBldrFtry : public Factory {
public:
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<MovingTriangle3DRscAvtShapeBldr> mt3rasb = std::make_shared<MovingTriangle3DRscAvtShapeBldr>();
    mainRsrc.insert(zbe::factories::functionName_ + name, mt3rasb);
    specificRsrc.insert("MovingTriangle3DRscAvtShapeBldr."s + name, mt3rasb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto mt3rasb = specificRsrc.get("MovingTriangle3DRscAvtShapeBldr."s + name);

      auto velocityIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "velocityIdx"s, "MovingTriangle3DRscAvtShapeBldrFtry"s);
      if(!velocityIdx) {
        return;
      }
      auto orientationIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "orientationIdx"s, "MovingTriangle3DRscAvtShapeBldrFtry"s);
      if(!orientationIdx) {
        return;
      }
      auto positionIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "positionIdx"s, "MovingTriangle3DRscAvtShapeBldrFtry"s);
      if(!positionIdx) {
        return;
      }
      auto radsIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "radsIdx"s, "MovingTriangle3DRscAvtShapeBldrFtry"s);
      if(!radsIdx) {
        return;
      }
      auto sizeIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "sizeIdx"s, "MovingTriangle3DRscAvtShapeBldrFtry"s);
      if(!sizeIdx) {
        return;
      }
      auto e1Idx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "e1Idx"s, "MovingTriangle3DRscAvtShapeBldrFtry"s);
      if(!e1Idx) {
        return;
      }
      auto e2Idx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "e2Idx"s, "MovingTriangle3DRscAvtShapeBldrFtry"s);
      if(!e2Idx) {
        return;
      }

      auto triangleList = JSONFactory::loadParamCfgStoreP<std::forward_list<Triangle3D>>(triangle3DListRsrc, j, "TriangleList"s, "triangle"s, "MovingTriangle3DRscAvtShapeBldrFtry"s);
      if(!triangleList) {
        SysError::setError("EntityTimerBldrFtry config for contextTime is invalid"s);
        return;
      }

      mt3rasb->setIdxs(*velocityIdx, *orientationIdx, *positionIdx, *radsIdx, *sizeIdx, *e1Idx, *e2Idx);
      mt3rasb->setBaseTriangle((*triangleList)->front());

    } else {
      SysError::setError("MovingTriangle3DRscAvtShapeBldrFtry config for "s + name + " not found."s);
    }
  }

private:
  using FunctionType = Funct<std::shared_ptr<SAvatar<MovingTriangle3D>>, std::shared_ptr<Entity>>;
  using ListType = TicketedForwardList<MovingTriangle3DRscAvtShapeBldr::AvtBaseType>;
  RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc                          = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<MovingTriangle3DRscAvtShapeBldr>& specificRsrc    = RsrcStore<MovingTriangle3DRscAvtShapeBldr>::getInstance();
  RsrcStore<FunctionType>& mainRsrc = RsrcStore<FunctionType>::getInstance();
  RsrcStore<std::forward_list<Triangle3D>> &triangle3DListRsrc = RsrcStore<std::forward_list<Triangle3D>>::getInstance();
};

// TODO shape builders, factorias y demas pestes

class MovingTriangle3DAvt : public SAvatar<MovingTriangle3D>, public AvatarImp {
public:
  void setupEntity(std::shared_ptr<Entity> entity, uint64_t positionAidx, uint64_t positionBidx, uint64_t positionCidx, uint64_t velocityidx) {
    AvatarImp::setupEntity(entity);
    _Avatar<1, MovingTriangle3D>::setup(&getTriangle, &setTriangle, (void*)this);
    positionA = entity->getVector3D(positionAidx);
    positionB = entity->getVector3D(positionBidx);
    positionC = entity->getVector3D(positionCidx);
    velocity = entity->getVector3D(velocityidx);
    cTime = entity->getContextTime();
  }

  static std::shared_ptr<Value<MovingTriangle3D> > getTriangle(void *instance) {
    auto  mta = (MovingTriangle3DAvt*)instance;
    auto& positionA = mta->positionA;
    auto& positionB = mta->positionB;
    auto& positionC = mta->positionC;
    auto& velocity = mta->velocity;
    auto pA = positionA->get();
    auto pB = positionB->get();
    auto pC = positionC->get();
    auto v = velocity->get();
    //auto time = mta->cTime->getTotalTime();
    Triangle3D t{pA.toPoint(), pB.toPoint(), pC.toPoint()};
    MovingTriangle3D mt{t, v};
    auto out = std::make_shared<SimpleValue<MovingTriangle3D> >();
    out->set(mt);
    return out;
  }

  static void setTriangle(void*, MovingTriangle3D ) {
    assert(false);
  }

  std::shared_ptr<Entity> getEntity() {
    assert(false);
  }

private:
 std::shared_ptr<Value<Vector3D> > positionA;
 std::shared_ptr<Value<Vector3D> > positionB;
 std::shared_ptr<Value<Vector3D> > positionC;
 std::shared_ptr<Value<Vector3D> > velocity;
 std::shared_ptr<ContextTime> cTime;
};

class MovingTriangle3DAvtShapeBldr  : public Funct<std::shared_ptr<SAvatar<MovingTriangle3D>>, std::shared_ptr<Entity>> {
public:
  using AvtBaseType = SAvatar<MovingSphere>;
  std::shared_ptr<SAvatar<MovingTriangle3D>> operator()(std::shared_ptr<Entity> ent) {
    std::shared_ptr<MovingTriangle3DAvt> avt = std::make_shared<MovingTriangle3DAvt>();
    avt->setupEntity(ent, positionAidx, positionBidx, positionCidx, velocityidx);
    return avt;
  }

  void setIdxs(uint64_t positionAidx, uint64_t positionBidx, uint64_t positionCidx, uint64_t velocityidx) {
      this->positionAidx = positionAidx;
      this->positionBidx = positionBidx;
      this->positionCidx = positionCidx;
      this->velocityidx = velocityidx;
  }

private:
 uint64_t positionAidx;
 uint64_t positionBidx;
 uint64_t positionCidx;
 uint64_t velocityidx;
};

class MovingTriangle3DAvtShapeBldrFtry : public Factory {
public:
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<MovingTriangle3DAvtShapeBldr> msasb = std::make_shared<MovingTriangle3DAvtShapeBldr>();
    mainRsrc.insert(zbe::factories::functionName_ + name, msasb);
    specificRsrc.insert("MovingTriangle3DAvtShapeBldr."s + name, msasb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto msasb = specificRsrc.get("MovingTriangle3DAvtShapeBldr."s + name);

      auto positionAIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "positionAIdx"s, "MovingTriangle3DAvtShapeBldrFtry"s);
      if(!positionAIdx) {
        return;
      }
      auto positionBIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "positionBIdx"s, "MovingTriangle3DAvtShapeBldrFtry"s);
      if(!positionBIdx) {
        return;
      }
      auto positionCIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "positionCIdx"s, "MovingTriangle3DAvtShapeBldrFtry"s);
      if(!positionCIdx) {
        return;
      }

      auto velocityIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "velocityIdx"s, "MovingTriangle3DAvtShapeBldrFtry"s);
      if(!velocityIdx) {
        return;
      }
      msasb->setIdxs(*positionAIdx, *positionBIdx, *positionCIdx, *velocityIdx);

    } else {
      SysError::setError("MovingTriangle3DAvtShapeBldrFtry config for "s + name + " not found."s);
    }
  }

private:
  using FunctionType = Funct<std::shared_ptr<SAvatar<MovingTriangle3D>>, std::shared_ptr<Entity>>;
  using ListType = TicketedForwardList<MovingTriangle3DAvtShapeBldr::AvtBaseType>;
  RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc                          = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<MovingTriangle3DAvtShapeBldr>& specificRsrc    = RsrcStore<MovingTriangle3DAvtShapeBldr>::getInstance();
  RsrcStore<FunctionType>& mainRsrc = RsrcStore<FunctionType>::getInstance();
};

class MovingTriangle3DAvtBldr : public Funct<std::shared_ptr<SAvatar<MovingTriangle3D>>, std::shared_ptr<Entity>> {
public:
  using AvtBaseType = SAvatar<MovingTriangle3D>;
  std::shared_ptr<SAvatar<MovingTriangle3D>> operator()(std::shared_ptr<Entity> ent) {
    std::shared_ptr<MovingTriangle3DAvt> avt = std::make_shared<MovingTriangle3DAvt>();
    avt->setupEntity(ent, positionAidx, positionBidx, positionCidx, velocityidx);
    for(auto indexNList : indexNLists) {
      auto ticket = indexNList.second->push_front(avt);
      ent->addTicket(indexNList.first, ticket);
    }
  }

  void setIdxs(uint64_t positionAidx, uint64_t positionBidx, uint64_t positionCidx, uint64_t velocityidx) {
      this->positionAidx = positionAidx;
      this->positionBidx = positionBidx;
      this->positionCidx = positionCidx;
      this->velocityidx = velocityidx;
  }

  void addIndexNlist(uint64_t index, std::shared_ptr<TicketedForwardList<AvtBaseType>> list) {
    indexNLists.push_back({index, list});
  }

private:
 uint64_t positionAidx;
 uint64_t positionBidx;
 uint64_t positionCidx;
 uint64_t velocityidx;
 std::vector<std::pair<uint64_t, std::shared_ptr<TicketedForwardList<AvtBaseType>>>> indexNLists;
};

class MovingTriangle3DAvtBldrFtry : public Factory {
public:
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<MovingTriangle3DAvtBldr> msab = std::make_shared<MovingTriangle3DAvtBldr>();
    mainRsrc.insert(zbe::factories::functionName_ + name, msab);
    specificRsrc.insert("MovingTriangle3DAvtBldr."s + name, msab);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto mtab = specificRsrc.get("MovingTriangle3DAvtBldr."s + name);

      auto positionAIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "positionAIdx"s, "MovingTriangle3DAvtBldrFtry"s);
      if(!positionAIdx) {
        return;
      }

      auto positionBIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "positionBIdx"s, "MovingTriangle3DAvtBldrFtry"s);
      if(!positionBIdx) {
        return;
      }

      auto positionCIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "positionCIdx"s, "MovingTriangle3DAvtBldrFtry"s);
      if(!positionCIdx) {
        return;
      }

      auto velocityIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "velocityIdx"s, "MovingTriangle3DAvtBldrFtry"s);
      if(!velocityIdx) {
        return;
      }

      mtab->setIdxs(*positionAIdx, *positionBIdx, *positionCIdx, *velocityIdx);

    } else {
      SysError::setError("MovingTriangle3DAvtBldrFtry config for "s + name + " not found."s);
    }
  }

private:
  using FunctionType = Funct<std::shared_ptr<SAvatar<MovingTriangle3D>>, std::shared_ptr<Entity>>;
  using ListType = TicketedForwardList<MovingTriangle3DAvtBldr::AvtBaseType>;
  RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc                          = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<MovingTriangle3DAvtBldr>& specificRsrc    = RsrcStore<MovingTriangle3DAvtBldr>::getInstance();
  RsrcStore<FunctionType>& mainRsrc = RsrcStore<FunctionType>::getInstance();
};

class PosUpwardsTargetToPosUpwardsDirAvt : public MAvatar<Vector3D, Vector3D, Vector3D>, AvatarImp {
/*  TODO:
  La objetos que se pintan hacia donde se mueven tienen que tener un atributo mas asociado al movimiento: upwards.
  La castaña heredará el upwards de la camara y este se reflejará en los comportamientos de bote.
  El avatar de pintado de la castaña convertira esta direccion/upwards en lo que necesita el pintado.*/
public:

  /** \brief
   */
   void setupEntity(std::shared_ptr<Entity> entity, uint64_t positionidx, uint64_t targetidx, uint64_t upwardsidx) {
     AvatarImp::setupEntity(entity);
     _Avatar<1, Vector3D>::setup(&getPosition, &setPosition, (void*)this);
     _Avatar<2, Vector3D>::setup(&getDirection, &setDirection, (void*)this);
     _Avatar<3, Vector3D>::setup(&getUpwards, &setUpwards, (void*)this);
     position = entity->getVector3D(positionidx);
     target = entity->getVector3D(targetidx);
     upwards = entity->getVector3D(upwardsidx);
   }

   static std::shared_ptr<Value<Vector3D> > getPosition(void *instance) {
     return ((PosUpwardsTargetToPosUpwardsDirAvt*)instance)->position;
   }

   static std::shared_ptr<Value<Vector3D> > getDirection(void *instance) {
     auto& position = ((PosUpwardsTargetToPosUpwardsDirAvt*)instance)->position;
     auto& target =   ((PosUpwardsTargetToPosUpwardsDirAvt*)instance)->target;
     auto p = position->get();
     auto t = target->get();
     auto v = (t - p).normalize();// * s;
     auto r = std::make_shared<SimpleValue<Vector3D> >();
     r->set(v);
     return r;
   }

   static std::shared_ptr<Value<Vector3D> > getUpwards(void *instance) {
     return ((PosUpwardsTargetToPosUpwardsDirAvt*)instance)->upwards;
   }

   static void setPosition(void *instance, Vector3D position) {
     assert(false);
   }

   static void setDirection(void*, Vector3D) {
     assert(false);
   }

   static void setUpwards(void*, Vector3D) {
     assert(false);
   }

   std::shared_ptr<Entity> getEntity() {
     assert(false);
   }


private:
  std::shared_ptr<Value<Vector3D> > position;
  std::shared_ptr<Value<Vector3D> > target;
  std::shared_ptr<Value<Vector3D> > upwards;
};



class PosUpwardsTargetToPosUpwardsDirAvtFtry : public Factory {
  void create(std::string name, uint64_t){
    using namespace std::string_literals;

    auto puttpuda = std::make_shared<PosUpwardsTargetToPosUpwardsDirAvt>();
    puttpudaStore.insert("PosUpwardsTargetToPosUpwardsDirAvt."s + name, puttpuda);
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
        SysError::setError("PosUpwardsTargetToPosUpwardsDirAvtFtry " + name + " config for entity must be a string."s);
        return;
      }
      if (!j["lists"].is_object()) {
        SysError::setError("PosUpwardsTargetToPosUpwardsDirAvtFtry " + name + " config for lists must be an object. But is "s + j["lists"].type_name());
        return;
      }
      if (!j["positionIdx"].is_string()) {
        SysError::setError("PosUpwardsTargetToPosUpwardsDirAvtFtry " + name + " config for positionIdx must be a string."s);
        return;
      }
      if (!j["targetIdx"].is_string()) {
        SysError::setError("PosUpwardsTargetToPosUpwardsDirAvtFtry " + name + " config for targetIdx must be a string."s);
        return;
      }
      if (!j["upwardsIdx"].is_string()) {
        SysError::setError("PosUpwardsTargetToPosUpwardsDirAvtFtry " + name + " config for upwardsIdx must be a string."s);
        return;
      }

      std::string entityName = j["entity"].get<std::string>();
      if(!entityRsrc.contains("Entity."s + entityName)) {
        SysError::setError("PosUpwardsTargetToPosUpwardsDirAvtFtry config for entity: "s + entityName + " is not an entity name."s);
        return;
      }

      std::shared_ptr<Entity> ent = entityRsrc.get("Entity."s + entityName);

      std::string positionIdxName = j["positionIdx"].get<std::string>();
      if(!dict.contains(positionIdxName)) {
        SysError::setError("PosUpwardsTargetToPosUpwardsDirAvtFtry config for positionIdx: "s + positionIdxName + " is not an positionIdx name."s);
        return;
      }
      std::string targetIdxName = j["targetIdx"].get<std::string>();
      if(!dict.contains(targetIdxName)) {
        SysError::setError("PosUpwardsTargetToPosUpwardsDirAvtFtry config for targetIdx: "s + targetIdxName + " is not an targetIdx name."s);
        return;
      }
      std::string upwardsIdxName = j["upwardsIdx"].get<std::string>();
      if(!dict.contains(upwardsIdxName)) {
        SysError::setError("PosUpwardsTargetToPosUpwardsDirAvtFtry config for targetIdx: "s + targetIdxName + " is not an targetIdx name."s);
        return;
      }

      uint64_t positionIdx = dict.get(positionIdxName);
      uint64_t targetIdx = dict.get(targetIdxName);
      uint64_t upwardsIdx = dict.get(upwardsIdxName);

      std::shared_ptr<PosUpwardsTargetToPosUpwardsDirAvt> avt = puttpudaStore.get("PosUpwardsTargetToPosUpwardsDirAvt."s + name);

      avt->setupEntity(ent, positionIdx, targetIdx, upwardsIdx);

      auto listsCfg = j["lists"];
      for (auto& listCfg : listsCfg.items()) {
        if (!listCfg.value().is_string()) {
          SysError::setError("PosUpwardsTargetToPosUpwardsDirAvt " + name + " config for lists must contain strings. But is "s + listCfg.value().type_name());
          return;
        }
        auto list = listStore.get("List." + listCfg.key());
        auto ticket = list->push_front(avt);
        ent->addTicket(dict.get(listCfg.value().get<std::string>()), ticket);
      }
      puttpudaStore.remove("PosUpwardsTargetToPosUpwardsDirAvt."s + name);
    } else {
      SysError::setError("Avatar config for "s + name + " not found."s);
    }
  }

private:
  NameRsrcDictionary &dict                                                 = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc                                    = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<PosUpwardsTargetToPosUpwardsDirAvt>& puttpudaStore             = RsrcStore<PosUpwardsTargetToPosUpwardsDirAvt>::getInstance();
  RsrcStore<Entity>& entityRsrc                                            = RsrcStore<Entity>::getInstance();
  RsrcStore<TicketedForwardList<MAvatar<Vector3D, Vector3D, Vector3D> > >& listStore = RsrcStore<TicketedForwardList<MAvatar<Vector3D, Vector3D, Vector3D> > >::getInstance();
};


class PosUpwardsTargetToPosUpwardsDirAvtBldr : public Funct<void, std::shared_ptr<Entity>> {
public:
  using AvtBaseType = MAvatar<Vector3D, Vector3D, Vector3D>;
  void operator()(std::shared_ptr<Entity> ent) {
    std::shared_ptr<PosUpwardsTargetToPosUpwardsDirAvt> avt = std::make_shared<PosUpwardsTargetToPosUpwardsDirAvt>();

    avt->setupEntity(ent, positionidx, targetidx, upwardsidx);
    for(auto indexNList : indexNLists) {
      auto ticket = indexNList.second->push_front(avt);
      ent->addTicket(indexNList.first, ticket);
    }
  }

  void setIdxs(uint64_t positionidx, uint64_t targetidx, uint64_t upwardsidx) {
      this->positionidx = positionidx;
      this->targetidx = targetidx;
      this->upwardsidx = upwardsidx;
  }

  void addIndexNlist(uint64_t index, std::shared_ptr<TicketedForwardList<AvtBaseType>> list) {
    indexNLists.push_back({index, list});
  }

private:
  uint64_t positionidx;
  uint64_t targetidx;
  uint64_t upwardsidx;
  std::vector<std::pair<uint64_t, std::shared_ptr<TicketedForwardList<AvtBaseType>>>> indexNLists;
};

class PosUpwardsTargetToPosUpwardsDirAvtBldrFtry : public Factory {
public:
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<PosUpwardsTargetToPosUpwardsDirAvtBldr> put2pudab = std::make_shared<PosUpwardsTargetToPosUpwardsDirAvtBldr>();
    mainRsrc.insert(zbe::factories::functionName_ + name, put2pudab);
    specificRsrc.insert("PosUpwardsTargetToPosUpwardsDirAvtBldr."s + name, put2pudab);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto pttpdvb = specificRsrc.get("PosUpwardsTargetToPosUpwardsDirAvtBldr."s + name);

      auto positionIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "positionIdx"s, "PosUpwardsTargetToPosUpwardsDirAvtBldrFtry"s);
      if(!positionIdx) {
        return;
      }
      auto targetIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "targetIdx"s, "PosUpwardsTargetToPosUpwardsDirAvtBldrFtry"s);
      if(!targetIdx) {
        return;
      }
      auto upwardsIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "upwardsIdx"s, "PosUpwardsTargetToPosUpwardsDirAvtBldrFtry"s);
      if(!upwardsIdx) {
        return;
      }

      pttpdvb->setIdxs(*positionIdx, *targetIdx, *upwardsIdx);

      JSONFactory::loadAllIndexed<TicketedForwardList<typename PosUpwardsTargetToPosUpwardsDirAvtBldr::AvtBaseType>>(listRsrc, uintDict, j, zbe::factories::listName, "lists"s, "PosUpwardsTargetToPosUpwardsDirAvtBldrFtry"s,
          [&](uint64_t idx, std::shared_ptr<ListType> list) {
            pttpdvb->addIndexNlist(idx, list);
            return true;
          }
      );

    } else {
      SysError::setError("PosUpwardsTargetToPosUpwardsDirAvtBldrFtry config for "s + name + " not found."s);
    }
  }

private:
  using FunctionType = Funct<void, std::shared_ptr<Entity>>;
  using ListType = TicketedForwardList<typename PosUpwardsTargetToPosUpwardsDirAvtBldr::AvtBaseType>;
  NameRsrcDictionary &uintDict = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc    = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<PosUpwardsTargetToPosUpwardsDirAvtBldr>& specificRsrc    = RsrcStore<PosUpwardsTargetToPosUpwardsDirAvtBldr>::getInstance();
  RsrcStore<FunctionType>& mainRsrc = RsrcStore<FunctionType>::getInstance();
  RsrcStore<ListType>& listRsrc = RsrcStore<ListType>::getInstance();
};

// // ---------------------- TODO PosTargetUpwardsToPosDirAngleAvt


// class PosTargetUpwardsToPosDirAngleAvt : public MAvatar<double, Vector3D, Vector3D>, AvatarImp {
// public:

//   /** \brief
//    */
//    void setupEntity(std::shared_ptr<Entity> entity, uint64_t positionidx, uint64_t targetidx, uint64_t upwardsidx) {
//      AvatarImp::setupEntity(entity);
//      _Avatar<1, Vector3D>::setup(&getPosition, &setPosition, (void*)this);
//      _Avatar<2, Vector3D>::setup(&getDirection, &setDirection, (void*)this);
//      _Avatar<3, double>::setup(&getAngle, &setAngle, (void*)this);
//      position = entity->getVector3D(positionidx);
//      target = entity->getVector3D(targetidx);
//      upwards = entity->getVector3D(upwardsidx);
//    }

//    static std::shared_ptr<Value<Vector3D> > getPosition(void *instance) {
//      return ((PosTargetUpwardsToPosDirAngleAvt*)instance)->position;
//    }

//    static std::shared_ptr<Value<Vector3D> > getDirection(void *instance) {
//      auto& position = ((PosTargetUpwardsToPosDirAngleAvt*)instance)->position;
//      auto& target =   ((PosTargetUpwardsToPosDirAngleAvt*)instance)->target;
//      auto p = position->get();
//      auto t = target->get();
//      auto v = (t - p).normalize();
//      auto r = std::make_shared<SimpleValue<Vector3D> >();
//      r->set(v);
//      return r;
//    }

//    static std::shared_ptr<Value<double> > getAngle(void *instance, double angle) {
//     //  auto& position = ((PosTargetUpwardsToPosDirAngleAvt*)instance)->position;
//     //  auto& target =  ((PosTargetUpwardsToPosDirAngleAvt*)instance)->target;
//     //  auto& upwards =  ((PosTargetUpwardsToPosDirAngleAvt*)instance)->upwards;
//     //  auto p = position->get();
//     //  auto t = target->get();
//     //  auto u = upwards->get();
//     //  auto d = (t - p).normalize();
//     //  glm::mat4 rotmat = glm::orientation (detail::tvec3< T > const &Normal, detail::tvec3< T > const &Up);
//     //  //glm::mat4 rotmat = orientation (detail::tvec3< T > const &d, detail::tvec3< T > const &u);
//     //  glm::quat q = glm::quat_cast(rotmat);
//     //  double angle = glm::angle(q);


//      return std::make_shared<SimpleValue<double> >();
//    }

//    static void setAngle(void*, double) {
//      assert(false);
//    }

//    static void setDirection(void*, Vector3D) {
//      assert(false);
//    }

//    static void setPosition(void *, Vector3D) {
//      assert(false);
//    }

//    std::shared_ptr<Entity> getEntity() {
//      assert(false);
//    }


// private:
//   std::shared_ptr<Value<Vector3D> > position;
//   std::shared_ptr<Value<Vector3D> > target;
//   std::shared_ptr<Value<Vector3D> > upwards;
// };

// class PosTargetUpwardsToPosDirAngleAvtBldr : public Funct<void, std::shared_ptr<Entity>> {
// public:
//   using AvtBaseType = MAvatar<double, Vector3D, Vector3D>;
//   void operator()(std::shared_ptr<Entity> ent) {
//     std::shared_ptr<PosTargetUpwardsToPosDirAngleAvt> avt = std::make_shared<PosTargetUpwardsToPosDirAngleAvt>();

//     avt->setupEntity(ent, positionidx, targetidx, upwardsidx);
//     for(auto indexNList : indexNLists) {
//       auto ticket = indexNList.second->push_front(avt);
//       ent->addTicket(indexNList.first, ticket);
//     }
//   }

//   void setIdxs(uint64_t positionidx, uint64_t targetidx, uint64_t upwardsidx) {
//       this->positionidx = positionidx;
//       this->targetidx = targetidx;
//       this->upwardsidx = upwardsidx;
//   }

//   void addIndexNlist(uint64_t index, std::shared_ptr<TicketedForwardList<AvtBaseType>> list) {
//     indexNLists.push_back({index, list});
//   }

// private:
//   uint64_t positionidx;
//   uint64_t targetidx;
//   uint64_t upwardsidx;
//   std::vector<std::pair<uint64_t, std::shared_ptr<TicketedForwardList<AvtBaseType>>>> indexNLists;
// };


// class PosTargetUpwardsToPosDirAngleAvtBldrFtry : public Factory {
// public:
//   void create(std::string name, uint64_t cfgId) {
//     using namespace std::string_literals;
//     std::shared_ptr<PosTargetUpwardsToPosDirAngleAvtBldr> ptutpdaab = std::make_shared<PosTargetUpwardsToPosDirAngleAvtBldr>();
//     mainRsrc.insert(zbe::factories::functionName_ + name, ptutpdaab);
//     specificRsrc.insert("PosTargetUpwardsToPosDirAngleAvtBldr."s + name, ptutpdaab);
//   }

//   void setup(std::string name, uint64_t cfgId) {
//     using namespace std::string_literals;
//     using namespace nlohmann;
//     std::shared_ptr<json> cfg = configRsrc.get(cfgId);

//     if(cfg) {
//       auto j = *cfg;

//       auto ptutpdaab = specificRsrc.get("PosTargetUpwardsToPosDirAngleAvtBldr."s + name);

//       auto positionIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "positionIdx"s, "PosTargetUpwardsToPosDirAngleAvtBldrFtry"s);
//       if(!positionIdx) {
//         return;
//       }
//       auto targetIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "targetIdx"s, "PosTargetUpwardsToPosDirAngleAvtBldrFtry"s);
//       if(!targetIdx) {
//         return;
//       }
//       auto upwardsIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "upwardsIdx"s, "PosTargetUpwardsToPosDirAngleAvtBldrFtry"s);
//       if(!upwardsIdx) {
//         return;
//       }

//       ptutpdaab->setIdxs(*positionIdx, *targetIdx, *upwardsIdx);

//       JSONFactory::loadAllIndexed<TicketedForwardList<typename PosTargetUpwardsToPosDirAngleAvtBldr::AvtBaseType>>(listRsrc, uintDict, j, zbe::factories::listName, "lists"s, "PosTargetToPosDirAvtBldrFtry"s,
//           [&](uint64_t idx, std::shared_ptr<ListType> list) {
//             pttpdvb->addIndexNlist(idx, list);
//             return true;
//           }
//       );

//     } else {
//       SysError::setError("PosTargetUpwardsToPosDirAngleAvtBldrFtry config for "s + name + " not found."s);
//     }
//   }

// private:
//   using FunctionType = Funct<void, std::shared_ptr<Entity>>;
//   using ListType = TicketedForwardList<typename PosTargetUpwardsToPosDirAngleAvtBldr::AvtBaseType>;
//   NameRsrcDictionary &uintDict = NameRsrcDictionary::getInstance();
//   RsrcStore<nlohmann::json> &configRsrc    = RsrcStore<nlohmann::json>::getInstance();
//   RsrcStore<PosTargetUpwardsToPosDirAngleAvtBldr>& specificRsrc    = RsrcStore<PosTargetUpwardsToPosDirAngleAvtBldr>::getInstance();
//   RsrcStore<FunctionType>& mainRsrc = RsrcStore<FunctionType>::getInstance();
//   RsrcStore<ListType>& listRsrc = RsrcStore<ListType>::getInstance();
// };

// // ------- TODO aquí estamos creando avatares , bldrs y factorias para movig Triangle HitBox.

// class MovingTriangle3DHitboxAvt : public SAvatar<MovingTriangle3D>, public AvatarImp {
// public:
//   void setupEntity(std::shared_ptr<Entity> entity, uint64_t positionidx, uint64_t velocityidx, uint64_t orientationidx, uint64_t sizeidx) {
//     AvatarImp::setupEntity(entity);
//     _Avatar<1, MovingTriangle3D>::setup(&getTriangle, &setTriangle, (void*)this);
//     position = entity->getVector3D(positionidx);
//     velocity = entity->getVector3D(velocityidx);
//     orientation = entity->getVector3D(orientationidx);
//     size = entity->getFloat(sizeidx);
//     cTime = entity->getContextTime();
//   }

//   static std::shared_ptr<Value<MovingTriangle3D> > getTriangle(void *instance) {
//     auto  mtha = (MovingTriangle3DHitboxAvt*)instance;
//     auto& position = mtha->position;
//     auto& orientation = mtha->orientation;
//     auto& velocity = mtha->velocity;
//     auto& size = mtha->size;
//     auto p = position->get();
//     auto o = orientation->get();
//     auto v = velocity->get();
//     auto s = size->get();
//     auto time = mtha->cTime->getTotalTime();

//     TODO: Hemos encontrado (recordado) que no tenemos orientacion en nuestro pintado.
//     No mola. Hay que arreglarlo.
//     Una vez hecho eso, hay que traer esas matematicas de translacion, escalado y rotacion aqui
//     MAL:
//     Si que tenemos orientación pero es incorrecta. Tenemos que calcular pitch y yaw desde el look-at
//     https://discord.com/channels/244405112569593857/246018374587383810/1037485466531930223
//     Con esa lógica construimos un avatar nuevo que sustituirá a
//     PosTargetToPosDirAvtFtry

//     Triangle3D t{triangle.a, triangle.b, triangle.c};
//     MovingTriangle3D mt{t, v};
//     auto out = std::make_shared<SimpleValue<MovingTriangle3D> >();
//     out->set(mt);
//     return out;
//   }

//   static void setTriangle(void*, MovingTriangle3D ) {
//     assert(false);
//   }

//   std::shared_ptr<Entity> getEntity() {
//     assert(false);
//   }

//   void setTriangleHitbox(std::shared_ptr<Triangle3D> triangle) {
//     this->triangle = triangle;
//   }


// private:
//  std::shared_ptr<Triangle3D> triangle;
//  std::shared_ptr<Value<Vector3D> > position;
//  std::shared_ptr<Value<Vector3D> > velocity;
//  std::shared_ptr<Value<Vector3D> > orientation;
//  std::shared_ptr<Value<float> > size;
//  std::shared_ptr<ContextTime> cTime;
// };

// class MovingTriangle3DHitboxAvtShapeBldr  : public Funct<std::shared_ptr<SAvatar<MovingTriangle3D>>, std::shared_ptr<Entity>> {
// public:
//   using AvtBaseType = SAvatar<MovingSphere>;
//   std::shared_ptr<SAvatar<MovingTriangle3D>> operator()(std::shared_ptr<Entity> ent) {
//     std::shared_ptr<MovingTriangle3DHitboxAvt> avt = std::make_shared<MovingTriangle3DHitboxAvt>();
//     avt->setupEntity(ent, positionidx, velocityidx, orientationidx, sizeidx);
//     return avt;
//   }

//   void setIdxs(uint64_t positionidx, uint64_t velocityidx, uint64_t orientationidx, uint64_t sizeidx) {
//       this->positionidx = positionidx;
//       this->velocityidx = velocityidx;
//       this->orientationidx = orientationidx;
//       this->sizeidx = sizeidx;
//   }

// private:
//  uint64_t positionidx;
//  uint64_t velocityidx;
//  uint64_t orientationidx;
//  uint64_t sizeidx;

// };

// class MovingTriangle3DHitboxAvtShapeBldrFtry : public Factory {
// public:
//   void create(std::string name, uint64_t cfgId) {
//     using namespace std::string_literals;
//     std::shared_ptr<MovingTriangle3DHitboxAvtShapeBldr> mt3hasb = std::make_shared<MovingTriangle3DHitboxAvtShapeBldr>();
//     mainRsrc.insert(zbe::factories::functionName_ + name, mt3hasb);
//     specificRsrc.insert("MovingTriangle3DHitboxAvtShapeBldr."s + name, msasb);
//   }

//   void setup(std::string name, uint64_t cfgId) {
//     using namespace std::string_literals;
//     using namespace nlohmann;
//     std::shared_ptr<json> cfg = configRsrc.get(cfgId);

//     if(cfg) {
//       auto j = *cfg;

//       auto mt3hasb = specificRsrc.get("MovingTriangle3DHitboxAvtShapeBldr."s + name);

//       auto positionidx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "positionidx"s, "MovingTriangle3DHitboxAvtShapeBldrFtry"s);
//       if(!positionidx) {
//         return;
//       }
//       auto velocityidx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "velocityidx"s, "MovingTriangle3DHitboxAvtShapeBldrFtry"s);
//       if(!velocityidx) {
//         return;
//       }
//       auto orientationidx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "orientationidx"s, "MovingTriangle3DHitboxAvtShapeBldrFtry"s);
//       if(!orientationidx) {
//         return;
//       }

//       auto sizeidx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "sizeidx"s, "MovingTriangle3DHitboxAvtShapeBldrFtry"s);
//       if(!sizeidx) {
//         return;
//       }
//       mt3hasb->setIdxs(*positionidx, *velocityidx, *orientationidx, *sizeidx);

//     } else {
//       SysError::setError("MovingTriangle3DHitboxAvtShapeBldrFtry config for "s + name + " not found."s);
//     }
//   }

// private:
//   using FunctionType = Funct<std::shared_ptr<SAvatar<MovingTriangle3D>>, std::shared_ptr<Entity>>;
//   using ListType = TicketedForwardList<MovingTriangle3DHitboxAvtShapeBldr::AvtBaseType>;
//   RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();
//   RsrcStore<nlohmann::json> &configRsrc                          = RsrcStore<nlohmann::json>::getInstance();
//   RsrcStore<MovingTriangle3DHitboxAvtShapeBldr>& specificRsrc    = RsrcStore<MovingTriangle3DHitboxAvtShapeBldr>::getInstance();
//   RsrcStore<FunctionType>& mainRsrc = RsrcStore<FunctionType>::getInstance();
// };

// class MovingTriangle3DHitboxAvtBldr : public Funct<std::shared_ptr<SAvatar<MovingTriangle3D>>, std::shared_ptr<Entity>> {
// public:
//   using AvtBaseType = SAvatar<MovingTriangle3D>;
//   std::shared_ptr<SAvatar<MovingTriangle3D>> operator()(std::shared_ptr<Entity> ent) {
//     std::shared_ptr<MovingTriangle3DHitboxAvt> avt = std::make_shared<MovingTriangle3DHitboxAvt>();
//     avt->setupEntity(ent, positionidx, velocityidx, orientationidx, sizeidx);
//     for(auto indexNList : indexNLists) {
//       auto ticket = indexNList.second->push_front(avt);
//       ent->addTicket(indexNList.first, ticket);
//     }
//   }

//   void setIdxs(uint64_t positionidx, uint64_t velocityidx, uint64_t orientationidx, uint64_t sizeidx) {
//       this->positionidx = positionidx;
//       this->velocityidx = velocityidx;
//       this->orientationidx = orientationidx;
//       this->sizeidx = sizeidx;
//   }

//   void addIndexNlist(uint64_t index, std::shared_ptr<TicketedForwardList<AvtBaseType>> list) {
//     indexNLists.push_back({index, list});
//   }

// private:
//  uint64_t positionidx;
//  uint64_t velocityidx;
//  uint64_t orientationidx;
//  uint64_t sizeidx;
//  std::vector<std::pair<uint64_t, std::shared_ptr<TicketedForwardList<AvtBaseType>>>> indexNLists;
// };

// class MovingTriangle3DHitboxAvtBldrFtry : public Factory {
// public:
//   void create(std::string name, uint64_t cfgId) {
//     using namespace std::string_literals;
//     std::shared_ptr<MovingTriangle3DHitboxAvtBldr> mt3hab = std::make_shared<MovingTriangle3DHitboxAvtBldr>();
//     mainRsrc.insert(zbe::factories::functionName_ + name, mt3hab);
//     specificRsrc.insert("MovingTriangle3DHitboxAvtBldr."s + name, msab);
//   }

//   void setup(std::string name, uint64_t cfgId) {
//     using namespace std::string_literals;
//     using namespace nlohmann;
//     std::shared_ptr<json> cfg = configRsrc.get(cfgId);

//     if(cfg) {
//       auto j = *cfg;

//       auto mt3hab = specificRsrc.get("MovingTriangle3DHitboxAvtBldr."s + name);

//       auto positionidx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "positionidx"s, "MovingTriangle3DHitboxAvtBldrFtry"s);
//       if(!positionidx) {
//         return;
//       }

//       auto velocityidx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "velocityidx"s, "MovingTriangle3DHitboxAvtBldrFtry"s);
//       if(!velocityidx) {
//         return;
//       }

//       auto orientationidx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "orientationidx"s, "MovingTriangle3DHitboxAvtBldrFtry"s);
//       if(!orientationidx) {
//         return;
//       }

//       auto sizeidx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "sizeidx"s, "MovingTriangle3DHitboxAvtBldrFtry"s);
//       if(!sizeidx) {
//         return;
//       }

//       mt3hab->setIdxs(*positionidx, *velocityidx, *orientationidx, *sizeidx);

//     } else {
//       SysError::setError("MovingTriangle3DHitboxAvtBldrFtry config for "s + name + " not found."s);
//     }
//   }

// private:
//   using FunctionType = Funct<std::shared_ptr<SAvatar<MovingTriangle3D>>, std::shared_ptr<Entity>>;
//   using ListType = TicketedForwardList<MovingTriangle3DHitboxAvtBldr::AvtBaseType>;
//   RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();
//   RsrcStore<nlohmann::json> &configRsrc                          = RsrcStore<nlohmann::json>::getInstance();
//   RsrcStore<MovingTriangle3DHitboxAvtBldr>& specificRsrc    = RsrcStore<MovingTriangle3DHitboxAvtBldr>::getInstance();
//   RsrcStore<FunctionType>& mainRsrc = RsrcStore<FunctionType>::getInstance();
// };

// TODO
// MovingTriangle3DAvtShapeBldr
// MovingTriangle3DAvtShapeBldrFtry
// MovingTriangle3DAvtBldr
// MovingTriangle3DAvtBldrFtry

// -----


class DerivedPosMovingSphereAvt : public SAvatar<MovingSphere>, public AvatarImp {
public:

  /** \brief
   */
   void setupEntity(std::shared_ptr<Entity> entity, uint64_t positionidx, uint64_t radiusidx) {
     AvatarImp::setupEntity(entity);
     _Avatar<1, MovingSphere>::setup(&getSphere, &setSphere, (void*)this);
     position = entity->getVector3D(positionidx);
     radius = entity->getFloat(radiusidx);
     cTime = entity->getContextTime();
   }

   static std::shared_ptr<Value<MovingSphere> > getSphere(void *instance) {
     auto  dpmsa = (DerivedPosMovingSphereAvt*)instance;
     auto& position = dpmsa->position;
     auto p = position->get();
     auto r = dpmsa->radius->get();
     auto time = dpmsa->cTime->getTotalTime();
     float div = (time / (float)dpmsa->period) * TAU;
     float cosine = cos(div);
     float newVal = ((cosine + 1.0) / 2.0) * (dpmsa->max - dpmsa->min) + dpmsa->min;
     Vector3D v{0.0, 0.0, 0.0};
     v[dpmsa->component] = newVal / time;
     Sphere s(p.toPoint(), r);
     MovingSphere ms{s, v};
     auto out = std::make_shared<SimpleValue<MovingSphere> >();
     out->set(ms);
     return out;
   }

   static void setSphere(void *instance, MovingSphere position) {
     assert(false);
   }

   std::shared_ptr<Entity> getEntity() {
     assert(false);
   }

   void setRange(float min, float max) {this->min = min; this->max = max;}

   void setPeriod(int64_t period) {this->period = period;}

   void setComponent(int64_t component) {
     assert(component>=0 && component<=2);
     this->component = component;
   }

private:
  std::shared_ptr<Value<Vector3D> > position;
  std::shared_ptr<Value<float> > radius;
  std::shared_ptr<ContextTime> cTime;

  float min;
  float max;
  int64_t period;
  int64_t component;
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

class TargetToDirAvtBldr : public Funct<void, std::shared_ptr<Entity>> {
public:
  using AvtBaseType = MAvatar<Vector3D, Vector3D, Vector3D>;
  void operator()(std::shared_ptr<Entity> ent) {
    std::shared_ptr<TargetToDirAvt> avt = std::make_shared<TargetToDirAvt>();
    avt->setupEntity(ent, positionidx, targetidx,upwardsidx, scaleidx);
    for(auto indexNList : indexNLists) {
      auto ticket = indexNList.second->push_front(avt);
      ent->addTicket(indexNList.first, ticket);
    }
  }

  void setIdxs(uint64_t positionidx, uint64_t targetidx, uint64_t upwardsidx, uint64_t scaleidx) {
      this->positionidx = positionidx;
      this->targetidx = targetidx;
      this->upwardsidx = upwardsidx;
      this->scaleidx = scaleidx;
  }

  void addIndexNlist(uint64_t index, std::shared_ptr<TicketedForwardList<AvtBaseType>> list) {
    indexNLists.push_back({index, list});
  }

private:
  uint64_t positionidx;
  uint64_t targetidx;
  uint64_t upwardsidx;
  uint64_t scaleidx;
  std::vector<std::pair<uint64_t, std::shared_ptr<TicketedForwardList<AvtBaseType>>>> indexNLists;
};


class PosTargetToPosDirAvtBldr : public Funct<void, std::shared_ptr<Entity>> {
public:
  using AvtBaseType = MAvatar<Vector3D, Vector3D>;
  void operator()(std::shared_ptr<Entity> ent) {
    std::shared_ptr<PosTargetToPosDirAvt> avt = std::make_shared<PosTargetToPosDirAvt>();

    avt->setupEntity(ent, positionidx, targetidx);
    for(auto indexNList : indexNLists) {
      auto ticket = indexNList.second->push_front(avt);
      ent->addTicket(indexNList.first, ticket);
    }
  }

  void setIdxs(uint64_t positionidx, uint64_t targetidx) {
      this->positionidx = positionidx;
      this->targetidx = targetidx;
  }

  void addIndexNlist(uint64_t index, std::shared_ptr<TicketedForwardList<AvtBaseType>> list) {
    indexNLists.push_back({index, list});
  }

private:
  uint64_t positionidx;
  uint64_t targetidx;
  std::vector<std::pair<uint64_t, std::shared_ptr<TicketedForwardList<AvtBaseType>>>> indexNLists;
};


class DerivedCosVelAvtBldr : public Funct<void, std::shared_ptr<Entity>> {
public:
  using AvtBaseType = MAvatar<Vector3D, Vector3D>;
  void operator()(std::shared_ptr<Entity> ent) {
    std::shared_ptr<DerivedCosVelAvt> avt = std::make_shared<DerivedCosVelAvt>();
    avt->setRange(min, max);
    avt->setPeriod(period);
    avt->setComponent(component);

    avt->setupEntity(ent, positionidx);
    for(auto indexNList : indexNLists) {
      auto ticket = indexNList.second->push_front(avt);
      ent->addTicket(indexNList.first, ticket);
    }
  }

  void setIdx(uint64_t positionidx) {
      this->positionidx = positionidx;
  }

  void addIndexNlist(uint64_t index, std::shared_ptr<TicketedForwardList<AvtBaseType>> list) {
    indexNLists.push_back({index, list});
  }

  void setRange(float min, float max) {this->min = min; this->max = max;}

  void setPeriod(int64_t period) {this->period = period;}

  void setComponent(int64_t component) {
    assert(component>=0 && component<=2);
    this->component = component;
  }

private:
    float min;
    float max;
    int64_t period;
    int64_t component;
    uint64_t positionidx;
    std::vector<std::pair<uint64_t, std::shared_ptr<TicketedForwardList<AvtBaseType>>>> indexNLists;
};

class DerivedPosMovingSphereAvtShapeBldr : public Funct<std::shared_ptr<SAvatar<MovingSphere>>, std::shared_ptr<Entity>> {
// This class where c&p from DerivedPosMovingSphereAvtBldr removing list managment
public:
  using AvtBaseType = SAvatar<MovingSphere>;
  std::shared_ptr<SAvatar<MovingSphere>> operator()(std::shared_ptr<Entity> ent) {
    std::shared_ptr<DerivedPosMovingSphereAvt> avt = std::make_shared<DerivedPosMovingSphereAvt>();
    avt->setRange(min, max);
    avt->setPeriod(period);
    avt->setComponent(component);
    avt->setupEntity(ent, positionidx, radiusidx);
    return avt;
  }

  void setIdxs(uint64_t positionidx, uint64_t radiusidx) {
      this->positionidx = positionidx;
      this->radiusidx = radiusidx;
  }

  void setRange(float min, float max) {this->min = min; this->max = max;}

  void setPeriod(int64_t period) {this->period = period;}

  void setComponent(int64_t component) {
    assert(component>=0 && component<=2);
    this->component = component;
  }

private:
 float min;
 float max;
 int64_t period;
 int64_t component;
 uint64_t positionidx;
 uint64_t radiusidx;
};

class DerivedPosMovingSphereAvtBldr : public Funct<void, std::shared_ptr<Entity>> {
// This class where c&p to DerivedPosMovingSphereAvtShapeBldr
public:
  using AvtBaseType = SAvatar<MovingSphere>;
  void operator()(std::shared_ptr<Entity> ent) {
    std::shared_ptr<DerivedPosMovingSphereAvt> avt = std::make_shared<DerivedPosMovingSphereAvt>();
    avt->setRange(min, max);
    avt->setPeriod(period);
    avt->setComponent(component);

    avt->setupEntity(ent, positionidx, radiusidx);
    for(auto indexNList : indexNLists) {
      auto ticket = indexNList.second->push_front(avt);
      ent->addTicket(indexNList.first, ticket);
    }
  }

  void setIdxs(uint64_t positionidx, uint64_t radiusidx) {
      this->positionidx = positionidx;
      this->radiusidx = radiusidx;
  }

  void addIndexNlist(uint64_t index, std::shared_ptr<TicketedForwardList<AvtBaseType>> list) {
    indexNLists.push_back({index, list});
  }


  void setRange(float min, float max) {this->min = min; this->max = max;}

  void setPeriod(int64_t period) {this->period = period;}

  void setComponent(int64_t component) {
    assert(component>=0 && component<=2);
    this->component = component;
  }

private:
 float min;
 float max;
 int64_t period;
 int64_t component;
 uint64_t positionidx;
 uint64_t radiusidx;
 std::vector<std::pair<uint64_t, std::shared_ptr<TicketedForwardList<AvtBaseType>>>> indexNLists;
};

class LookAtToPitchAvtBldr : public Funct<void, std::shared_ptr<Entity>> {
public:
  using AvtBaseType = MAvatar<Vector3D, Vector3D>;
  void operator()(std::shared_ptr<Entity> ent) {
    std::shared_ptr<LookAtToPitchAvt> avt = std::make_shared<LookAtToPitchAvt>();
    avt->setupEntity(ent, positionidx, targetidx,upwardsidx);
    for(auto indexNList : indexNLists) {
      auto ticket = indexNList.second->push_front(avt);
      ent->addTicket(indexNList.first, ticket);
    }
  }

  void setIdxs(uint64_t positionidx, uint64_t targetidx, uint64_t upwardsidx) {
      this->positionidx = positionidx;
      this->targetidx = targetidx;
      this->upwardsidx = upwardsidx;
  }

  void addIndexNlist(uint64_t index, std::shared_ptr<TicketedForwardList<AvtBaseType>> list) {
    indexNLists.push_back({index, list});
  }

private:
  uint64_t positionidx;
  uint64_t targetidx;
  uint64_t upwardsidx;
  std::vector<std::pair<uint64_t, std::shared_ptr<TicketedForwardList<AvtBaseType>>>> indexNLists;
};

class LookAtToYawAvtBldr : public Funct<void, std::shared_ptr<Entity>> {
public:
  using AvtBaseType = MAvatar<Vector3D, Vector3D>;
  void operator()(std::shared_ptr<Entity> ent) {
    std::shared_ptr<LookAtToPitchAvt> avt = std::make_shared<LookAtToPitchAvt>();
    avt->setupEntity(ent, positionidx, targetidx,upwardsidx);
    for(auto indexNList : indexNLists) {
      auto ticket = indexNList.second->push_front(avt);
      ent->addTicket(indexNList.first, ticket);
    }
  }

  void setIdxs(uint64_t positionidx, uint64_t targetidx, uint64_t upwardsidx) {
      this->positionidx = positionidx;
      this->targetidx = targetidx;
      this->upwardsidx = upwardsidx;
  }

  void addIndexNlist(uint64_t index, std::shared_ptr<TicketedForwardList<AvtBaseType>> list) {
    indexNLists.push_back({index, list});
  }

private:
  uint64_t positionidx;
  uint64_t targetidx;
  uint64_t upwardsidx;
  std::vector<std::pair<uint64_t, std::shared_ptr<TicketedForwardList<AvtBaseType>>>> indexNLists;
};

//---------------------------- NUEVAS

class TargetToDirAvtBldrFtry : public Factory {
public:
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<TargetToDirAvtBldr> ttdab = std::make_shared<TargetToDirAvtBldr>();
    mainRsrc.insert(zbe::factories::functionName_ + name, ttdab);
    specificRsrc.insert("TargetToDirAvtBldr."s + name, ttdab);
  }

  void setup(std::string name, uint64_t cfgId){
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto ttdab = specificRsrc.get("TargetToDirAvtBldr."s + name);

      auto positionIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "positionIdx"s, "TargetToDirAvtBldrFtry"s);
      if(!positionIdx) {
        return;
      }
      auto targetIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "targetIdx"s, "TargetToDirAvtBldrFtry"s);
      if(!targetIdx) {
        return;
      }
      auto upwardsIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "upwardsIdx"s, "TargetToDirAvtBldrFtry"s);
      if(!upwardsIdx) {
        return;
      }
      auto scaleIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "scaleIdx"s, "TargetToDirAvtBldrFtry"s);
      if(!scaleIdx) {
        return;
      }

      ttdab->setIdxs(*positionIdx, *targetIdx, *upwardsIdx, *scaleIdx);

      JSONFactory::loadAllIndexed<TicketedForwardList<typename TargetToDirAvtBldr::AvtBaseType>>(listRsrc, uintDict, j, zbe::factories::listName, "lists"s, "TargetToDirAvtBldrFtry"s,
          [&](uint64_t idx, std::shared_ptr<ListType> list) {
            ttdab->addIndexNlist(idx, list);
            return true;
          }
      );

    } else {
      SysError::setError("TargetToDirAvtBldrFtry config for "s + name + " not found."s);
    }
  }

private:
  using FunctionType = Funct<void, std::shared_ptr<Entity>>;
  using ListType = TicketedForwardList<typename TargetToDirAvtBldr::AvtBaseType>;
  NameRsrcDictionary &uintDict = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc    = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<TargetToDirAvtBldr>& specificRsrc    = RsrcStore<TargetToDirAvtBldr>::getInstance();
  RsrcStore<FunctionType>& mainRsrc = RsrcStore<FunctionType>::getInstance();
  RsrcStore<ListType>& listRsrc = RsrcStore<ListType>::getInstance();
};


class PosTargetToPosDirAvtBldrFtry : public Factory {
public:
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<PosTargetToPosDirAvtBldr> pttpdvb = std::make_shared<PosTargetToPosDirAvtBldr>();
    mainRsrc.insert(zbe::factories::functionName_ + name, pttpdvb);
    specificRsrc.insert("PosTargetToPosDirAvtBldr."s + name, pttpdvb);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto pttpdvb = specificRsrc.get("PosTargetToPosDirAvtBldr."s + name);

      auto positionIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "positionIdx"s, "PosTargetToPosDirAvtBldrFtry"s);
      if(!positionIdx) {
        return;
      }
      auto targetIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "targetIdx"s, "PosTargetToPosDirAvtBldrFtry"s);
      if(!targetIdx) {
        return;
      }

      pttpdvb->setIdxs(*positionIdx, *targetIdx);

      JSONFactory::loadAllIndexed<TicketedForwardList<typename PosTargetToPosDirAvtBldr::AvtBaseType>>(listRsrc, uintDict, j, zbe::factories::listName, "lists"s, "PosTargetToPosDirAvtBldrFtry"s,
          [&](uint64_t idx, std::shared_ptr<ListType> list) {
            pttpdvb->addIndexNlist(idx, list);
            return true;
          }
      );

    } else {
      SysError::setError("PosTargetToPosDirAvtBldrFtry config for "s + name + " not found."s);
    }
  }

private:
  using FunctionType = Funct<void, std::shared_ptr<Entity>>;
  using ListType = TicketedForwardList<typename PosTargetToPosDirAvtBldr::AvtBaseType>;
  NameRsrcDictionary &uintDict = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc    = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<PosTargetToPosDirAvtBldr>& specificRsrc    = RsrcStore<PosTargetToPosDirAvtBldr>::getInstance();
  RsrcStore<FunctionType>& mainRsrc = RsrcStore<FunctionType>::getInstance();
  RsrcStore<ListType>& listRsrc = RsrcStore<ListType>::getInstance();
};


class DerivedCosVelAvtBldrFtry : public Factory {
public:
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<DerivedCosVelAvtBldr> dcvab = std::make_shared<DerivedCosVelAvtBldr>();
    mainRsrc.insert(zbe::factories::functionName_ + name, dcvab);
    specificRsrc.insert("DerivedCosVelAvtBldr."s + name, dcvab);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto dcvab = specificRsrc.get("DerivedCosVelAvtBldr."s + name);

      auto positionIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "positionIdx"s, "DerivedCosVelAvtBldrFtry"s);
      if(!positionIdx) {
        return;
      }
      auto min = JSONFactory::loadParamCfgDict<float>(floatDict, j, "min"s, "DerivedCosVelAvtBldrFtry"s);
      if(!min) {
        return;
      }
      auto max = JSONFactory::loadParamCfgDict<float>(floatDict, j, "max"s, "DerivedCosVelAvtBldrFtry"s);
      if(!max) {
        return;
      }
      auto period = JSONFactory::loadParamCfgDict<int64_t>(intDict, j, "period"s, "DerivedCosVelAvtBldrFtry"s);
      if(!period) {
        return;
      }
      auto component = JSONFactory::loadParamCfgDict<int64_t>(intDict, j, "component"s, "DerivedCosVelAvtBldrFtry"s);
      if(!component) {
        return;
      }
      dcvab->setIdx(*positionIdx);
      dcvab->setRange(*min, *max);
      dcvab->setPeriod(*period);
      dcvab->setComponent(*component);

      JSONFactory::loadAllIndexed<TicketedForwardList<typename DerivedCosVelAvtBldr::AvtBaseType>>(listRsrc, uintDict, j, zbe::factories::listName, "lists"s, "DerivedCosVelAvtBldrFtry"s,
          [&](uint64_t idx, std::shared_ptr<ListType> list) {
            dcvab->addIndexNlist(idx, list);
            return true;
          }
      );

    } else {
      SysError::setError("DerivedCosVelAvtBldrFtry config for "s + name + " not found."s);
    }
  }

private:
  using FunctionType = Funct<void, std::shared_ptr<Entity>>;
  using ListType = TicketedForwardList<typename PosTargetToPosDirAvtBldr::AvtBaseType>;
  RsrcDictionary<float>& floatDict = RsrcDictionary<float>::getInstance();
  RsrcDictionary<int64_t>& intDict = RsrcDictionary<int64_t>::getInstance();
  RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc                          = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<TicketedForwardList<DerivedCosVelAvtBldr::AvtBaseType>>& listRsrc = RsrcStore<TicketedForwardList<DerivedCosVelAvtBldr::AvtBaseType>>::getInstance();
  RsrcStore<DerivedCosVelAvtBldr>& specificRsrc    = RsrcStore<DerivedCosVelAvtBldr>::getInstance();
  RsrcStore<FunctionType>& mainRsrc = RsrcStore<FunctionType>::getInstance();
};

class DerivedPosMovingSphereAvtShapeBldrFtry : public Factory {
// This class where c&p from DerivedPosMovingSphereAvtBldrFtry removing list managment
public:
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<DerivedPosMovingSphereAvtShapeBldr> dpmsa = std::make_shared<DerivedPosMovingSphereAvtShapeBldr>();
    mainRsrc.insert(zbe::factories::functionName_ + name, dpmsa);
    specificRsrc.insert("DerivedPosMovingSphereAvtShapeBldr."s + name, dpmsa);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto dpmsa = specificRsrc.get("DerivedPosMovingSphereAvtShapeBldr."s + name);

      auto positionIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "positionIdx"s, "DerivedPosMovingSphereAvtShapeBldrFtry"s);
      if(!positionIdx) {
        return;
      }
      auto radiusidx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "radiusIdx"s, "DerivedPosMovingSphereAvtShapeBldrFtry"s);
      if(!positionIdx) {
        return;
      }
      auto min = JSONFactory::loadParamCfgDict<float>(floatDict, j, "min"s, "DerivedPosMovingSphereAvtShapeBldrFtry"s);
      if(!min) {
        return;
      }
      auto max = JSONFactory::loadParamCfgDict<float>(floatDict, j, "max"s, "DerivedPosMovingSphereAvtShapeBldrFtry"s);
      if(!max) {
        return;
      }
      auto period = JSONFactory::loadParamCfgDict<int64_t>(intDict, j, "period"s, "DerivedPosMovingSphereAvtShapeBldrFtry"s);
      if(!period) {
        return;
      }
      auto component = JSONFactory::loadParamCfgDict<int64_t>(intDict, j, "component"s, "DerivedPosMovingSphereAvtShapeBldrFtry"s);
      if(!component) {
        return;
      }
      dpmsa->setIdxs(*positionIdx, *radiusidx);
      dpmsa->setRange(*min, *max);
      dpmsa->setPeriod(*period);
      dpmsa->setComponent(*component);

    } else {
      SysError::setError("DerivedPosMovingSphereAvtShapeBldrFtry config for "s + name + " not found."s);
    }
  }

private:
  using FunctionType = Funct<std::shared_ptr<SAvatar<MovingSphere>>, std::shared_ptr<Entity>>;
  using ListType = TicketedForwardList<DerivedPosMovingSphereAvtShapeBldr::AvtBaseType>;
  RsrcDictionary<float>& floatDict = RsrcDictionary<float>::getInstance();
  RsrcDictionary<int64_t>& intDict = RsrcDictionary<int64_t>::getInstance();
  RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc                          = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<DerivedPosMovingSphereAvtShapeBldr>& specificRsrc    = RsrcStore<DerivedPosMovingSphereAvtShapeBldr>::getInstance();
  RsrcStore<FunctionType>& mainRsrc = RsrcStore<FunctionType>::getInstance();
};

class DerivedPosMovingSphereAvtBldrFtry : public Factory {
// This class where c&p to DerivedPosMovingSphereAvtShapeBldrFtry
public:
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<DerivedPosMovingSphereAvtBldr> dpmsa = std::make_shared<DerivedPosMovingSphereAvtBldr>();
    mainRsrc.insert(zbe::factories::functionName_ + name, dpmsa);
    specificRsrc.insert("DerivedPosMovingSphereAvtBldr."s + name, dpmsa);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto dpmsa = specificRsrc.get("DerivedPosMovingSphereAvtBldr."s + name);

      auto positionIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "positionIdx"s, "DerivedPosMovingSphereAvtBldrFtry"s);
      if(!positionIdx) {
        return;
      }
      auto radiusidx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "radiusIdx"s, "DerivedPosMovingSphereAvtBldrFtry"s);
      if(!positionIdx) {
        return;
      }
      auto min = JSONFactory::loadParamCfgDict<float>(floatDict, j, "min"s, "DerivedPosMovingSphereAvtBldrFtry"s);
      if(!min) {
        return;
      }
      auto max = JSONFactory::loadParamCfgDict<float>(floatDict, j, "max"s, "DerivedPosMovingSphereAvtBldrFtry"s);
      if(!max) {
        return;
      }
      auto period = JSONFactory::loadParamCfgDict<int64_t>(intDict, j, "period"s, "DerivedPosMovingSphereAvtBldrFtry"s);
      if(!period) {
        return;
      }
      auto component = JSONFactory::loadParamCfgDict<int64_t>(intDict, j, "component"s, "DerivedPosMovingSphereAvtBldrFtry"s);
      if(!component) {
        return;
      }
      dpmsa->setIdxs(*positionIdx, *radiusidx);
      dpmsa->setRange(*min, *max);
      dpmsa->setPeriod(*period);
      dpmsa->setComponent(*component);

      JSONFactory::loadAllIndexed<TicketedForwardList<typename DerivedPosMovingSphereAvtBldr::AvtBaseType>>(listRsrc, uintDict, j, zbe::factories::listName, "lists"s, "DerivedPosMovingSphereAvtBldrFtry"s,
          [&](uint64_t idx, std::shared_ptr<ListType> list) {
            dpmsa->addIndexNlist(idx, list);
            return true;
          }
      );

    } else {
      SysError::setError("DerivedPosMovingSphereAvtBldrFtry config for "s + name + " not found."s);
    }
  }

private:
  using FunctionType = Funct<void, std::shared_ptr<Entity>>;
  using ListType = TicketedForwardList<DerivedPosMovingSphereAvtBldr::AvtBaseType>;
  RsrcDictionary<float>& floatDict = RsrcDictionary<float>::getInstance();
  RsrcDictionary<int64_t>& intDict = RsrcDictionary<int64_t>::getInstance();
  RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc                          = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<ListType>& listRsrc = RsrcStore<ListType>::getInstance();
  RsrcStore<DerivedPosMovingSphereAvtBldr>& specificRsrc    = RsrcStore<DerivedPosMovingSphereAvtBldr>::getInstance();
  RsrcStore<FunctionType>& mainRsrc = RsrcStore<FunctionType>::getInstance();
};

class LookAtToPitchAvtBldrFtry : public Factory {
public:
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<LookAtToPitchAvtBldr> latpab = std::make_shared<LookAtToPitchAvtBldr>();
    mainRsrc.insert(zbe::factories::functionName_ + name, latpab);
    specificRsrc.insert("LookAtToPitchAvtBldr."s + name, latpab);
  }
  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto latpab = specificRsrc.get("LookAtToPitchAvtBldr."s + name);

      auto positionIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "positionIdx"s, "LookAtToPitchAvtBldrFtry"s);
      if(!positionIdx) {
        return;
      }
      auto targetidx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "targetidx"s, "LookAtToPitchAvtBldrFtry"s);
      if(!targetidx) {
        return;
      }
      auto upwardsidx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "upwardsidx"s, "LookAtToPitchAvtBldrFtry"s);
      if(!upwardsidx) {
        return;
      }
      latpab->setIdxs(*positionIdx, *targetidx, *upwardsidx);

      JSONFactory::loadAllIndexed<TicketedForwardList<typename LookAtToPitchAvtBldr::AvtBaseType>>(listRsrc, uintDict, j, zbe::factories::listName, "lists"s, "LookAtToPitchAvtBldrFtry"s,
          [&](uint64_t idx, std::shared_ptr<ListType> list) {
            latpab->addIndexNlist(idx, list);
            return true;
          }
      );
    } else {
      SysError::setError("LookAtToPitchAvtBldrFtry config for "s + name + " not found."s);
    }
  }
private:
  using FunctionType = Funct<void, std::shared_ptr<Entity>>;
  using ListType = TicketedForwardList<LookAtToPitchAvtBldr::AvtBaseType>;
  RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc                          = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<ListType>& listRsrc = RsrcStore<ListType>::getInstance();
  RsrcStore<LookAtToPitchAvtBldr>& specificRsrc    = RsrcStore<LookAtToPitchAvtBldr>::getInstance();
  RsrcStore<FunctionType>& mainRsrc = RsrcStore<FunctionType>::getInstance();
};

class LookAtToYawAvtBldrFtry : public Factory {
public:
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<LookAtToYawAvtBldr> latyab = std::make_shared<LookAtToYawAvtBldr>();
    mainRsrc.insert(zbe::factories::functionName_ + name, latyab);
    specificRsrc.insert("LookAtToYawAvtBldr."s + name, latyab);
  }
  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto latyab = specificRsrc.get("LookAtToYawAvtBldr."s + name);

      auto positionIdx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "positionIdx"s, "LookAtToYawAvtBldrFtry"s);
      if(!positionIdx) {
        return;
      }
      auto targetidx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "targetidx"s, "LookAtToYawAvtBldrFtry"s);
      if(!targetidx) {
        return;
      }
      auto upwardsidx = JSONFactory::loadParamCfgDict<uint64_t>(uintDict, j, "upwardsidx"s, "LookAtToYawAvtBldrFtry"s);
      if(!upwardsidx) {
        return;
      }
      latyab->setIdxs(*positionIdx, *targetidx, *upwardsidx);

      JSONFactory::loadAllIndexed<TicketedForwardList<typename DerivedCosVelAvtBldr::AvtBaseType>>(listRsrc, uintDict, j, zbe::factories::listName, "lists"s, "LookAtToYawAvtBldrFtry"s,
          [&](uint64_t idx, std::shared_ptr<ListType> list) {
            latyab->addIndexNlist(idx, list);
            return true;
          }
      );

    } else {
      SysError::setError("LookAtToYawAvtBldrFtry config for "s + name + " not found."s);
    }
  }
private:
  using FunctionType = Funct<void, std::shared_ptr<Entity>>;
  using ListType = TicketedForwardList<LookAtToYawAvtBldr::AvtBaseType>;
  RsrcDictionary<uint64_t>& uintDict = RsrcDictionary<uint64_t>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc                          = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<ListType >& listRsrc = RsrcStore<ListType >::getInstance();
  RsrcStore<LookAtToYawAvtBldr>& specificRsrc    = RsrcStore<LookAtToYawAvtBldr>::getInstance();
  RsrcStore<FunctionType>& mainRsrc = RsrcStore<FunctionType>::getInstance();
};


//---------------------------- NUEVAS
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

//-----
class DerivedCosVelAvtFtry : public Factory {
  /** \brief Builds a TargetToDirAvt.
   *  \param name Name for the created TargetToDirAvt.
   *  \param cfgId TargetToDirAvt's configuration id.
   */
  void create(std::string name, uint64_t){
    using namespace std::string_literals;

    auto dcv = std::make_shared<DerivedCosVelAvt>();
    dcvStore.insert("DerivedCosVelAvt."s + name, dcv);
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
        SysError::setError("DerivedCosVelAvtFtry " + name + " config for entity must be a string."s);
        return;
      }
      if (!j["lists"].is_object()) {
        SysError::setError("DerivedCosVelAvtFtry " + name + " config for lists must be an object. But is "s + j["lists"].type_name());
        return;
      }
      if (!j["positionIdx"].is_string()) {
        SysError::setError("DerivedCosVelAvtFtry " + name + " config for positionIdx must be a string."s);
        return;
      }
      if (!j["min"].is_string()) {
        SysError::setError("DerivedCosVelAvtFtry config for min: "s + j["min"].get<std::string>() + ": must be a literal float name."s);
        return;
      }
      if (!j["max"].is_string()) {
        SysError::setError("DerivedCosVelAvtFtry config for max: "s + j["max"].get<std::string>() + ": must be a literal float name."s);
        return;
      }
      if (!j["period"].is_string()) {
        SysError::setError("DerivedCosVelAvtFtry config for period: "s + j["period"].get<std::string>() + ": must be a literal int64_t name."s);
        return;
      }
      if (!j["component"].is_string()) {
        SysError::setError("DerivedCosVelAvtFtry config for component: "s + j["component"].get<std::string>() + ": must be a literal int64_t name."s);
        return;
      }

      std::string entityName = j["entity"].get<std::string>();
      if(!entityRsrc.contains("Entity."s + entityName)) {
        SysError::setError("DerivedCosVelAvtFtry config for entity: "s + entityName + " is not an entity name."s);
        return;
      }

      std::string positionIdxName = j["positionIdx"].get<std::string>();
      if(!dict.contains(positionIdxName)) {
        SysError::setError("DerivedCosVelAvtFtry config for positionIdx: "s + positionIdxName + " is not an positionIdx name."s);
        return;
      }

      std::string minName = j["min"].get<std::string>();
      if(!floatDict.contains(minName)) {
        SysError::setError("DerivedCosVelAvtFtry config for min: "s + minName + " is not a float literal."s);
        return;
      }

      std::string maxName = j["max"].get<std::string>();
      if(!floatDict.contains(maxName)) {
        SysError::setError("DerivedCosVelAvtFtry config for max: "s + maxName + " is not a float literal."s);
        return;
      }

      std::string periodName = j["period"].get<std::string>();
      if(!intDict.contains(periodName)) {
        SysError::setError("DerivedCosVelAvtFtry config for period: "s + periodName + " is not a int64_t literal."s);
        return;
      }

      std::string componentName = j["component"].get<std::string>();
      if(!intDict.contains(componentName)) {
        SysError::setError("DerivedCosVelAvtFtry config for period: "s + periodName + " is not a int64_t literal."s);
        return;
      }

      std::shared_ptr<Entity> ent = entityRsrc.get("Entity."s + entityName);
      float min = floatDict.get(minName);
      float max = floatDict.get(maxName);
      int64_t period = intDict.get(periodName);
      int64_t component = intDict.get(componentName);
      uint64_t positionIdx = dict.get(positionIdxName);
      auto dcv = dcvStore.get("DerivedCosVelAvt."s + name);

      dcv->setupEntity(ent, positionIdx);
      dcv->setRange(min, max);
      dcv->setPeriod(period);
      dcv->setComponent(component);

      auto listsCfg = j["lists"];
      for (auto& listCfg : listsCfg.items()) {
        if (!listCfg.value().is_string()) {
          SysError::setError("DerivedCosVelAvtFtry " + name + " config for lists must contain strings. But is "s + listCfg.value().type_name());
          return;
        }
        auto list = listStore.get("List." + listCfg.key());
        auto ticket = list->push_front(dcv);
        ent->addTicket(dict.get(listCfg.value().get<std::string>()), ticket);
      }
      dcvStore.remove("DerivedCosVelAvt."s + name);
    } else {
      SysError::setError("DerivedCosVelAvtFtry config for "s + name + " not found."s);
    }
  }

private:
  RsrcDictionary<float>& floatDict = RsrcDictionary<float>::getInstance();
  RsrcDictionary<int64_t>& intDict = RsrcDictionary<int64_t>::getInstance();
  NameRsrcDictionary &dict                                       = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc                          = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<DerivedCosVelAvt>& dcvStore                          = RsrcStore<DerivedCosVelAvt>::getInstance();
  RsrcStore<Entity>& entityRsrc                                  = RsrcStore<Entity>::getInstance();
  RsrcStore<TicketedForwardList<MAvatar<Vector3D> > >& listStore = RsrcStore<TicketedForwardList<MAvatar<Vector3D> > >::getInstance();
};


class DerivedPosMovingSphereAvtFtry : public Factory {
  /** \brief Builds a TargetToDirAvt.
   *  \param name Name for the created TargetToDirAvt.
   *  \param cfgId TargetToDirAvt's configuration id.
   */
  void create(std::string name, uint64_t){
    using namespace std::string_literals;

    auto dpmsa = std::make_shared<DerivedPosMovingSphereAvt>();
    dpmsavtStore.insert("DerivedPosMovingSphereAvt."s + name, dpmsa);
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
        SysError::setError("DerivedPosMovingSphereAvtFtry " + name + " config for entity must be a string."s);
        return;
      }
      if (!j["lists"].is_object()) {
        SysError::setError("DerivedPosMovingSphereAvtFtry " + name + " config for lists must be an object. But is "s + j["lists"].type_name());
        return;
      }
      if (!j["positionIdx"].is_string()) {
        SysError::setError("DerivedPosMovingSphereAvtFtry " + name + " config for positionIdx must be a string."s);
        return;
      }
      if (!j["radiusIdx"].is_string()) {
        SysError::setError("DerivedPosMovingSphereAvtFtry " + name + " config for positionIdx must be a string."s);
        return;
      }
      if (!j["min"].is_string()) {
        SysError::setError("DerivedPosMovingSphereAvtFtry config for min: "s + j["min"].get<std::string>() + ": must be a literal float name."s);
        return;
      }
      if (!j["max"].is_string()) {
        SysError::setError("DerivedPosMovingSphereAvtFtry config for max: "s + j["max"].get<std::string>() + ": must be a literal float name."s);
        return;
      }
      if (!j["period"].is_string()) {
        SysError::setError("DerivedPosMovingSphereAvtFtry config for period: "s + j["period"].get<std::string>() + ": must be a literal int64_t name."s);
        return;
      }
      if (!j["component"].is_string()) {
        SysError::setError("DerivedPosMovingSphereAvtFtry config for component: "s + j["component"].get<std::string>() + ": must be a literal int64_t name."s);
        return;
      }

      std::string entityName = j["entity"].get<std::string>();
      if(!entityRsrc.contains("Entity."s + entityName)) {
        SysError::setError("DerivedPosMovingSphereAvtFtry config for entity: "s + entityName + " is not an entity name."s);
        return;
      }

      std::string positionIdxName = j["positionIdx"].get<std::string>();
      if(!dict.contains(positionIdxName)) {
        SysError::setError("DerivedPosMovingSphereAvtFtry config for positionIdx: "s + positionIdxName + " is not an positionIdx name."s);
        return;
      }

      std::string radiusIdxName = j["radiusIdx"].get<std::string>();
      if(!dict.contains(radiusIdxName)) {
        SysError::setError("DerivedPosMovingSphereAvtFtry config for radiusIdx: "s + radiusIdxName + " is not an positionIdx name."s);
        return;
      }

      std::string minName = j["min"].get<std::string>();
      if(!floatDict.contains(minName)) {
        SysError::setError("DerivedPosMovingSphereAvtFtry config for min: "s + minName + " is not a float literal."s);
        return;
      }

      std::string maxName = j["max"].get<std::string>();
      if(!floatDict.contains(maxName)) {
        SysError::setError("DerivedPosMovingSphereAvtFtry config for max: "s + maxName + " is not a float literal."s);
        return;
      }

      std::string periodName = j["period"].get<std::string>();
      if(!intDict.contains(periodName)) {
        SysError::setError("DerivedPosMovingSphereAvtFtry config for period: "s + periodName + " is not a int64_t literal."s);
        return;
      }

      std::string componentName = j["component"].get<std::string>();
      if(!intDict.contains(componentName)) {
        SysError::setError("DerivedPosMovingSphereAvtFtry config for period: "s + periodName + " is not a int64_t literal."s);
        return;
      }

      std::shared_ptr<Entity> ent = entityRsrc.get("Entity."s + entityName);
      float min = floatDict.get(minName);
      float max = floatDict.get(maxName);
      int64_t period = intDict.get(periodName);
      int64_t component = intDict.get(componentName);
      uint64_t positionIdx = dict.get(positionIdxName);
      uint64_t radiusIdx = dict.get(radiusIdxName);
      auto dpmsa = dpmsavtStore.get("DerivedPosMovingSphereAvtFtry."s + name);

      dpmsa->setupEntity(ent, positionIdx, radiusIdx);
      dpmsa->setRange(min, max);
      dpmsa->setPeriod(period);
      dpmsa->setComponent(component);

      auto listsCfg = j["lists"];
      for (auto& listCfg : listsCfg.items()) {
        if (!listCfg.value().is_string()) {
          SysError::setError("DerivedPosMovingSphereAvtFtry " + name + " config for lists must contain strings. But is "s + listCfg.value().type_name());
          return;
        }
        auto list = listStore.get("List." + listCfg.key());
        auto ticket = list->push_front(dpmsa);
        ent->addTicket(dict.get(listCfg.value().get<std::string>()), ticket);
      }
      dpmsavtStore.remove("DerivedPosMovingSphereAvt."s + name);
    } else {
      SysError::setError("DerivedPosMovingSphereAvtFtry config for "s + name + " not found."s);
    }
  }

private:
  RsrcDictionary<float>& floatDict = RsrcDictionary<float>::getInstance();
  RsrcDictionary<int64_t>& intDict = RsrcDictionary<int64_t>::getInstance();
  NameRsrcDictionary &dict                                       = NameRsrcDictionary::getInstance();
  RsrcStore<nlohmann::json> &configRsrc                          = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<DerivedPosMovingSphereAvt>& dpmsavtStore                   = RsrcStore<DerivedPosMovingSphereAvt>::getInstance();
  RsrcStore<Entity>& entityRsrc                                  = RsrcStore<Entity>::getInstance();
  RsrcStore<TicketedForwardList<MAvatar<MovingSphere> > >& listStore = RsrcStore<TicketedForwardList<MAvatar<MovingSphere> > >::getInstance();
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
