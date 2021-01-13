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

#include <memory>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/tools/math/math.h"
//#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/system/SysTime.h"

#include "ZBE/core/system/system.h"

#include "ZBE/factories/Factory.h"

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
    UniformLinearMotion2D(const UniformLinearMotion2D&) = delete;
    void operator=(const UniformLinearMotion2D&) = delete;

    /** \brief Default constructor.
     */
    UniformLinearMotion2D() : contextTime(zbe::SysTime::getInstance()) {}

    /** \brief Virtual destructor.
     */
    virtual ~UniformLinearMotion2D() {}

    void setContextTime(std::shared_ptr<ContextTime> contextTime) {
      this->contextTime = contextTime;
    }

    /** \brief Makes the entity move in a straight line
     */
    void apply(std::shared_ptr<MAvatar<Vector<2>, Vector<2> > > avatar) {
      auto vvel = AvtUtil::get<1, Vector<2> >(avatar);
      auto vpos = AvtUtil::get<2, Vector<2> >(avatar);
      vpos->set(vpos->get() + (vvel->get() * contextTime->getCurrentTime()) * zbe::INVERSE_SECOND);
    }

  private:
    std::shared_ptr<ContextTime> contextTime;
};

/** \brief Define the minimal functions of every behavior.
 */
class UniformLinearMotion3D : virtual public Behavior<Vector3D, Vector3D > {
  public:
    UniformLinearMotion3D(const UniformLinearMotion3D&) = delete;
    void operator=(const UniformLinearMotion3D&) = delete;

    /** \brief Default constructor.
     */
    UniformLinearMotion3D() : contextTime(zbe::SysTime::getInstance()) {}

    /** \brief Virtual destructor.
     */
    virtual ~UniformLinearMotion3D() {}

    void setContextTime(std::shared_ptr<ContextTime> contextTime) {
      this->contextTime = contextTime;
    }

    /** \brief Makes the entity move in a straight line
     */
    void apply(std::shared_ptr<MAvatar<Vector3D, Vector3D > > avatar) {
      auto vpos = avatar->get<1, Vector3D>();
      auto vvel = avatar->get<2, Vector3D>();
      vpos->set(vpos->get() + (vvel->get() * contextTime->getCurrentTime()) * zbe::INVERSE_SECOND);
    }

  private:
    std::shared_ptr<ContextTime> contextTime;
};

/** \brief Define the minimal functions of every behavior.
 */
class FixedUniformLinearMotion3D : virtual public Behavior<Vector3D > {
public:

  FixedUniformLinearMotion3D(const FixedUniformLinearMotion3D&) = delete;
  void operator=(const FixedUniformLinearMotion3D&) = delete;

  /** \brief Default constructor.
   */
  FixedUniformLinearMotion3D() : contextTime(nullptr), vvel() {}

  /** \brief Virtual destructor.
   */
  virtual ~FixedUniformLinearMotion3D() = default;

  void setVelocity(Vector3D vvel) {
    this->vvel = vvel;
  }

  void setContextTime(std::shared_ptr<ContextTime> contextTime) {
    this->contextTime = contextTime;
  }

  /** \brief Makes the entity move in a straight line
   */
  void apply(std::shared_ptr<MAvatar<Vector3D> > avatar) {
    auto vpos = avatar->get<1, Vector3D>();
    vpos->set(vpos->get() + (vvel * contextTime->getCurrentTime()) * zbe::INVERSE_SECOND);
  }

private:
  std::shared_ptr<ContextTime> contextTime;
  Vector3D vvel;
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
      if (!j["contextTime"].is_string()) {
        SysError::setError("FixedUniformLinearMotion3DFtry config for contextTime: "s + j["limit"].get<std::string>() + ": must be a literal context time name."s);
        return;
      }

      std::string velocityName = j["velocity"].get<std::string>();
      if(!vecStore.contains(velocityName)) {
        SysError::setError("FixedUniformLinearMotion3DFtry config for velocity: "s + velocityName + " is not a vector literal."s);
        return;
      }

      std::string cTimeName = j["contextTime"].get<std::string>();
      if(!cTimeRsrc.contains("ContextTime."s + cTimeName)) {
        SysError::setError("FixedUniformLinearMotion3DFtry config for contextTime: "s + cTimeName + " is not a context time name."s);
        return;
      }

      auto vel = vecStore.get(velocityName);
      std::shared_ptr<ContextTime> cTime = cTimeRsrc.get("ContextTime."s + cTimeName);
      auto fulm3d = fulm3dRsrc.get("FixedUniformLinearMotion3D."s + name);

      fulm3d->setVelocity(vel);
      fulm3d->setContextTime(cTime);

    } else {
      SysError::setError("FixedUniformLinearMotion3DFtry config for "s + name + " not found."s);
    }

  }

