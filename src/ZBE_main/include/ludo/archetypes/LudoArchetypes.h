/**
 * Copyright 2012 Batis Degryll Ludo
 * @file LudoArchetypes.h
 * @since 2017-02-25
 * @date 2017-02-25
 * @author Ludo
 * @brief Archetypes for ludo's proving grounds.
 */

#ifndef ZBE_MAIN_LUDO_LUDOARCHETYPES
#define ZBE_MAIN_LUDO_LUDOARCHETYPES

#include "ZBE/archetypes/Drawable.h"

namespace ludo {

/** \brief This define a Drawable entity with an angle.
 */
class RotatedDrawable : virtual public zbe::Drawable {
  public:
    virtual ~RotatedDrawable() {}

    virtual double getAngle() = 0;
};

/** \brief This define a Drawable entity with modifiable graphgics id
 */
class SetableGraphics {
  public:
    virtual ~SetableGraphics() {}

    virtual void setGraphics(unsigned) = 0;
};

///** \brief This define a Drawable entity with an angle.
// */
//class State {
//  public:
//    virtual ~State() {}
//    virtual uint64_t getState() = 0;
//};

}  // namespace zbe

#endif  // ZBE_MAIN_LUDO_LUDOARCHETYPES
