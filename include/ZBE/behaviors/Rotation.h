/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Rotation.h
 * @since 2017-01-13
 * @date 2017-05-10
 * @author Degryll Ludo
 * @brief Implements an uniform linear motion behavior.
 */

#ifndef ZBE_BEHAVIORS_ROTATION_H_
#define ZBE_BEHAVIORS_ROTATION_H_

#include <memory>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/tools/math/math.h"
//#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/Parametric.h"
#include "ZBE/core/entities/avatars/Avatar.h"

#include "ZBE/core/system/system.h"

#include "ZBE/factories/Factory.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace zbe {

class LimitedExcentricalRotation3D : virtual public Behavior<float, float, Vector3D,Vector3D, Vector3D, Vector3D>, public Parametric<float> {
   public:
    /** \brief Default constructor.
     */
    LimitedExcentricalRotation3D() = default;

    /** \brief Virtual destructor.
     */
    ~LimitedExcentricalRotation3D() = default;

    void set(float offset) {
      this->radians = offset * sensibility;
    }

    void setSensibility(float sensibility) {
      this->sensibility = sensibility;
    }

    /** \brief Makes the entity move in a straight line
     */
    void apply(std::shared_ptr<MAvatar<float, float, Vector3D, Vector3D, Vector3D, Vector3D> > avatar) {
      auto vvpos = avatar->get<1, Vector3D>();
      auto vvexc = avatar->get<2, Vector3D>();
      auto vvrot = avatar->get<3, Vector3D>();
      auto vvzero = avatar->get<4, Vector3D>();

      auto vfmin = avatar->get<5, float>();
      auto vfmax = avatar->get<6, float>();
      
      auto vpos = vvpos->get();
      auto vexc = vvexc->get();
      auto vrot = vvrot->get();
      auto vzero = vvzero->get();

      float min = vfmin->get();
      float max = vfmax->get();
      
      vpos = vpos - vexc;
      vrot.normalize();
      glm::vec3 rot{vrot.x, vrot.y, vrot.z};
      glm::vec3 pos(vpos.x, vpos.y, vpos.z);

      Vector3D vab = normalize(vpos);
      Vector3D vac =  vzero.normalize();

      glm::vec3 ab(vab.x, vab.y, vab.z);
      glm::vec3 ac(vac.x, vac.y, vac.z);

      float current = glm::orientedAngle(ab, ac, ab);

      float finalRadians = radians;

      if(current + radians > max) {
        finalRadians = max - current;
      } else if(current + radians < min) {
        finalRadians = min - current;
      }

      pos = glm::rotate(pos, finalRadians, rot);

      avatar->set<1, Vector3D>(Vector3D{pos.x + vexc.x, pos.y + vexc.y, pos.z + vexc.z});
    }

  private:
    float radians;
    float sensibility;
};

class LimitedExcentricalRotation3DFtry : virtual public Factory {
public:
  /** \brief Builds a Rotation2D.
   *  \param name Name for the created Rotation2D.
   *  \param cfgId Rotation2D's configuration id.
   */
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<LimitedExcentricalRotation3D> er3d = std::shared_ptr<LimitedExcentricalRotation3D>(new LimitedExcentricalRotation3D);
    behaviorStore.insert("Behavior."s + name, er3d);
    rot3DStore.insert("LimitedExcentricalRotation3D."s + name, er3d);
    pmtStore.insert("Parametric."s + name, er3d);
  }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configStore.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      if (!j["sensibility"].is_string()) {
        SysError::setError("LimitedExcentricalRotation3D config for sensibility: must be a literal sensibility name."s);
        return;
      }

      std::string sensibilityName = j["sensibility"].get<std::string>();
      if(!floatDict.contains(sensibilityName)) {
        SysError::setError("LimitedExcentricalRotation3D config for sensibility: "s + sensibilityName + " is not a sensibility name."s);
        return;
      }
      
      auto rot3D = rot3DStore.get("LimitedExcentricalRotation3D."s + name);
      float sensibility = floatDict.get(sensibilityName);
      rot3D->setSensibility(sensibility);

    } else {
      SysError::setError("LimitedExcentricalRotation3D config for "s + name + " not found."s);
    }

  }

