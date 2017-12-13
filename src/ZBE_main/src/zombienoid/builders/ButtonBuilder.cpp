/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ButtonBuilder.cpp
 * @since 2017-12-09
 * @date 2017-12-09
 * @author Degryll Ludo Batis
 * @brief ZBNoid button builder.
 */

#include "zombienoid/builders/ButtonBuilder.h"

#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/entities/avatars/AnimatedSprite.h"
#include "ZBE/entities/avatars/SingleTextSprite.h"

#include "ZBE/events/handlers/input/DaemonInputHandler.h"

#include "zombienoid/archetypes/implementations/SimpleStateDrawable.h"
#include "zombienoid/archetypes/implementations/SimpleTextDrawable.h"

namespace zombienoid {

void ButtonBuilder::build() {
  const int64_t IDLE_BUTTON_STATE = 0;

  RsrcTicketedAEC<AnimatedSprite>::get(asDrwListId).push_front(std::make_shared<SimpleStateDrawable>(area, IDLE_BUTTON_STATE, graphics));
  RsrcTicketedAEC<SingleTextSprite>::get(spsDrwListId).push_front(std::make_shared<SimpleTextDrawable>(area, text, graphics));
  ieg->addHandler(ZBEK_MOUSE_LEFT, new DaemonInputHandler(daemon));
}

}  // namespace zombienoid
