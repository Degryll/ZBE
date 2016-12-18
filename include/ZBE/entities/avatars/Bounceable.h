/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Bounceable.h
 * @since 2016-12-17
 * @date 2016-12-17
 * @author Batis
 * @brief This define an avatar that can bounce.
 */

#ifndef ZBE_ENTITIES_AVATARS_BOUNCEABLE_H_
#define ZBE_ENTITIES_AVATARS_BOUNCEABLE_H_

namespace zbe {

/** \brief This define an avatar that can bounce.
 */
class Bounceable {
  public:
    virtual ~Bounceable(){};
    virtual double getFactor() = 0;
};

}  // namespace zbe

#endif //ZBE_ENTITIES_AVATARS_BOUNCEABLE_H_
