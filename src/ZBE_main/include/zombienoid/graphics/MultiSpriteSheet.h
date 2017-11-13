/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MultiSpriteSheet.h
 * @since 2017-10-11
 * @date 2017-10-11
 * @author Degryll Ludo Batis
 * @brief Interface capable of generate a sprite from a given entity.
 */

#ifndef ZOMBIENOID_GRAPHICS_MULTISPRITESHEET_H_
#define ZOMBIENOID_GRAPHICS_MULTISPRITESHEET_H_

#include <stdint.h>
#include <vector>

#include "ZBE/core/tools/graphics/SpriteSheet.h"
#include "ZBE/core/tools/graphics/Sprite.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Region.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/avatars/AnimatedSprite.h"

namespace zombienoid {

struct ImgSrcDef {

  ImgSrcDef(uint64_t imgSrcId, uint64_t frameTime, unsigned frameAmount, zbe::Region2D intialRegion, zbe::Vector2D frameDisplacemet)
    : imgSrcId(imgSrcId),
      frameTime(frameTime),
      frameAmount(frameAmount),
      intialRegion(intialRegion),
      frameDisplacemet(frameDisplacemet){}

  ImgSrcDef() : imgSrcId(), frameTime(), frameAmount(), intialRegion(), frameDisplacemet(){}

  uint64_t imgSrcId;
  uint64_t frameTime;
  unsigned frameAmount;
  zbe::Region2D intialRegion;
  zbe::Vector2D frameDisplacemet;
};


/** \brief Interface capable of generate a sprite from a given entity.
 */
class MultiSpriteSheet : public zbe::SpriteSheet<zbe::AnimatedSprite> {
public:

  /** \brief Parametriced constructor
   *  \param id Id for the SpriteSheet;
   **/
  MultiSpriteSheet(int64_t size, const ImgSrcDef& defaultISD) : imageDefintions(size), size(size), defaultISD(defaultISD) {
    for(unsigned i =0; i<size;i++){
      imageDefintions[i] = defaultISD;
    }
  }

  /** \brief Generate a sprite from a given entity.
   *  \return generated sprite
   **/
  zbe::Sprite generateSprite(zbe::AnimatedSprite* a) {
    //Sprite(Region2D src, Region2D dst, double angle, uint64_t graphics)
    ImgSrcDef& usedisd = defaultISD;
    int64_t state = a->getState();
    if(state>=0 && state<size) {
        usedisd = imageDefintions[state];
    }
    uint64_t time = a->getTime() % (usedisd.frameAmount * usedisd.frameTime);
    uint64_t frame = time/usedisd.frameTime;
    zbe::Region2D src(usedisd.intialRegion.p + (usedisd.frameDisplacemet *  frame), usedisd.intialRegion.v);
    zbe::Region2D dst({(double)a->getX(), (double)a->getY()}, {(double)a->getW(), (double)a->getH()});
    zbe::Sprite s(src, dst, a->getDegrees(), usedisd.imgSrcId);
    return s;
  }

  void setImgSrcDef(int64_t index, ImgSrcDef isd){
    if(index >= 0 && index < size){
      imageDefintions[index]= isd;
    }
  }

  uint64_t getSize(){
    return size;
  }

  void setDefaultISD(ImgSrcDef isd){
    defaultISD = isd;
  }

private:
  std::vector<ImgSrcDef> imageDefintions;
  int64_t size;
  ImgSrcDef defaultISD;
};

}  // namespace zombienoid

#endif  // ZOMBIENOID_GRAPHICS_MULTISPRITESHEET_H_
