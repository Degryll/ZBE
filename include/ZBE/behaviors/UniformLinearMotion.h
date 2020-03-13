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

//#include "ZBE/entities/avatars/Movable.h"

#include "ZBE/core/system/system.h"

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

}  // namespace zbe

#endif  // ZBE_BEHAVIORS_UNIFORMLINEARMOTION_H_
