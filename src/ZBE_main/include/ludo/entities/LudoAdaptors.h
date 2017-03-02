/**
 * Copyright 2012 Batis Degryll Ludo
 * @file LudoEntities.h
 * @since 2017-02-25
 * @date 2017-02-25
 * @author Ludo
 * @brief Entities for ludo's proving grounds.
 */

#ifndef ZBE_MAIN_LUDO_ENTITIES_LUDOADAPTORS
#define ZBE_MAIN_LUDO_ENTITIES_LUDOADAPTORS

#include <cstdint>
#include <memory>

#include "ludo/entities/LudoAvatars.h"
#include "ludo/entities/LudoEntities.h"
#include "ludo/archetypes/LudoArchetypes.h"

namespace ludo {
template<typename T>
class SimpleRotatedSpriteAdaptor {
    public:
        virtual ~SimpleRotatedSpriteAdaptor(){}
        virtual std::shared_ptr<SimpleRotatedSprite> getSimpleRotatedSprite(T * entity) = 0;
};

class RotatedDrawableSimpleRotatedSpriteAdaptor : public SimpleRotatedSpriteAdaptor<RotatedDrawable> {
  public:
    virtual std::shared_ptr<SimpleRotatedSprite> getSimpleRotatedSprite(RotatedDrawable * entity) {
      std::shared_ptr<SimpleRotatedSprite> s = std::make_shared<SimpleRotatedSprite>();

      s->x = entity->getX();
      s->y = entity->getY();
      s->w = entity->getW();
      s->h = entity->getH();
      s->graphics = entity->getGraphics();
      s->angle = entity->getAngle();
      s->angle = (s->angle < 0 ? 360.0 + s->angle : s->angle );
      return (s);
    };
};

} // namespace

#endif //ZBE_MAIN_LUDO_ENTITIES_LUDOADAPTORS
