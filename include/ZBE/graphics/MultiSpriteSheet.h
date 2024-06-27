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
#include <memory>
#include <vector>

#include "ZBE/core/tools/graphics/SpriteSheet.h"
#include "ZBE/core/tools/graphics/Sprite.h"
#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Region.h"
#include "ZBE/core/entities/avatars/Avatar.h"

#include "ZBE/core/system/system.h"

#include "ZBE/resources/definitions.h"

namespace zbe {

/** \brief Tool capable of generate a sprite from a AnimatedSprite.
 */
class ZBEAPI MultiSpriteSheet : public SpriteSheet<uint64_t, int64_t, double, Vector2D, Vector2D> {
public:

  /** \brief Parametriced constructor
   *  \param id Id for the SpriteSheet;
   **/
  MultiSpriteSheet(int64_t size, const SprtDef& defaultSD = SprtDef()) : spriteDefintions(static_cast<size_t>(size)), size(size), defaultSD(defaultSD) {
    for(unsigned i = 0; i < size; i++) {
      spriteDefintions[i] = defaultSD;
    }
  }

  MultiSpriteSheet(int64_t size, const ImgDef& defaultID) : spriteDefintions(static_cast<size_t>(size)), size(size), defaultSD(defaultID) {
    for(unsigned i = 0; i < size; i++) {
      spriteDefintions[i] = defaultSD;
    }
  }

  /** \brief Generate a sprite from a given entity.
   *  \return generated sprite
   **/
  Sprite generateSprite(std::shared_ptr<MAvatar<uint64_t, int64_t, double, Vector2D, Vector2D> > avatar) override {
    SprtDef& usedSD = defaultSD;
    int64_t state = avatar->get<4, int64_t>()->get();
    if(state>=0 && state<size) {
        usedSD = spriteDefintions[state];
    }
    auto cTime = avatar->getContextTime();
    // uint64_t time = a->getTime() % (usedSD.img.frameAmount * usedSD.img.frameTime);
    // TODO ensure that we are using the right time: getTotalTime?
    uint64_t time = cTime->getTotalTime() % (usedSD.img.frameAmount * usedSD.img.frameTime);
    uint64_t frame = time/usedSD.img.frameTime;
    Region2D src(usedSD.img.region.p + (usedSD.img.regionOffset *  frame), usedSD.img.region.v);
    auto size = avatar->get<2, Vector2D>()->get();
    auto pos = avatar->get<1, Vector2D>()->get();
    Region2D dst({static_cast<double>(pos.x) + usedSD.drawOffset.x, static_cast<double>(pos.y) + usedSD.drawOffset.y}, {static_cast<double>(size.x) * usedSD.scale.x, static_cast<double>(size.y) * usedSD.scale.y});
    Sprite s(src, dst, avatar->get<3, double>()->get(), usedSD.img.imgSrcId);
    return s;
    //return Sprite(Region2D(), Region2D(), 0.0, 0);
  }

  // Sprite generateSprite(int) {
  //     return Sprite(Region2D(), Region2D(), 0.0, 0);
  // }

  void setSprite(int64_t index, SprtDef sd){
    if(index >= 0 && index < size){
      spriteDefintions[index]= sd;
    }
  }

  void setSprite(int64_t index, ImgDef id){
    if(index >= 0 && index < size){
      spriteDefintions[index]= SprtDef(id);
    }
  }

  uint64_t getSize(){
    return size;
  }

  void setDefaultSprite(SprtDef sd){
    defaultSD = sd;
  }

  void setDefaultSprite(ImgDef id){
    defaultSD = SprtDef(id);
  }

private:
  std::vector<SprtDef> spriteDefintions;
  int64_t size;
  SprtDef defaultSD;
};

}  // namespace zbe

#endif  // ZBE_GRAPHICS_MULTISPRITESHEET_H_
