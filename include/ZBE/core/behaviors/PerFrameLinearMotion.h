#ifndef CORE_BEHAVIORS_PERFRAMELINEARMOTION_H
#define CORE_BEHAVIORS_PERFRAMELINEARMOTION_H

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/archetypes/Movable.h"

namespace zbe {

template<unsigned s>
/** \brief This behavior does a linear movement by frames, rather than real time.
 */
class PerFrameLinearMotion : public Behavior<Movable<s> > {
  public:
    PerFrameLinearMotion();
    virtual ~PerFrameLinearMotion();

    void apply(Movable<s> * entity);

  protected:
  private:
};

template<unsigned s>
PerFrameLinearMotion<s>::PerFrameLinearMotion() {
  //ctor
}

template<unsigned s>
void PerFrameLinearMotion<s>::apply(Movable<s> * entity){
  Point<s> endPos = entity->getPosition() + entity->getVelocity();
  entity->setPosition(endPos);
}

template<unsigned s>
PerFrameLinearMotion<s>::~PerFrameLinearMotion() {
  //dtor
}

}
#endif // CORE_BEHAVIORS_PERFRAMELINEARMOTION_H
