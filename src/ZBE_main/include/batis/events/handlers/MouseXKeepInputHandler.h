/**
 * Copyright 2012 Batis Degryll Ludo
 * @file MKBallInputHandler.h
 * @since 2017-02-12
 * @date 2017-03-12
 * @author Batis
 * @brief Handler that uses the MouseKeeper to store the mouse X
 */

#ifndef ZBE_MAIN_BATIS_EVENTS_HANDLERS_MOUSEXKEEPINPUTHANDLER
#define ZBE_MAIN_BATIS_EVENTS_HANDLERS_MOUSEXKEEPINPUTHANDLER

#include <cstdlib>

#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/SDL/starters/SDL_Starter.h"
#include "batis/events/MouseKeeper.h"

namespace batis {

class MouseXKeepInputHandler : public zbe::InputHandler {
	public:
	  MouseXKeepInputHandler(const MouseXKeepInputHandler&) = delete;
	  void operator=(const MouseXKeepInputHandler&) = delete;

  	MouseXKeepInputHandler() : keeper(batis::MouseKeeper::getInstance()) {}

  	void run(float status) override {
      keeper.setX(status);
  	}

	private:
    MouseKeeper& keeper;
};
} //namespace batis

#endif //ZBE_MAIN_GAME_EVENTS_HANDLERS_MOUSEXKEEPINPUTHANDLER