private:

  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcDictionary<Vector3D>& vecStore = RsrcDictionary<Vector3D>::getInstance();
  RsrcStore<ContextTime>& cTimeRsrc = RsrcStore<ContextTime>::getInstance();
  RsrcStore<Behavior<Vector3D> >& behaviorRsrc = RsrcStore<Behavior<Vector3D> >::getInstance();
  RsrcStore<FixedUniformLinearMotion3D>& fulm3dRsrc = RsrcStore<FixedUniformLinearMotion3D>::getInstance();
};

/** \brief Factory for UniformLinearMotion3DFtry.
 */
class ZBEAPI UniformLinearMotion3DFtry : virtual public Factory {
public:
  /** \brief Builds a UniformLinearMotion3D.
   *  \param name Name for the created UniformLinearMotion3D.
   *  \param cfgId UniformLinearMotion3D's configuration id.
   */
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<FixedUniformLinearMotion3D> fulm3d = std::shared_ptr<FixedUniformLinearMotion3D>(new FixedUniformLinearMotion3D);
    behaviorRsrc.insert("Behavior."s + name, fulm3d);
    fulm3dRsrc.insert("UniformLinearMotion3D."s + name, fulm3d);
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
      if (!j["contextTime"].is_string()) {
        SysError::setError("UniformLinearMotion3DFtry config for contextTime: "s + j["limit"].get<std::string>() + ": must be a literal context time name."s);
        return;
      }

      std::string cTimeName = j["contextTime"].get<std::string>();
      if(!cTimeRsrc.contains("ContextTime."s + cTimeName)) {
        SysError::setError("UniformLinearMotion3DFtry config for contextTime: "s + cTimeName + " is not a context time name."s);
        return;
      }
      std::shared_ptr<ContextTime> cTime = cTimeRsrc.get("ContextTime."s + cTimeName);
      auto ulm3d = fulm3dRsrc.get("UniformLinearMotion3D."s + name);
      ulm3d->setContextTime(cTime);

    } else {
      SysError::setError("UniformLinearMotion3DFtry config for "s + name + " not found."s);
    }

  }

private:

  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcDictionary<Vector3D>& vecStore = RsrcDictionary<Vector3D>::getInstance();
  RsrcStore<ContextTime>& cTimeRsrc = RsrcStore<ContextTime>::getInstance();
  RsrcStore<Behavior<Vector3D> >& behaviorRsrc = RsrcStore<Behavior<Vector3D> >::getInstance();
  RsrcStore<FixedUniformLinearMotion3D>& fulm3dRsrc = RsrcStore<FixedUniformLinearMotion3D>::getInstance();
};

/** \brief Factory for UniformLinearMotion2DFtry.
 */
class ZBEAPI UniformLinearMotion2DFtry : virtual public Factory {
public:
  /** \brief Builds a UniformLinearMotion2D.
   *  \param name Name for the created UniformLinearMotion2D.
   *  \param cfgId UniformLinearMotion2D's configuration id.
   */
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<UniformLinearMotion2D> ulm3d = std::shared_ptr<UniformLinearMotion2D>(new UniformLinearMotion2D);
    behaviorRsrc.insert("Behavior."s + name, ulm3d);
    ulm2dRsrc.insert("UniformLinearMotion2D."s + name, ulm3d);
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
      if (!j["contextTime"].is_string()) {
        SysError::setError("UniformLinearMotion2DFtry config for contextTime: "s + j["limit"].get<std::string>() + ": must be a literal context time name."s);
        return;
      }

      std::string cTimeName = j["contextTime"].get<std::string>();
      if(!cTimeRsrc.contains("ContextTime."s + cTimeName)) {
        SysError::setError("UniformLinearMotion2DFtry config for contextTime: "s + cTimeName + " is not a context time name."s);
        return;
      }
      std::shared_ptr<ContextTime> cTime = cTimeRsrc.get("ContextTime."s + cTimeName);
      auto ulm3d = ulm2dRsrc.get("UniformLinearMotion2D."s + name);
      ulm3d->setContextTime(cTime);

    } else {
      SysError::setError("UniformLinearMotion2DFtry config for "s + name + " not found."s);
    }

  }

private:

  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcDictionary<Vector2D>& vecStore = RsrcDictionary<Vector2D>::getInstance();
  RsrcStore<ContextTime>& cTimeRsrc = RsrcStore<ContextTime>::getInstance();
  RsrcStore<Behavior<Vector2D, Vector2D> >& behaviorRsrc = RsrcStore<Behavior<Vector2D, Vector2D> >::getInstance();
  RsrcStore<UniformLinearMotion2D>& ulm2dRsrc = RsrcStore<UniformLinearMotion2D>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_BEHAVIORS_UNIFORMLINEARMOTION_H_
