/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseMovable2D.h
 * @since 2016-12-17
 * @date 2018-02-25
 * @author Batis
 * @brief Simple implementations of Bounceable avatar interface.
 */

#ifndef ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLEBOUNCEABLE_H_
#define ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLEBOUNCEABLE_H_

#include "ZBE/entities/avatars/Bounceable.h"

namespace zbe {

/** \brief Simple implementations of Bounceable avatar interface.
 */
class SimpleBounceable : public Bounceable{
  public:

    /** \brief Builds this SimpleBounceable with a factor.
     */
    SimpleBounceable(double factor) : factor(factor) {}

    /** \brief Virtual destructor.
     */
    virtual ~SimpleBounceable() {}

    /** \brief Return the bounce factor.
     * \return The bounce factor.
     */
    double getFactor(){return factor;}

  private:
    double factor;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_SIMPLEBOUNCEABLE_H_