private:

  RsrcStore<nlohmann::json>& configStore = RsrcStore<nlohmann::json>::getInstance();
  RsrcDictionary<float>& floatDict = RsrcDictionary<float>::getInstance();
  RsrcDictionary<Vector3D>& vect3DDict = RsrcDictionary<Vector3D>::getInstance();
  RsrcStore<Behavior<float, float, Vector3D, Vector3D, Vector3D, Vector3D> >& behaviorStore = RsrcStore<Behavior<float, float, Vector3D, Vector3D, Vector3D, Vector3D> >::getInstance();
  RsrcStore<LimitedExcentricalRotation3D>& rot3DStore = RsrcStore<LimitedExcentricalRotation3D>::getInstance();
  RsrcStore<Parametric<float> >& pmtStore = RsrcStore<Parametric<float> >::getInstance();
};


class ExcentricalRotation3D : virtual public Behavior<Vector3D,Vector3D, Vector3D>, public Parametric<float> {
   public:
    /** \brief Default constructor.
     */
    ExcentricalRotation3D() = default;

    /** \brief Virtual destructor.
     */
    ~ExcentricalRotation3D() = default;

    void set(float offset) {
      this->radians = offset * sensibility;
    }

    void setSensibility(float sensibility) {
      this->sensibility = sensibility;
    }

    /** \brief Makes the entity move in a straight line
     */
    void apply(std::shared_ptr<MAvatar<Vector3D, Vector3D, Vector3D > > avatar) {
      auto vvpos = avatar->get<1, Vector3D>();
      auto vvexc = avatar->get<2, Vector3D>();
      auto vvrot = avatar->get<3, Vector3D>();
      
      auto vpos = vvpos->get();
      auto vexc = vvexc->get();
      auto vrot = vvrot->get();
      vpos = vpos - vexc;

      vrot.normalize();
      glm::vec3 rot{vrot.x, vrot.y, vrot.z};   
      glm::vec3 pos(vpos.x, vpos.y, vpos.z);
      pos = glm::rotate(pos, radians, rot);
      avatar->set<1, Vector3D>(Vector3D{pos.x + vexc.x, pos.y + vexc.y, pos.z + vexc.z});
    }

  private:
    float radians;
    float sensibility;
};

class ExcentricalRotation3DFtry : virtual public Factory {
public:
  /** \brief Builds a Rotation2D.
   *  \param name Name for the created Rotation2D.
   *  \param cfgId Rotation2D's configuration id.
   */
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<ExcentricalRotation3D> er3d = std::shared_ptr<ExcentricalRotation3D>(new ExcentricalRotation3D);
    behaviorStore.insert("Behavior."s + name, er3d);
    rot3DStore.insert("ExcentricalRotation3D."s + name, er3d);
    pmtStore.insert("Parametric."s + name, er3d);
  }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configStore.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      if (!j["sensibility"].is_string()) {
        SysError::setError("ExcentricalRotation3D config for sensibility: must be a literal sensibility name."s);
        return;
      }

      std::string sensibilityName = j["sensibility"].get<std::string>();
      if(!floatDict.contains(sensibilityName)) {
        SysError::setError("ExcentricalRotation3D config for sensibility: "s + sensibilityName + " is not a sensibility name."s);
        return;
      }
      
      auto rot3D = rot3DStore.get("ExcentricalRotation3D."s + name);
      float sensibility = floatDict.get(sensibilityName);
      rot3D->setSensibility(sensibility);

    } else {
      SysError::setError("ExcentricalRotation3D config for "s + name + " not found."s);
    }

  }

