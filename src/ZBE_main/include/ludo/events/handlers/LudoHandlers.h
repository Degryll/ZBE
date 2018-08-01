/**
 * Copyright 2012 Batis Degryll Ludo
 * @file LudoHandlers.h
 * @since 2017-02-25
 * @date 2018-07-30
 * @author Ludo
 * @brief Collection of zbe::InputHandler && zbe::TimeHandler for ludomain.
 */
#ifndef LUDO_EVENTS_HANDLERS_LUDOHANDLERS_H
#define LUDO_EVENTS_HANDLERS_LUDOHANDLERS_H

#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/SDL/starters/SDL_Starter.h"

#include "ludo/entities/LudoEntities.h"
#include "ludo/entities/LudoAvatars.h"

namespace ludo {

class ExitInputHandler : public zbe::InputHandler {
	public:
	  ExitInputHandler(const ExitInputHandler&) = delete;
	  void operator=(const ExitInputHandler&) = delete;

  	ExitInputHandler() {}

  	void run(uint32_t, float status) {
      if( status) {
          zbe::SDL_Starter::getInstance().quit();
          exit(0);
      }
  	}

	private:

};

} //namespace ludo

#endif //LUDO_EVENTS_HANDLERS_LUDOHANDLERS_H
