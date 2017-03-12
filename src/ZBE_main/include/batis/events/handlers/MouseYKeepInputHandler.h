/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MKBallInputHandler.h
 * @since 2017-02-12
 * @date 2017-03-12
 * @author Batis
 * @brief Handler that uses the MouseKeeper to store the mouse Y
 */

#ifndef ZBE_MAIN_BATIS_EVENTS_HANDLERS_MOUSEYKEEPINPUTHANDLER
#define ZBE_MAIN_BATIS_EVENTS_HANDLERS_MOUSEYKEEPINPUTHANDLER

#include <cstdlib>

#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/SDL/starters/SDL_Starter.h"
#include "batis/events/MouseKeeper.h"

namespace batis {

class MouseYKeepInputHandler : public zbe::InputHandler {
	public:
	  MouseYKeepInputHandler(const MouseYKeepInputHandler&) = delete;
	  void operator=(const MouseYKeepInputHandler&) = delete;

  	MouseYKeepInputHandler() : keeper(batis::MouseKeeper::getInstance()) {}

  	void run(float status) {
      keeper.setY(status);
  	}

	private:
    MouseKeeper& keeper;
};
} //namespace batis

#endif //ZBE_MAIN_GAME_EVENTS_HANDLERS_MOUSEYKEEPINPUTHANDLER
