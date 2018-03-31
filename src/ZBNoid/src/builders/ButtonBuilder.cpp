/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ButtonBuilder.cpp
 * @since 2017-12-09
 * @date 2017-12-09
 * @author Degryll Ludo Batis
 * @brief ZBNoid button builder.
 */

#include "builders/ButtonBuilder.h"

#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/avatars/AnimatedSprite.h"

#include "ZBE/entities/avatars/SingleTextSprite.h"

#include "ZBE/events/handlers/input/DaemonClickIH.h"

#include "archetypes/implementations/SimpleStateDrawable.h"
#include "archetypes/implementations/SimpleTextDrawable.h"

namespace zombienoid {

void ButtonBuilder::build() {

  ZBNCfg::rmTFAECAnimSprt.get(asDrwListId)->push_front(std::make_shared<zbe::AEC<zbe::AnimatedSprite> >(std::make_shared<zbe::AEFixed<zbe::AnimatedSprite> >(new SimpleStateDrawable(area, IDLE_BUTTON_STATE, 0.0, graphics))));
  ZBNCfg::rmTFAECSTextSprt.get(spsDrwListId)->push_front(std::make_shared<zbe::AEC<zbe::SingleTextSprite> >(std::make_shared<zbe::AEFixed<zbe::SingleTextSprite> >(new SimpleTextDrawable(area, text, textGraphics))));
  brdcstHI->addHandler(std::make_shared<zbe::DaemonClickIH>(area, xvalue, yvalue, daemon));
}

}  // namespace zombienoid
