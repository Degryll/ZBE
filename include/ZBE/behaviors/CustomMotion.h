/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CustomMotion.h
 * @since 2020-04-10
 * @date 2020-04-10
 * @author Degryll
 * @brief Implements a customizable motion behavior.
 */

#ifndef ZBE_BEHAVIORS_CUSTOMMOTION_H_
#define ZBE_BEHAVIORS_CUSTOMMOTION_H_

#include <functional>
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
 template <unsigned s>
class CustomMotion : virtual public Behavior<Vector<s>, Vector<s>, Vector<s> > {
  public:
    CustomMotion(const CustomMotion&) = delete;
    void operator=(const CustomMotion&) = delete;

    /** \brief Default constructor.
     */
    CustomMotion() : contextTime(zbe::SysTime::getInstance()), f() {}

    /** \brief Virtual destructor.
     */
    virtual ~CustomMotion() {}

//    void setFunction(std::function<void(std::shared_ptr<Value<Vector<s> > >, std::shared_ptr<Value<Vector<s> > >, std::shared_ptr<Value<Vector<s> > >, std::shared_ptr<ContextTime> contextTime)> f) {
    void setFunction(std::function<void(double&, double&, double&, double&, double&, double&, double)> f) {
      this->f = f;
    }

    /** \brief Makes the entity move in a straight line
     */
    void apply(std::shared_ptr<MAvatar<Vector<s>, Vector<s>, Vector<s> > > avatar) {
      auto vacl = AvtUtil::get<3, Vector<s> >(avatar);
      auto vvel = AvtUtil::get<2, Vector<s> >(avatar);
      auto vpos = AvtUtil::get<1, Vector<s> >(avatar);
      Vector<s> acel = vacl->get();
      Vector<s> vel = vvel->get();
      Vector<s> pos = vpos->get();
      f(pos.x, pos.y, vel.x, vel.y, acel.x, acel.y, contextTime->getCurrentTime() * zbe::INVERSE_SECOND);
      vacl->set(acel);
      vvel->set(vel);
      vpos->set(pos);
      //vpos->set(vpos->get() + (vvel->get() * contextTime->getCurrentTime()) * zbe::INVERSE_SECOND);
    }

  private:
    std::shared_ptr<ContextTime> contextTime;
//    std::function<void(std::shared_ptr<Value<Vector<s> > >, std::shared_ptr<Value<Vector<s> > >, std::shared_ptr<Value<Vector<s> > >, std::shared_ptr<ContextTime> contextTime)> f;
    std::function<void(double&, double&, double&, double&, double&, double&, double)> f;
};

}  // namespace zbe

#endif  // ZBE_BEHAVIORS_CUSTOMMOTION_H_
