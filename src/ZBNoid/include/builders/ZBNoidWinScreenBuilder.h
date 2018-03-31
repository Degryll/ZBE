/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ZBNoidWinScreenBuilder.h
 * @since 2017-12-08
 * @date 2017-12-08
 * @author Degryll Ludo Batis
 * @brief Defines a daemon that ends the game if the number of lifes reaches 0 in zombienoid game.
 */

#ifndef ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDWINSCREENBUILDER_H
#define ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDWINSCREENBUILDER_H

#include <memory>
#include <cstdint>

#include "ZBNoid.h"

#include "ZBE/core/daemons/Daemon.h"


#include "ZBE/core/events/generators/InputEventGenerator.h"

namespace zombienoid {

  /** \brief Defines a daemon that ends the game if the number of lifes reaches 0 in zombienoid game.
   */
  class ZBNoidWinScreenBuilder {
    public:

      ZBNoidWinScreenBuilder(const ZBNoidWinScreenBuilder&) = delete;
      void operator=(const ZBNoidWinScreenBuilder&) = delete;

      ZBNoidWinScreenBuilder(std::shared_ptr<RsrcIDDictionary> rsrcIDDic, std::shared_ptr<zbe::SDLWindow> window, std::shared_ptr<zbe::InputBuffer> inputBuffer) : rsrcIDDic(rsrcIDDic), window(window), inputBuffer(inputBuffer) {}

      ~ZBNoidWinScreenBuilder(){}

      /** \brief It will finish the game if the number of lifes reaches 0
       */
      std::shared_ptr<zbe::Daemon> build();

    private:
      std::shared_ptr<RsrcIDDictionary> rsrcIDDic;
      std::shared_ptr<zbe::SDLWindow> window;
      std::shared_ptr<zbe::InputBuffer> inputBuffer;
  };


}  // namespace zombienoid


#endif // ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDWINSCREENBUILDER_H
