/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ZBNoidLevelClear.cpp
 * @since 2017-12-08
 * @date 2017-12-08
 * @author Degryll Ludo Batis
 * @brief .
 */

#include "zombienoid/daemons/ZBNoidLevelCleaner.h"

namespace zombienoid {

void ZBNoidLevelCleaner::run() {
  using namespace zbe;

  // entities
  // wrappers--------------------------------------------------------------------------------------------------

  std::shared_ptr<AEC<AnimatedSprite> > aecas;
  std::shared_ptr<AEC<Stated> > aecs;

  // bricks---------------------------------------------------------------------------------------------------
  // bricks counter---------------------------------------------------------------------------------------------

  ZBNCfg::rmTFAEConer.get(ZBNCfg::BRICK_COLLISIONER_LIST)->clear();
  ZBNCfg::rmTFAECAnimSprt.get(ZBNCfg::BRICK_AS_LIST)->clear();
  ZBNCfg::rmTFAECStatAvtPos2D.get(ZBNCfg::BRICK_LIST)->clear();

  // ball-----------------------------------------------------------------------------------------------------

  for(auto aecBall : (*ZBNCfg::rmTFAECBncr2DRszAvt.get(ZBNCfg::BALL_LIST))) {
    zbe::Avatar* avtr;
    std::shared_ptr<AvatarEntityContainer<zbe::Avatar> > aecA = aecBall;
    aecA->get()->assignAvatar(&avtr);
    avtr->setERASED();
  }

  ZBNCfg::rmVInt64.get(ZBNCfg::GAMESTATE)->setValue(LEVELCLEARSUCCESS);
}

} //namespace zombienoid
