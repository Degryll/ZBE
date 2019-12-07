/**
 * Copyright 2012 Batis Degryll Ludo
 * @file DaemonTimeHandler.h
 * @since 2017-11-24
 * @date 2018-02-25
 * @author Batis Degrill Ludo
 * @brief Time handler capable of erase a ticket.
 */

#ifndef ZBE_EVENTS_HANDLERS_TIME_TICKETERASER_H
#define ZBE_EVENTS_HANDLERS_TIME_TICKETERASER_H

#include <cstdint>
#include <memory>

#include "ZBE/core/tools/containers/Ticket.h"
#include "ZBE/core/events/handlers/TimeHandler.h"

#include "ZBE/core/system/system.h"

namespace zbe {

class ZBEAPI TicketEraser : public TimeHandler {
  public:
	TicketEraser(const TicketEraser&) = delete; //!< Avoid copy.
	void operator=(const TicketEraser&) = delete; //!< Avoid copy.

    /** brief Empty constructor
     */
  	TicketEraser(): t(nullptr){}

    /** brief Parametrized constructor
     * param ticket Ticket to be erased
     */
  	TicketEraser(std::shared_ptr<Ticket> ticket): t(ticket){}

  	void setTicket(std::shared_ptr<Ticket> ticket) {t = ticket;}

    /** brief Erases ticket
     *  param time not used
     */
  	void run(uint64_t) {
        t->setERASED();
  	}

  private:
    std::shared_ptr<zbe::Ticket> t;
};

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_TIME_TICKETERASER_H
