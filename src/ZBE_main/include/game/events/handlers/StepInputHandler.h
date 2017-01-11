#ifndef ZBE_MAIN_GAME_EVENTS_HANDLERS_STEPINPUTHANDLER
#define ZBE_MAIN_GAME_EVENTS_HANDLERS_STEPINPUTHANDLER

#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/archetypes/Position.h"

namespace game {

class StepInputHandler : public zbe::InputHandler {
	public:
  	StepInputHandler(zbe::Position<2>* position, int movement) : p(position), m(movement) {}

  	void run(float state) {
      zbe::Point<2>& aux = p->getPosition();
      aux[0] += m;
      p->setPosition(aux);
  	}

	private:
  	zbe::Position<2>* p;
    int m;
};
} //namespace game

#endif //ZBE_MAIN_GAME_EVENTS_HANDLERS_STEPINPUTHANDLER
