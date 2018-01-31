/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ZBNoidLostScreenBuilder.h
 * @since 2017-12-08
 * @date 2017-12-08
 * @author Degryll Ludo Batis
 * @brief
 */

#ifndef ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDLOSTSCREENBUILDER_H
#define ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDLOSTSCREENBUILDER_H

#include <memory>
#include <cstdint>

#include "zombienoid/ZBNoid.h"

#include "ZBE/core/daemons/Daemon.h"


#include "ZBE/core/events/generators/InputEventGenerator.h"

namespace zombienoid {

  /** \brief 
   */
  class ZBNoidLostScreenBuilder {
    public:

      ZBNoidLostScreenBuilder(const ZBNoidLostScreenBuilder&) = delete;
      void operator=(const ZBNoidLostScreenBuilder&) = delete;

      ZBNoidLostScreenBuilder(std::shared_ptr<RsrcIDDictionary> rsrcIDDic, std::shared_ptr<zbe::SDLWindow> window, std::shared_ptr<zbe::InputBuffer> inputBuffer) : rsrcIDDic(rsrcIDDic), window(window), inputBuffer(inputBuffer) {}

      ~ZBNoidLostScreenBuilder(){}

      /** \brief It will finish the game if the number of lifes reaches 0
       */
      std::shared_ptr<zbe::Daemon> build();

    private:
      std::shared_ptr<RsrcIDDictionary> rsrcIDDic;
      std::shared_ptr<zbe::SDLWindow> window;
      std::shared_ptr<zbe::InputBuffer> inputBuffer;
  };


}  // namespace zombienoid


#endif // ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDLOSTSCREENBUILDER_H
