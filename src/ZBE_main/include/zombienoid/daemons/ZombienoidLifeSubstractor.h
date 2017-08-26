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


namespace zombienoid {
  /** \brief Defines a daemon that substracts lifes in Zombienoid game.
   */
  class ZombienoidLifeSubstractor : public zbe::Daemon {
    public:

      /** \brief Parametrized constructor.
       *  \param nballs Current number of balls
       *  \param nlifes Current number of lifes
       */
      ZombienoidLifeSubstractor(std::shared_ptr<zbe::Value<int64_t> > nballs, std::shared_ptr<zbe::Value<int64_t> > nlifes) : nb(nballs), nl(nlifes) {}

      /** \brief It will run decrease lifes there are no balls.
       */
      void run(){
        if(nb->getValue() == 0){
          nl->add(-1);
        }
      }

    private:
      std::shared_ptr<zbe::Value<int64_t> > nb;
      std::shared_ptr<zbe::Value<int64_t> > nl;
  };


}  // namespace zombienoid


#endif // ZBE_MAIN_ZOMBIENOID_DAEMONS_ZOMBIENOIDLIFESUBSTRACTOR_H
