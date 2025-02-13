/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MKBallInputHandler.h
 * @since 2017-02-12
 * @date 2017-03-12
 * @author Batis
 * @brief Handler that will create a ball with the direction and speed indicated between two mouse clicks
 */

#ifndef ZBE_MAIN_BATIS_EVENTS_HANDLERS_MKBALLINPUTHANDLER
#define ZBE_MAIN_BATIS_EVENTS_HANDLERS_MKBALLINPUTHANDLER

#include <cstdlib>

#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/SDL/starters/SDL_Starter.h"
#include "batis/events/MouseKeeper.h"

namespace batis {

class MKBallInputHandler : public zbe::InputHandler {
	public:
	  MKBallInputHandler(const MKBallInputHandler&) = delete;
	  void operator=(const MKBallInputHandler&) = delete;

  	MKBallInputHandler(): keeper(batis::MouseKeeper::getInstance()), mouseEven(true) {}

  	void run(float status) override {
      if( status) {
        mouseEven = !mouseEven;
        if (mouseEven) {

        }
        printf("Posicion %f, %f\n", keeper.getX(), keeper.getY());
      }
  	}

	private:
    MouseKeeper& keeper;
    bool mouseEven;
    //ballList
    //
};
} //namespace batis

#endif //ZBE_MAIN_GAME_EVENTS_HANDLERS_MKBALLINPUTHANDLER
