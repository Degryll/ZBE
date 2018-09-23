/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ZombienoidDeathTester.h
 * @since 2017-08-26
 * @date 2017-08-26
 * @author Degryll Ludo Batis
 * @brief Defines a daemon that ends the game if the number of lifes reaches 0 in zombienoid game.
 */

#ifndef ZBE_MAIN_ZOMBIENOID_DAEMONS_ZOMBIENOIDDEATHTESTER_H
#define ZBE_MAIN_ZOMBIENOID_DAEMONS_ZOMBIENOIDDEATHTESTER_H

#include <memory>
#include <cstdint>

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/daemons/MainLoop.h"

#include "ZBE/core/tools/shared/Value.h"


namespace zombienoid {
  /** \brief Defines a daemon that ends the game if the number of lifes reaches 0 in zombienoid game.
   */
  class ZombienoidDeathTester : public zbe::Daemon {
    public:

      ZombienoidDeathTester(const ZombienoidDeathTester&) = delete;
      void operator=(const ZombienoidDeathTester&) = delete;

      /** \brief Parametrized constructor.
       *  \param nballs Current number of balls
       *  \param nlifes Current number of lifes
       */
      ZombienoidDeathTester(std::shared_ptr<zbe::Value<int64_t> > nlifes, std::shared_ptr<zbe::MainLoop> mainloop, std::shared_ptr<zbe::Value<int64_t> > gamesState, uint64_t outValue)
        : nl(nlifes), ml(mainloop), gamesState(gamesState), outValue(outValue) {}

      ~ZombienoidDeathTester(){}

      /** \brief It will finish the game if the number of lifes reaches 0
       */
      void run(){
        if(nl->get() <= 0){
          ml->stop();
          gamesState->set(outValue);
        }
      }

    private:
      std::shared_ptr<zbe::Value<int64_t> > nl;
      std::shared_ptr<zbe::MainLoop> ml;
      std::shared_ptr<zbe::Value<int64_t> > gamesState;
      uint64_t outValue;
  };


}  // namespace zombienoid


#endif // ZBE_MAIN_ZOMBIENOID_DAEMONS_ZOMBIENOIDDEATHTESTER_H
