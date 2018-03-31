/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ZBNoidLevelReset.cpp
 * @since 2017-12-08
 * @date 2017-12-08
 * @author Degryll Ludo Batis
 * @brief .
 */

#include "daemons/ZBNoidLevelReset.h"

namespace zombienoid {

void ZBNoidLevelReset::run() {
  using namespace zbe;
  ZBNCfg::rmVInt64.get(ZBNCfg::NLIFES)->setValue(0);

  ZBNCfg::rmVInt64.get(ZBNCfg::NPOINTS)->setValue(0);

  ZBNCfg::rmVInt64.get(ZBNCfg::GAMESTATE)->setValue(RESETSUCCESS);
}

} //namespace zombienoid
