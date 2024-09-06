#ifndef ZBE_MAIN_GAME_EVENTS_HANDLERS_TTPHANDLER
#define ZBE_MAIN_GAME_EVENTS_HANDLERS_TTPHANDLER

#include <cstdio>

#include "ZBE/core/events/handlers/TimeHandler.h"
#include "ZBE/core/tools/math/Point.h"

#include "ZBE/entities/avatars/Positionable.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"

namespace game {

class TtpHandler : public zbe::TimeHandler {
	public:
	  TtpHandler(const TtpHandler&) = delete;
	  void operator=(const TtpHandler&) = delete;

  	TtpHandler(std::shared_ptr<zbe::AvatarEntity<zbe::Positionable<2> >> entity, std::shared_ptr<zbe::TimeEventGenerator> teg) : e(entity), teg(teg) {}

  	void run(uint64_t time) {
      zbe::Positionable<2>* avatar;
      e->assignAvatar(&avatar);

      zbe::Point<2> position = avatar->getPosition();

      if (position[0] >= 300){
      	position[0] = 100;
        position[1] += 50;
	      if (position[1] > 300) {
      		position[1] = 100;
	      }
      } else {
        position[0] += 50;
      }
      avatar->setPosition(position);
      std::shared_ptr<zbe::TimeHandler> t = std::make_shared<TtpHandler>(e, teg);
      teg->addTimer(t,time + (zbe::SECOND*2));
  	}

	private:
  	std::shared_ptr<zbe::AvatarEntity<zbe::Positionable<2> > > e;
  	std::shared_ptr<zbe::TimeEventGenerator> teg;
};

} //namespace game

#endif //ZBE_MAIN_GAME_EVENTS_HANDLERS_TTPHANDLER