private:

  RsrcStore<nlohmann::json>& configStore = RsrcStore<nlohmann::json>::getInstance();
  RsrcDictionary<float>& floatDict = RsrcDictionary<float>::getInstance();
  RsrcDictionary<Vector3D>& vect3DDict = RsrcDictionary<Vector3D>::getInstance();
  RsrcStore<Behavior<Vector3D, Vector3D, Vector3D> >& behaviorStore = RsrcStore<Behavior<Vector3D, Vector3D, Vector3D> >::getInstance();
  RsrcStore<ExcentricalRotation3D>& rot3DStore = RsrcStore<ExcentricalRotation3D>::getInstance();
  RsrcStore<Parametric<float> >& pmtStore = RsrcStore<Parametric<float> >::getInstance();
};

/** \brief Define the minimal functions of every behavior.
 */
class Rotation3D : virtual public Behavior<Vector3D, Vector3D>, public Parametric<float> {
  public:
    /** \brief Default constructor.
     */
    Rotation3D() = default;

    /** \brief Virtual destructor.
     */
    ~Rotation3D() = default;

    void set(float offset) {
      this->radians = offset * sensibility;
    }

    void setSensibility(float sensibility) {
      this->sensibility = sensibility;
    }

    /** \brief Makes the entity move in a straight line
     */
    void apply(std::shared_ptr<MAvatar<Vector3D, Vector3D > > avatar) {
      auto vpos = avatar->get<1, Vector3D>();
      auto vrot = avatar->get<2, Vector3D>();

      glm::vec3 pos(vpos->get().x, vpos->get().y, vpos->get().z);
      glm::vec3 rot(vrot->get().x, vrot->get().y, vrot->get().z);

      pos = glm::rotate(pos, radians, rot);
      avatar->set<1, Vector3D>(Vector3D{pos.x, pos.y, pos.z});
    }

  private:
    float radians;
    float sensibility;
};

/** \brief Factory for Rotation2DFtry.
 */
class Rotation3DFtry : virtual public Factory {
public:
  /** \brief Builds a Rotation2D.
   *  \param name Name for the created Rotation2D.
   *  \param cfgId Rotation2D's configuration id.
   */
  void create(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    std::shared_ptr<Rotation3D> rot3D = std::shared_ptr<Rotation3D>(new Rotation3D);
    behaviorStore.insert("Behavior."s + name, rot3D);
    rot3DStore.insert("Rotation3D."s + name, rot3D);
    pmtStore.insert("Parametric."s + name, rot3D);
  }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configStore.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      if (!j["sensibility"].is_string()) {
        SysError::setError("Rotation3DFtry config for sensibility: must be a literal sensibility name."s);
        return;
      }

      std::string sensibilityName = j["sensibility"].get<std::string>();
      if(!floatDict.contains(sensibilityName)) {
        SysError::setError("Rotation3DFtry config for sensibility: "s + sensibilityName + " is not a sensibility name."s);
        return;
      }
      float sensibility = floatDict.get(sensibilityName);
      auto rot3D = rot3DStore.get("Rotation3D."s + name);
      rot3D->setSensibility(sensibility);

    } else {
      SysError::setError("Rotation3DFtry config for "s + name + " not found."s);
    }

  }

private:

  RsrcStore<nlohmann::json>& configStore = RsrcStore<nlohmann::json>::getInstance();
  RsrcDictionary<float>& floatDict = RsrcDictionary<float>::getInstance();
  RsrcStore<Behavior<Vector3D, Vector3D> >& behaviorStore = RsrcStore<Behavior<Vector3D, Vector3D> >::getInstance();
  RsrcStore<Rotation3D>& rot3DStore = RsrcStore<Rotation3D>::getInstance();
  RsrcStore<Parametric<float> >& pmtStore = RsrcStore<Parametric<float> >::getInstance();
};

}  // namespace zbe

#endif  // ZBE_BEHAVIORS_ROTATION_H_
