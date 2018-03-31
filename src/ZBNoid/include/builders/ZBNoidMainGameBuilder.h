/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ZBNoidMainGameBuilder.h
 * @since 2018-01-17
 * @date 2018-01-17
 * @author Degryll Ludo Batis
 * @brief ZBNoid builder of the main game (the actual game, no tittle screens).
 */

#ifndef ZBE_MAIN_ZOMBIENOID_BUILDERS_ZBNOIDMAINGAMEBUILDER_H
#define ZBE_MAIN_ZOMBIENOID_BUILDERS_ZBNOIDMAINGAMEBUILDER_H

#include <memory>
#include <cstdint>

#include "ZBNoid.h"

#include "graphics/RsrcIDDictionary.h"

#include "ZBE/SDL/system/SDLWindow.h"

namespace zombienoid {

/** \brief Defines a daemon that ends the game if the number of lifes reaches 0 in zombienoid game.
 */
class ZBNoidMainGameBuilder {
public:
  ZBNoidMainGameBuilder(std::shared_ptr<RsrcIDDictionary> rsrcIDDic, std::shared_ptr<zbe::SDLWindow> window, std::shared_ptr<zbe::InputBuffer> inputBuffer) : rsrcIDDic(rsrcIDDic), window(window), inputBuffer(inputBuffer) {}
  ~ZBNoidMainGameBuilder() {}

  std::shared_ptr<zbe::Daemon> build();
private:
  std::shared_ptr<RsrcIDDictionary> rsrcIDDic;
  std::shared_ptr<zbe::SDLWindow> window;
  std::shared_ptr<zbe::InputBuffer> inputBuffer;
};


}  // namespace zombienoid


#endif // ZBE_MAIN_ZOMBIENOID_BUILDERS_ZBNOIDMAINGAMEBUILDER_H
