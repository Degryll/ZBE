#ifndef ZBE_MAIN_GAME_EVENTS_HANDLERS_STEPINPUTHANDLER
#define ZBE_MAIN_GAME_EVENTS_HANDLERS_STEPINPUTHANDLER

#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/tools/math/Vector.h"

namespace game {

class StepInputHandler : public zbe::InputHandler {
	public:
	  StepInputHandler(const StepInputHandler&) = delete;
	  void operator=(const StepInputHandler&) = delete;

  	StepInputHandler(zbe::Mobile<2>* entity, int movement, int dimension) : e(entity), m(movement), d(dimension) {}

  	void run(float status) {
      zbe::Vector<2>& aux = e->getVelocity();
      if( status) {
        aux[d] = m;
      } else {
        aux[d] = 0;
      }
  	}

	private:
  	zbe::Mobile<2>* e;
    int m;
    int d;
};
} //namespace game

#endif //ZBE_MAIN_GAME_EVENTS_HANDLERS_STEPINPUTHANDLER
