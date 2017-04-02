/**
 * Copyright 2012 Batis Degryll Ludo
 * @file LudoHandlers.h
 * @since 2017-02-25
 * @date 2017-02-25
 * @author Ludo
 * @brief Collection of zbe::InputHandler && zbe::TimeHandler for ludomain.
 */
#ifndef LUDO_EVENTS_HANDLERS_LUDOHANDLERS_H
#define LUDO_EVENTS_HANDLERS_LUDOHANDLERS_H

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/tools/containers/ListManager.h"
#include "ZBE/core/tools/containers/Ticket.h"
#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/events/handlers/TimeHandler.h"

namespace ludo {
/** \brief Actuator capable of making a BouncerCollisioner bounce in a Bounceable.
 */
template <typename R>
class LudoBallBouncer: public zbe::Actuator<zbe::Bouncer<2>, R> {
  public:
    void act(zbe::VoidReactObject<R>*) {
      zbe::Bouncer<2> * gb = zbe::Actuator<zbe::Bouncer<2>, R>::getCollisioner();
      zbe::CollisionData * cd = zbe::Actuator<zbe::Bouncer<2>, R>::getCollisionData();
      zbe::Vector<2> n = gb->getPosition() - cd->getPoint();
      gb->addNormal(n);
    }
};


class GraphicsSet : public zbe::InputHandler {
  public:
	GraphicsSet(const GraphicsSet&) = delete;
	void operator=(const GraphicsSet&) = delete;

  	GraphicsSet(uint64_t graphics, uint64_t id): graphics(graphics), id(id){
  	}

  	void run(float status) {
      if( status > 0.5f) {
        zbe::ListManager<std::forward_list<SetableGraphics*> >& lmSG = zbe::ListManager<std::forward_list<SetableGraphics*> >::getInstance();
        std::forward_list<SetableGraphics*>* setableGs = lmSG.get(id);
        for(auto sg : (*setableGs)){
            sg->setGraphics(graphics);
        }
      }
  	}

  private:
    uint64_t graphics;
    uint64_t id;
};

class TicketToggler : public zbe::InputHandler {
  public:
	TicketToggler(const TicketToggler&) = delete;
	void operator=(const TicketToggler&) = delete;

  	TicketToggler(std::shared_ptr<zbe::Ticket> ticket): t(ticket){
  	}

  	void run(float status) {
      if( status > 0.5f) {
        t->setACTIVE();
      } else {
        t->setINACTIVE();
      }
  	}

  private:
    std::shared_ptr<zbe::Ticket> t;
};


class DemonRecurrentTimeHandler : public zbe::TimeHandler {
  public:
	DemonRecurrentTimeHandler(const DemonRecurrentTimeHandler&) = delete;
	void operator=(const DemonRecurrentTimeHandler&) = delete;

  	DemonRecurrentTimeHandler(std::shared_ptr<zbe::Daemon> daemon, zbe::TimeEventGenerator &teg, uint64_t period):d(daemon), teg(teg), p(period) {}

  	void run(uint64_t time) {
      d->run();
      std::shared_ptr<zbe::TimeHandler> t = std::make_shared<DemonRecurrentTimeHandler>(d, teg, p);
      teg.addTimer(t,time + p);
  	}

  private:
  	std::shared_ptr<zbe::Daemon> d;
  	zbe::TimeEventGenerator &teg;
  	uint64_t p;
};

class TimedDemonRecurrentTimeHandler : public zbe::TimeHandler {
  public:
	TimedDemonRecurrentTimeHandler(const TimedDemonRecurrentTimeHandler&) = delete;
	void operator=(const TimedDemonRecurrentTimeHandler&) = delete;

  	TimedDemonRecurrentTimeHandler(std::shared_ptr<zbe::TimedDaemon> daemon, zbe::TimeEventGenerator &teg, uint64_t period):d(daemon), teg(teg), p(period) {}

  	void run(uint64_t time) {
      d->run(0);
      std::shared_ptr<zbe::TimeHandler> t = std::make_shared<TimedDemonRecurrentTimeHandler>(d, teg, p);
      teg.addTimer(t,time + p);
  	}

  private:
  	std::shared_ptr<zbe::TimedDaemon> d;
  	zbe::TimeEventGenerator &teg;
  	uint64_t p;
};

} //namespace ludo

#endif //LUDO_EVENTS_HANDLERS_LUDOHANDLERS_H
