/**
 * Copyright 2012 Batis Degryll Ludo
 * @file DaemonTimeHandler.h
 * @since 2017-11-24
 * @date 2017-11-24
 * @author Batis Degrill Ludo
 * @brief Time handler capable of erase a ticket.
 */

#ifndef ZBE_EVENTS_HANDLERS_TIME_TICKETERASER_H
#define ZBE_EVENTS_HANDLERS_TIME_TICKETERASER_H

#include <memory>

#include "ZBE/core/tools/containers/Ticket.h"
#include "ZBE/core/events/handlers/TimeHandler.h"

namespace zbe {

class TicketEraser : public TimeHandler {
  public:
	TicketEraser(const TicketEraser&) = delete;
	void operator=(const TicketEraser&) = delete;

  	TicketEraser(std::shared_ptr<Ticket> ticket): t(ticket){
  	}

  	void run(uint64_t) {
        t->setERASED();
  	}

  private:
    std::shared_ptr<zbe::Ticket> t;

};

} //namespace zbe
#endif //ZBE_EVENTS_HANDLERS_TIME_TICKETERASER_H
