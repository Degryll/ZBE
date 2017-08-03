#ifndef ZBE_MAIN_ZMBIENOID_EVENTS_HANDLERS_EXITINPUTHANDLER
#define ZBE_MAIN_ZMBIENOID_EVENTS_HANDLERS_EXITINPUTHANDLER

#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/SDL/starters/SDL_Starter.h"

namespace zombienoid {

class ExitInputHandler : public zbe::InputHandler {
	public:
	  ExitInputHandler(const ExitInputHandler&) = delete;
	  void operator=(const ExitInputHandler&) = delete;

  	ExitInputHandler() {}

  	void run(float status) {
      if( status) {
          zbe::SDL_Starter::getInstance().quit();
          exit(0);
      }
  	}

	private:

};
} //namespace zombienoid

#endif //ZBE_MAIN_ZMBIENOID_EVENTS_HANDLERS_EXITINPUTHANDLER
