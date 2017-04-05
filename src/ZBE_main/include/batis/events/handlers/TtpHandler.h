#ifndef ZBE_MAIN_GAME_EVENTS_HANDLERS_TTPHANDLER
#define ZBE_MAIN_GAME_EVENTS_HANDLERS_TTPHANDLER

#include <cstdio>

#include "ZBE/core/events/handlers/TimeHandler.h"
#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/entities/avatars/Positionable.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "batis/entities/GameBoard.h"


namespace batis {

class TtpHandler : public zbe::TimeHandler {
	public:
	  TtpHandler(const TtpHandler&) = delete;
	  void operator=(const TtpHandler&) = delete;

  	TtpHandler(zbe::AvatarEntity<zbe::Positionable<2> >* entity, zbe::TimeEventGenerator &teg, batis::GameBoard &board) : e(entity), teg(teg), board(board) {}

  	void run(uint64_t time) {
      zbe::Positionable<2>* avatar;
      e->assignAvatar(&avatar);

      zbe::Point<2> position = avatar->getPosition();
      position[0] = (position[0]-board.board.margin)/(board.board.brickWidth + board.board.space);
      position[1] = (position[1]-board.board.margin)/(board.board.brickHeight + board.board.space);

      if (position[0] >= board.board.cols-1){
      	position[0] = 0;
        position[1] += 1;
	      if (position[1] > board.board.rows-1) {
      		position[1] = 0;
	      }
      } else {
        position[0] += 1;
      }
      position[0] = board.board.margin + (position[0] * (board.board.brickWidth + board.board.space));
      position[1] = board.board.margin + (position[1] * (board.board.brickHeight + board.board.space));

      avatar->setPosition(position);
      std::shared_ptr<zbe::TimeHandler> t = std::make_shared<batis::TtpHandler>(e, teg, board);
      teg.addTimer(t,time + (zbe::SECOND));
  	}

	private:
  	zbe::AvatarEntity<zbe::Positionable<2> >* e;
  	zbe::TimeEventGenerator &teg;
  	batis::GameBoard &board;
};

} //namespace batis

#endif //ZBE_MAIN_GAME_EVENTS_HANDLERS_TTPHANDLER
