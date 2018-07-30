/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ZombienoidLifeSubstractor.h
 * @since 2017-08-26
 * @date 2017-08-26
 * @author Degryll Ludo Batis
 * @brief Defines a daemon that substracts lifes in Zombienoid game
 */

#ifndef ZBE_MAIN_ZOMBIENOID_DAEMONS_ZOMBIENOIDLIFESUBSTRACTOR_H
#define ZBE_MAIN_ZOMBIENOID_DAEMONS_ZOMBIENOIDLIFESUBSTRACTOR_H

#include <memory>
#include <cstdint>

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/tools/shared/Value.h"

#include "ZBE/entities/avatars/Movable.h"

#include "behaviors/builders/BallBuilder.h"


namespace zombienoid {
  /** \brief Defines a daemon that substracts lifes in Zombienoid game.
   */
  class ZombienoidLifeSubstractor : public zbe::Daemon {
    public:

      ZombienoidLifeSubstractor(const ZombienoidLifeSubstractor&) = delete;
      void operator=(const ZombienoidLifeSubstractor&) = delete;

      /** \brief Parametrized constructor.
       *  \param nballs Current number of balls
       *  \param nlifes Current number of lifes
       */
      ZombienoidLifeSubstractor(std::shared_ptr<zbe::Value<int64_t> > nballs, std::shared_ptr<zbe::Value<int64_t> > nlifes, std::shared_ptr<zbe::Daemon> builder) : nb(nballs), nl(nlifes),    builder(builder) {}

      /** \brief It will run decrease lifes there are no balls.
       */
      void run(){
        if(nb->get() == 0){
          nl->add(-1);
          builder->run();
        }
      }

    private:
      std::shared_ptr<zbe::Value<int64_t> > nb;
      std::shared_ptr<zbe::Value<int64_t> > nl;
      std::shared_ptr<zbe::Daemon> builder;
  };


}  // namespace zombienoid


#endif // ZBE_MAIN_ZOMBIENOID_DAEMONS_ZOMBIENOIDLIFESUBSTRACTOR_H
