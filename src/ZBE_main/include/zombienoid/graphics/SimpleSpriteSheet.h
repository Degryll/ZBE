/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SpriteSheet.h
 * @since 2017-06-14
 * @date 2017-06-14
 * @author Degryll Ludo Batis
 * @brief Interface capable of generate a sprite from a given entity.
 */

#ifndef ZOMBIENOID_GRAPHICS_SIMPLESPRITESHEET_H_
#define ZOMBIENOID_GRAPHICS_SIMPLESPRITESHEET_H_

#include <stdint.h>

#include "ZBE/core/tools/graphics/Sprite.h"
#include "ZBE/core/tools/math/Region.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "zombienoid/graphics/SimpleSpriteSheet.h"

namespace zbe {

/** \brief Interface capable of generate a sprite from a given entity.
 */
class SimpleSpriteSheet : public SpriteSheet<AnimatedSprite> {
public:

  /** \brief Parametriced constructor
   *  \param id Id for the SpriteSheet;
   **/
  SimpleSpriteSheet(uint64_t id) : id(id) {}

  /** \brief Generate a sprite from a given entity.
   *  \return generated sprite
   **/
  Sprite generateSprite(AnimatedSprite* a) {
    //Sprite(Region2D src, Region2D dst, double angle, uint64_t graphics)
    Sprite s(Region<2>({0.0,0.0},{(double)a->getW(), (double)a->getH()}),Region<2>({(double)a->getX(), (double)a->getY()}, {(double)a->getW(), (double)a->getH()}), a->getDegrees(), id);
    return s;
  }
private:
  uint64_t id;
};

}  // namespace zbe

#endif  // ZOMBIENOID_GRAPHICS_SIMPLESPRITESHEET_H_
