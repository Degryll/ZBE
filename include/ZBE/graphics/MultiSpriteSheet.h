/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MultiSpriteSheet.h
 * @since 2018-04-10
 * @date 2018-04-10
 * @author Degryll Ludo Batis
 * @brief Tool capable of generate a sprite from a AnimatedSprite.
 */

#ifndef ZBE_GRAPHICS_MULTISPRITESHEET_H_
#define ZBE_GRAPHICS_MULTISPRITESHEET_H_

#include <stdint.h>
#include <vector>

#include "ZBE/core/tools/graphics/SpriteSheet.h"
#include "ZBE/core/tools/graphics/Sprite.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Region.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/avatars/AnimatedSprite.h"

namespace zbe {

/** \brief Definition of graphical data asociated to an image.
 */
struct ImgDef {

  ImgDef(uint64_t imgSrcId, uint64_t frameTime, unsigned frameAmount, zbe::Region2D region, zbe::Vector2D regionOffset)
    : imgSrcId(imgSrcId),
      frameTime(frameTime),
      frameAmount(frameAmount),
      region(region),
      regionOffset(regionOffset) {}

  ImgDef() : imgSrcId(), frameTime(), frameAmount(), region(), regionOffset(){}

  uint64_t imgSrcId;
  uint64_t frameTime;
  unsigned frameAmount;
  zbe::Region2D region;
  zbe::Vector2D regionOffset;

};

/** \brief Definition of a partial sprite.
 */
struct SprtDef {

    SprtDef(ImgDef img, zbe::Vector2D drawOffset, double ratio)
      : img(img), drawOffset(drawOffset), ratio(ratio) {}

    SprtDef() : img(), drawOffset(), ratio(){}

    ImgDef img;
    zbe::Vector2D drawOffset;
    double ratio;

};


/** \brief Tool capable of generate a sprite from a AnimatedSprite.
 */
class MultiSpriteSheet : public zbe::SpriteSheet<zbe::AnimatedSprite> {
public:

  /** \brief Parametriced constructor
   *  \param id Id for the SpriteSheet;
   **/
  MultiSpriteSheet(int64_t size, const SprtDef& defaultSD) : spriteDefintions(size), size(size), defaultSD(defaultSD) {
    for(unsigned i =0; i<size;i++){
      spriteDefintions[i] = defaultSD;
    }
  }

  MultiSpriteSheet(int64_t size, const ImgDef& defaultID) : spriteDefintions(size), size(size), defaultSD(defaultID, Vector2D({0.0,0.0}), 1.0) {
    for(unsigned i =0; i<size;i++){
      spriteDefintions[i] = defaultSD;
    }
  }

  /** \brief Generate a sprite from a given entity.
   *  \return generated sprite
   **/
  zbe::Sprite generateSprite(zbe::AnimatedSprite* a) {
    SprtDef& usedSD = defaultSD;
    int64_t state = a->getState();
    if(state>=0 && state<size) {
        usedSD = spriteDefintions[state];
    }
    uint64_t time = a->getTime() % (usedSD.img.frameAmount * usedSD.img.frameTime);
    uint64_t frame = time/usedSD.img.frameTime;
    zbe::Region2D src(usedSD.img.region.p + (usedSD.img.regionOffset *  frame), usedSD.img.region.v);
    zbe::Region2D dst({(double)a->getX() + usedSD.drawOffset.x, (double)a->getY() + usedSD.drawOffset.y}, {(double)a->getW() * usedSD.ratio, (double)a->getH() * usedSD.ratio});
    zbe::Sprite s(src, dst, a->getDegrees(), usedSD.img.imgSrcId);
    return s;
  }

  void setSprite(int64_t index, SprtDef sd){
    if(index >= 0 && index < size){
      spriteDefintions[index]= sd;
    }
  }

  void setSprite(int64_t index, ImgDef id){
    if(index >= 0 && index < size){
      spriteDefintions[index]= SprtDef(id, Vector2D({0.0,0.0}), 1.0);
    }
  }

  uint64_t getSize(){
    return size;
  }

  void setDefaultSprite(SprtDef sd){
    defaultSD = sd;
  }

  void setDefaultSprite(ImgDef id){
    defaultSD = SprtDef(id, Vector2D({0.0,0.0}), 1.0);
  }

private:
  std::vector<SprtDef> spriteDefintions;
  int64_t size;
  SprtDef defaultSD;
};

}  // namespace zbe

#endif  // ZBE_GRAPHICS_MULTISPRITESHEET_H_
