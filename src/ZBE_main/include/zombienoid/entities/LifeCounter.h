/**
 * Copyright 2011 Batis Degryll Ludo
 * @file LifeCounter.h
 * @since 2017-08-22
 * @date 2017-08-22
 * @author Batis Degryll Ludo
 * @brief A game life counter.
 */

#ifndef ZBE_MAIN_ZOMBIENOID_ENTITIES_LIFECOUNTER_H
#define ZBE_MAIN_ZOMBIENOID_ENTITIES_LIFECOUNTER_H

#include <string>
#include <memory>

#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/archetypes/implementations/BaseState.h"
#include "ZBE/archetypes/TextDrawable.h"

#include "ZBE/entities/avatars/implementations/BaseStated.h"
#include "ZBE/entities/avatars/implementations/BaseSingleTextSprite.h"
#include "ZBE/entities/avatars/Stated.h"
#include "ZBE/entities/TextBox.h"

namespace zbe {

/** \brief This implements a base 1:1 avatar that can bounce.
 */
class LifeCounter: public BaseState, // TODO build BaseState with a Value<uint64_t> reference.
                   public AvatarEntityFixed<Stated>,
                   public TextBox {
public:

  LifeCounter(int64_t x, int64_t y, int64_t width, int64_t height, uint64_t graphics, std::shared_ptr<Value<int64_t> > lifes)
    : BaseState(lifes), TextBox(x, y, width, height, graphics), t(std::to_string(lifes->getValue())) {
    AvatarEntityFixed<Stated>::setAvatar(new BaseStated(this));
    AvatarEntityFixed<SingleTextSprite>::setAvatar(new BaseSingleTextSprite(this));
  }

  const std::string& getText() {
    t = std::to_string(BaseState::getState());
    return t;
  }

private:
  std::string t;
};

} // namespace zbe

#endif  // ZBE_MAIN_ZOMBIENOID_ENTITIES_LIFECOUNTER_H
