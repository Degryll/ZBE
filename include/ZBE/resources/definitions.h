/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MultiSpriteSheet.h
 * @since 2018-04-10
 * @date 2018-04-10
 * @author Degryll Ludo Batis
 * @brief Tool capable of generate a sprite from a AnimatedSprite.
 */

#ifndef ZBE_RESOURCES_DEFINITIONS_H_
#define ZBE_RESOURCES_DEFINITIONS_H_

#include "ZBE/core/tools/math/objects.h"
#include "ZBE/core/tools/math/Region.h"
#include "ZBE/core/tools/math/Vector.h"

namespace zbe {

const Vector2D DFLT_SCALE = {1.0, 1.0};
const Vector2D DFLT_OFFSET = {0.0, 0.0};

/** \brief Definition of graphical data asociated to an image.
 */
struct ZBEAPI ImgDef {

  ImgDef(uint64_t imgSrcId, uint64_t frameTime, unsigned frameAmount, Region2D region, Vector2D regionOffset, Region2D texCoord, Vector2D texCoordOffset)
    : imgSrcId(imgSrcId),
      frameTime(frameTime),
      frameAmount(frameAmount),
      region(region),
      regionOffset(regionOffset),
      texCoord(texCoord),
      texCoordOffset(texCoordOffset) {}


  ImgDef(uint64_t imgSrcId = 0) : imgSrcId(imgSrcId), frameTime(SECOND), frameAmount(1), region({0.0,0.0}, {1.0,1.0}), regionOffset({0.0,0.0}), texCoord({0.0,0.0}, {0.0,0.0}), texCoordOffset({0.0,0.0}) {}

  uint64_t imgSrcId;
  uint64_t frameTime;
  unsigned frameAmount;
  Region2D region;
  Vector2D regionOffset;
  Region2D texCoord;
  Vector2D texCoordOffset;

};

/** \brief Definition of a partial sprite.
 */
struct ZBEAPI SprtDef {

    SprtDef(ImgDef img = 0, Vector2D drawOffset = DFLT_OFFSET, Vector2D scale = DFLT_SCALE)
      : img(img), drawOffset(drawOffset), scale(scale) {}

    ImgDef img;
    Vector2D drawOffset;
    Vector2D scale;

};

}  // namespace zbe

#endif  // ZBE_RESOURCES_DEFINITIONS_H_
