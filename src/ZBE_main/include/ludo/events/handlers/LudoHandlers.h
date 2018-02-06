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

#include "ZBE/core/zbe.h"
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/tools/containers/ResourceManager.h"
#include "ZBE/core/tools/containers/Ticket.h"
#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/events/handlers/TimeHandler.h"

#include "ludo/archetypes/LudoArchetypes.h"
#include "ludo/entities/LudoEntities.h"
#include "ludo/entities/LudoAvatars.h"

namespace ludo {

class GraphicsSet : public zbe::InputHandler {
  public:
	GraphicsSet(const GraphicsSet&) = delete;
	void operator=(const GraphicsSet&) = delete;

  	GraphicsSet(uint64_t graphics, uint64_t id): graphics(graphics), id(id){
  	}

  	void run(float status) {
      if( status > 0.5f) {
        zbe::ResourceManager<zbe::TicketedForwardList<SetableGraphics> >& lmSG = zbe::ResourceManager<zbe::TicketedForwardList<SetableGraphics> >::getInstance();
        std::shared_ptr<zbe::TicketedForwardList<SetableGraphics> > setableGs = lmSG.get(id);
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

class DaemonInputHandler : public zbe::InputHandler {
  public:
	DaemonInputHandler(const DaemonInputHandler&) = delete;
	void operator=(const DaemonInputHandler&) = delete;

  	DaemonInputHandler(std::shared_ptr<zbe::Daemon> daemon): d(daemon){
  	}

  	void run(float status) {
      if( status > 0.5f) {
        d->run();
      }
  	}

  private:
    std::shared_ptr<zbe::Daemon> d;
};

class TicketEraser : public zbe::TimeHandler {
  public:
	TicketEraser(const TicketEraser&) = delete;
	void operator=(const TicketEraser&) = delete;

  	TicketEraser(std::shared_ptr<zbe::Ticket> ticket): t(ticket){
  	}

  	void run(uint64_t) {
        t->setERASED();
  	}

  private:
    std::shared_ptr<zbe::Ticket> t;
};

class DemonRecurrentTimeHandler : public zbe::TimeHandler {
  public:
	DemonRecurrentTimeHandler(const DemonRecurrentTimeHandler&) = delete;
	void operator=(const DemonRecurrentTimeHandler&) = delete;

  	DemonRecurrentTimeHandler(std::shared_ptr<zbe::Daemon> daemon, std::shared_ptr<zbe::TimeEventGenerator> teg, uint64_t period):d(daemon), teg(teg), p(period) {}

  	void run(uint64_t time) {
      d->run();
      std::shared_ptr<zbe::TimeHandler> t = std::make_shared<DemonRecurrentTimeHandler>(d, teg, p);
      teg->addTimer(t,time + p);
  	}

  private:
  	std::shared_ptr<zbe::Daemon> d;
    std::shared_ptr<zbe::TimeEventGenerator> teg;
  	uint64_t p;
};

} //namespace ludo

#endif //LUDO_EVENTS_HANDLERS_LUDOHANDLERS_H
