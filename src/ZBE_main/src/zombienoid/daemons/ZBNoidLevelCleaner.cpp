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

  demagnetizeDaemon->run();

  // ball-----------------------------------------------------------------------------------------------------

  for(auto aecBall : (*ZBNCfg::rmTFAECBncr2DRszAvt.get(ZBNCfg::BALL_LIST))) {
    zbe::Avatar* avtr;
    std::shared_ptr<AvatarEntityContainer<zbe::Avatar> > aecA = aecBall;
    aecA->get()->assignAvatar(&avtr);
    avtr->setERASED();
  }

  for(auto aecItem : (*ZBNCfg::rmTFAECBncr2DAvt.get(ZBNCfg::ITEM_LIST))) {
    zbe::Avatar* avtr;
    std::shared_ptr<AvatarEntityContainer<zbe::Avatar> > aecA = aecItem;
    aecA->get()->assignAvatar(&avtr);
    avtr->setERASED();
  }

  // bar------------------------------------------------------------------------------------------------------

  for(auto aecBar : (*ZBNCfg::rmTFAECStat.get(ZBNCfg::STICKY_STATE_LIST))) {
    zbe::Stated* sttd;
    std::shared_ptr<AvatarEntityContainer<zbe::Stated> > aecS = aecBar;
    aecS->get()->assignAvatar(&sttd);
    sttd->setState(BAR_NORMAL_STATE);
  }
  ZBNCfg::rmTFAECAnimSprt.get(ZBNCfg::BOOM_AS_LIST)->clear();

  ZBNCfg::rmVInt64.get(ZBNCfg::STICKY_ITEM_STATE)->setValue(BAR_NORMAL_STATE);
  ZBNCfg::rmVInt64.get(ZBNCfg::GAMESTATE)->setValue(LEVELCLEARSUCCESS);

}

} //namespace zombienoid
