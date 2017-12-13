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

#include "ZBE/core/daemons/Daemon.h"


#include "ZBE/core/events/generators/InputEventGenerator.h"

namespace zombienoid {

  struct ZBNoidTitleBuilderCFG {
    uint64_t preLoopId;
    uint64_t postLoopId;
    uint64_t asDrawerId;
    uint64_t stsDrawerId;
    uint64_t spriteSheetID;
    uint64_t fontID;
  }
  /** \brief Defines a daemon that ends the game if the number of lifes reaches 0 in zombienoid game.
   */
  class ZBNoidTitleBuilder : public zbe::Daemon {
    public:

      ZBNoidTitleBuilder(const ZBNoidTitleBuilder&) = delete;
      void operator=(const ZBNoidTitleBuilder&) = delete;

      ZBNoidTitleBuilder(std::shared_ptr<InputEventGenerator> ieg, std::shared_ptr< Value<int64_t> > exit, const ZBNoidTitleBuilderCFG& cfg )
        : ieg(ieg), exit(exit), preLoopId(cfg.preLoopId), postLoopId(cfg.postLoopId), inputEventGenId(cfg.inputEventGenId),
          asDrawerId(cfg.asDrawerId), stsDrawerId(cfg.stsDrawerId), spriteSheetID(cfg.spriteSheetID), fontID(cfg.fontID) {
      }

      ~ZBNoidTitleBuilder(){}

      /** \brief It will finish the game if the number of lifes reaches 0
       */
      void run();

    private:
      std::shared_ptr<InputEventGenerator> ieg;
      std::shared_ptr< Value<int64_t> > exit;
      uint64_t preLoopId;
      uint64_t postLoopId;
      uint64_t asDrawerId;
      uint64_t stsDrawerId;
      uint64_t spriteSheetID;
      uint64_t fontID;
  };


}  // namespace zombienoid


#endif // ZBE_MAIN_ZOMBIENOID_DAEMONS_ZBNOIDTITLEBUILDER_H
