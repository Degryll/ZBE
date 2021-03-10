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
#include "ZBE/core/system/SysTime.h"

#include "ZBE/core/system/system.h"

#include "ZBE/factories/Factory.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>



namespace zbe {

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
        SysError::setError("Rotation3DFtry config for contextTime: "s + sensibilityName + " is not a context time name."s);
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
