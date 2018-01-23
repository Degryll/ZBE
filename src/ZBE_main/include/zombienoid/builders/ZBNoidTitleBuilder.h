/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ZBNoidTitleBuilder.h
 * @since 2017-12-08
 * @date 2017-12-08
 * @author Degryll Ludo Batis
 * @brief Defines a daemon that ends the game if the number of lifes reaches 0 in zombienoid game.
 */

#ifndef ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDTITLEBUILDER_H
#define ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDTITLEBUILDER_H

#include <memory>
#include <cstdint>

#include "zombienoid/ZBNoid.h"

#include "ZBE/core/daemons/Daemon.h"


#include "ZBE/core/events/generators/InputEventGenerator.h"

namespace zombienoid {

  /** \brief Defines a daemon that ends the game if the number of lifes reaches 0 in zombienoid game.
   */
  class ZBNoidTitleBuilder {
    public:

      ZBNoidTitleBuilder(const ZBNoidTitleBuilder&) = delete;
      void operator=(const ZBNoidTitleBuilder&) = delete;

      ZBNoidTitleBuilder(std::shared_ptr<RsrcIDDictionary> rsrcIDDic, std::shared_ptr<zbe::SDLWindow> window, std::shared_ptr<zbe::InputBuffer> inputBuffer) : rsrcIDDic(rsrcIDDic), window(window), inputBuffer(inputBuffer) {}

      ~ZBNoidTitleBuilder(){}

      /** \brief It will finish the game if the number of lifes reaches 0
       */
      std::shared_ptr<zbe::Daemon> build();

    private:
      std::shared_ptr<RsrcIDDictionary> rsrcIDDic;
      std::shared_ptr<zbe::SDLWindow> window;
      std::shared_ptr<zbe::InputBuffer> inputBuffer;
  };


}  // namespace zombienoid


#endif // ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDTITLEBUILDER_H
