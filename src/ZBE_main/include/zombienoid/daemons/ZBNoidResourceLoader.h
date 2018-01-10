/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ZBNoidResourceLoader.h
 * @since 2017-08-26
 * @date 2017-08-26
 * @author Degryll Ludo Batis
 * @brief Daemon that load all ZBNoid resources.
 */

#ifndef ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDRESOURCELOADER_H
#define ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDRESOURCELOADER_H

#include <memory>
#include <cstdint>

#include "ZBE/core/daemons/Daemon.h"

#include "zombienoid/ZBNoid.h"

#include "zombienoid/graphics/RsrcIDDictionary.h"

#include "ZBE/SDL/system/SDLWindow.h"

namespace zombienoid {
  /** \brief Defines a daemon that ends the game if the number of lifes reaches 0 in zombienoid game.
   */
  class ZBNoidResourceLoader : public zbe::Daemon {
    public:

      ZBNoidResourceLoader(const ZBNoidResourceLoader&) = delete;
      void operator=(const ZBNoidResourceLoader&) = delete;

      ZBNoidResourceLoader(std::shared_ptr<RsrcIDDictionary> rsrcIDDic, std::shared_ptr<zbe::SDLImageStore> imgStore, std::shared_ptr<zbe::SDLTextFontStore> textFontStore) : rsrcIDDic(rsrcIDDic), imgStore(imgStore), textFontStore(textFontStore)  {}

      ~ZBNoidResourceLoader() {}

      void run();

    private:
      std::shared_ptr<RsrcIDDictionary> rsrcIDDic;
      std::shared_ptr<zbe::SDLImageStore> imgStore;
      std::shared_ptr<zbe::SDLTextFontStore> textFontStore;
  };


}  // namespace zombienoid


#endif // ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDRESOURCELOADER_H
