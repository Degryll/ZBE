/**
 * Copyright 2012 Batis Degryll Ludo
 * @file UniformLinearMotion.h
 * @since 2017-01-13
 * @date 2017-05-10
 * @author Degryll Ludo
 * @brief Implements an uniform linear motion behavior.
 */

#ifndef ZBE_BEHAVIORS_UNIFORMLINEARMOTION_H_
#define ZBE_BEHAVIORS_UNIFORMLINEARMOTION_H_

#include <nlohmann/json.hpp>

#include <memory>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/tools/math/math.h"
//#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/system/SysTime.h"

#include "ZBE/core/system/system.h"

#include "ZBE/factories/Factory.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"

namespace zbe {
/*TODO make this a template.
template<unsigned s>
class UniformLinearMotion : virtual public Behavior<Vector<s>, Vector<s> > { ... }
We have tried this but:
"void apply(std::shared_ptr<MAvatar<Vector<s>, Vector<s> > > avatar) {
  std::shared_ptr<Vector<s> > p = avatar->get<1, Vector<s> >();
  ..."
Throw an error in this line:
std::shared_ptr<Vector<s> > p = avatar->get<1, Vector<s> >();
*/

/** \brief Define the minimal functions of every behavior.
 */
class UniformLinearMotion2D : virtual public Behavior<Vector<2>, Vector<2> > {
  public:

    /** \brief Virtual destructor.
     */
    virtual ~UniformLinearMotion2D() = default;

    /** \brief Makes the entity move in a straight line
     */
    void apply(std::shared_ptr<MAvatar<Vector<2>, Vector<2> > > avatar) {
      auto vvel = AvtUtil::get<1, Vector<2> >(avatar);
      auto vpos = AvtUtil::get<2, Vector<2> >(avatar);
      auto contextTime = avatar->getContextTime();
      vpos->set(vpos->get() + (vvel->get() * contextTime->getCurrentTime()) * zbe::INVERSE_SECOND);
    }

};

/** \brief Define the minimal functions of every behavior.
 */
class UniformLinearMotion3D : virtual public Behavior<Vector3D, Vector3D > {
  public:

    /** \brief Virtual destructor.
     */
    virtual ~UniformLinearMotion3D() = default;

    /** \brief Makes the entity move in a straight line
     */
    void apply(std::shared_ptr<MAvatar<Vector3D, Vector3D > > avatar) {
      auto vpos = avatar->get<1, Vector3D>();
      auto vvel = avatar->get<2, Vector3D>();
      auto contextTime = avatar->getContextTime();
      vpos->set(vpos->get() + (vvel->get() * contextTime->getCurrentTime()) * zbe::INVERSE_SECOND);
    }
};


/** \brief Define the minimal functions of every behavior.
 */
class RelativeUniformLinearMotion3D : virtual public Behavior<Vector3D, Vector3D, Vector3D > {
  public:
    /** \brief Virtual destructor.
     */
    virtual ~RelativeUniformLinearMotion3D() = default;

    void setVelocity(Vector3D velocity) {
      vel = velocity;
    }

    void apply(std::shared_ptr<MAvatar<Vector3D, Vector3D, Vector3D > > avatar) {
      auto vpos = avatar->get<1, Vector3D>();
      auto vdir = avatar->get<2, Vector3D>();
      auto vup = avatar->get<3, Vector3D>();
      auto nx = cross(vdir->get(), vup->get());

      Vector3D vx = nx * vel[0];
      Vector3D vy = vup->get() * vel[1];
      Vector3D vz = vdir->get() * vel[2];

      Vector3D v = vx + vy + vz;

      auto contextTime = avatar->getContextTime();

      avatar->set<1, Vector3D>(vpos->get() + (v * contextTime->getCurrentTime()) * zbe::INVERSE_SECOND);
    }

  private:
    Vector3D vel;
};


/** \brief Define the minimal functions of every behavior.
 */
class FixedUniformLinearMotion3D : virtual public Behavior<Vector3D > {
public:
  /** \brief Virtual destructor.
   */
  virtual ~FixedUniformLinearMotion3D() = default;

  void setVelocity(Vector3D vvel) {
    this->vvel = vvel;
  }

  /** \brief Makes the entity move in a straight line
   */
  void apply(std::shared_ptr<MAvatar<Vector3D> > avatar) {
    auto vpos = avatar->get<1, Vector3D>();
    //vpos->set(vpos->get() + (vvel * contextTime->getCurrentTime()) * zbe::INVERSE_SECOND);
    auto contextTime = avatar->getContextTime();
    avatar->set<1, Vector3D>(vpos->get() + (vvel * contextTime->getCurrentTime()) * zbe::INVERSE_SECOND);
  }

private:
  Vector3D vvel;
};

class UniformLinearMotion2DOnPlane : virtual public Behavior<Vector2D, Vector2D, Vector3D, Vector3D, Vector3D, Vector3D, Vector3D> {
public:
  virtual ~UniformLinearMotion2DOnPlane() = default;

  void apply(std::shared_ptr<MAvatar<Vector2D, Vector2D, Vector3D, Vector3D, Vector3D, Vector3D, Vector3D> > avatar) {
    auto contextTime = avatar->getContextTime();
    auto vplanePos = avatar->get<1, Vector3D>();
    // El avatar usado en el sistema de fisicas para generar el MovingTriangle3D debe actualizar en la entidad dos Values<Vector3D>
    // Esto vectores representan estos E1 y E2 que vienen a continuación. Estos son los vectores 0,1 y 1,0 del sistema de coordenadas del plano.
    // https://math.stackexchange.com/questions/3007739/transformation-matrix-between-a-2d-and-a-3d-coordinate-system
    auto vplaneE1 = avatar->get<2, Vector3D>();
    auto vplaneE2 = avatar->get<3, Vector3D>();

    auto vpos3D = avatar->get<4, Vector3D>();
    //auto vvel3D = avatar->get<5, Vector3D>();

    auto vpos2D = avatar->get<6, Vector2D>();
    auto vvel2D = avatar->get<7, Vector2D>();

    auto planePos = vplanePos->get();
    auto planeE1 = vplaneE1->get();
    auto planeE2 = vplaneE2->get();

    auto pos3D = vpos3D->get();
    //auto vel3D = vvel3D->get();

    auto pos2D = vpos2D->get();
    auto vel2D = vvel2D->get();

    Vector2D newPos2D = pos2D + (vel2D * (contextTime->getCurrentTime() * zbe::INVERSE_SECOND));
    Vector3D newPos3D = planePos + (planeE1 * newPos2D.x + planeE2 * newPos2D.y);
    //Vector3D newPos3D = planePos + (Matrix(vplaneE1,vplaneE2) * newPos2D);
    // TODO esto es una teoria.
    Vector3D newVel3D = (planeE1 * vel2D.x + planeE2 * vel2D.y);
    
    avatar->set<4, Vector3D>(newPos3D);
    avatar->set<5, Vector3D>(newVel3D);
    avatar->set<6, Vector2D>(newPos2D);
  }
};


/** \brief Factory for FixedUniformLinearMotion3DFtry.
 */
class FixedUniformLinearMotion3DFtry : virtual public Factory {
public:
  /** \brief Builds a FixedUniformLinearMotion3D.
   *  \param name Name for the created FixedUniformLinearMotion3D.
   *  \param cfgId FixedUniformLinearMotion3D's configuration id.
   */
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<FixedUniformLinearMotion3D> fulm3d = std::shared_ptr<FixedUniformLinearMotion3D>(new FixedUniformLinearMotion3D);
    behaviorRsrc.insert("Behavior."s + name, fulm3d);
    fulm3dRsrc.insert("FixedUniformLinearMotion3D."s + name, fulm3d);
  }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      if (!j["velocity"].is_string()) {
        SysError::setError("FixedUniformLinearMotion3DFtry config for velocity: "s + j["velocity"].get<std::string>() + ": must be a literal vector name."s);
        return;
      }

      std::string velocityName = j["velocity"].get<std::string>();
      if(!vecStore.contains(velocityName)) {
        SysError::setError("FixedUniformLinearMotion3DFtry config for velocity: "s + velocityName + " is not a vector literal."s);
        return;
      }

      auto vel = vecStore.get(velocityName);
      auto fulm3d = fulm3dRsrc.get("FixedUniformLinearMotion3D."s + name);

      fulm3d->setVelocity(vel);

    } else {
      SysError::setError("FixedUniformLinearMotion3DFtry config for "s + name + " not found."s);
    }

  }

private:

  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcDictionary<Vector3D>& vecStore = RsrcDictionary<Vector3D>::getInstance();
  RsrcStore<Behavior<Vector3D> >& behaviorRsrc = RsrcStore<Behavior<Vector3D> >::getInstance();
  RsrcStore<FixedUniformLinearMotion3D>& fulm3dRsrc = RsrcStore<FixedUniformLinearMotion3D>::getInstance();
};


class RelativeUniformLinearMotion3DFtry : virtual public Factory {
public:

  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<RelativeUniformLinearMotion3D> rulm3d = std::shared_ptr<RelativeUniformLinearMotion3D>(new RelativeUniformLinearMotion3D);
    behaviorRsrc.insert("Behavior."s + name, rulm3d);
    rulm3dRsrc.insert("RelativeUniformLinearMotion3D."s + name, rulm3d);
  }

  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      if (!j["velocity"].is_string()) {
        SysError::setError("RelativeUniformLinearMotion3DFtry config for velocity: "s + j["velocity"].get<std::string>() + ": must be a literal vector name."s);
        return;
      }

      std::string velocityName = j["velocity"].get<std::string>();
      if(!vecStore.contains(velocityName)) {
        SysError::setError("RelativeUniformLinearMotion3DFtry config for velocity: "s + velocityName + " is not a vector literal."s);
        return;
      }

      auto vel = vecStore.get(velocityName);
      auto rulm3d = rulm3dRsrc.get("RelativeUniformLinearMotion3D."s + name);

      rulm3d->setVelocity(vel);

    } else {
      SysError::setError("RelativeUniformLinearMotion3DFtry config for "s + name + " not found."s);
    }

  }

private:

  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcDictionary<Vector3D>& vecStore = RsrcDictionary<Vector3D>::getInstance();
  RsrcStore<Behavior<Vector3D, Vector3D, Vector3D> >& behaviorRsrc = RsrcStore<Behavior<Vector3D, Vector3D, Vector3D> >::getInstance();
  RsrcStore<RelativeUniformLinearMotion3D>& rulm3dRsrc = RsrcStore<RelativeUniformLinearMotion3D>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_BEHAVIORS_UNIFORMLINEARMOTION_H_
