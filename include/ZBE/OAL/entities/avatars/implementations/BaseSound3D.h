/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseSound3D.h
 * @since 2018-08-22
 * @date 2018-08-22
 * @author Batis Degryll Ludo
 * @brief This defines an avatar that produces sound.
 */

#ifndef ZBE_OAL_ENTITIES_AVATARS_BASESOUND3D_H_
#define ZBE_OAL_ENTITIES_AVATARS_BASESOUND3D_H_

#include <cstdint>
#include <AL/al.h>
#include <AL/alc.h>

#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/core/entities/Entity.h"

#include "ZBE/OAL/entities/avatars/Sound3D.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief This defines an avatar that produces sound.
 */
class BaseSound3D : public Sound3D {
public:
  using Base = void;//!< inheritance info

  enum State { NEW = 0, PLAYING = 1, END = 2};

  BaseSound3D(const BaseSound3D&) = delete;
  void operator=(const BaseSound3D&) = delete;

  BaseSound3D(EntityIds<3> point, EntityIds<3> velocity, EntityIds<1> ticket, uint64_t audioId) : Sound3D(audioId), p(point), v(velocity), t(ticket) {}

  /** \brief Virtual destructor.
   */
  virtual ~BaseSound3D() {}

  /** \brief Getter for the position.
  *  \return Emisor position.
  */
  Point3D getPosition() {
    double x = p.e->getDouble(p.ids[0])->get();
    double y = p.e->getDouble(p.ids[1])->get();
    double z = p.e->getDouble(p.ids[2])->get();
    return Point3D({x, y, z});
  }

  /** \brief Getter for the velocity.
  *  \return Emisor velocity.
  */
  Vector3D getVelocity() {
    double x = v.e->getDouble(v.ids[0])->get();
    double y = v.e->getDouble(v.ids[1])->get();
    double z = v.e->getDouble(v.ids[2])->get();
    return Vector3D({x, y, z});
  }

  /** \brief Tells if current sound is playing
  */
  virtual void stop() {
    setState(STOPPED);
    t.e->setERASED(t.ids[0]);
  }

private:
  EntityIds<3> p;
  EntityIds<3> v;
  EntityIds<1> t;
};

}  // namespace zbe

#endif  // ZBE_OAL_ENTITIES_AVATARS_BASESOUND3D_H_
