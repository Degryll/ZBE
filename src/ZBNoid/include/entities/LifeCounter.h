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
                   virtual public State,
                   public AvatarEntityFixed<Stated>,
                   public TextBox {
public:

  LifeCounter(int64_t x, int64_t y, int64_t width, int64_t height, uint64_t charLenght , uint64_t graphics, std::shared_ptr<Value<int64_t> > lifes)
    : BaseState(lifes), TextBox(x, y, width, height, graphics), len(charLenght), stateCache(BaseState::getState()), t(std::to_string(lifes->get())) {
    AvatarEntityFixed<Stated>::setAvatar(new BaseStated(this));
    AvatarEntityFixed<SingleTextSprite>::setAvatar(new BaseSingleTextSprite(this));
    updateText();
  }

  const std::string& getText() {
    updateText();
    return t;
  }

private:
  void updateText() {
    int64_t state = BaseState::getState();
    if(state != stateCache) {
      stateCache = BaseState::getState();
      t = std::to_string(state);
      t.insert(t.begin(), std::max((uint64_t)0, len - t.length()), ' ');
    }
  }
  uint64_t len;
  int64_t stateCache;
  std::string t;
};

} // namespace zbe

#endif  // ZBE_MAIN_ZOMBIENOID_ENTITIES_LIFECOUNTER_H
