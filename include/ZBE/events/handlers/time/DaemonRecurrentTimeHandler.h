/**
 * Copyright 2012 Batis Degryll Ludo
 * @file DaemonRecurrentTimeHandler.h
 * @since 2017-10-25
 * @date 2018-02-25
 * @author Batis Degrill Ludo
 * @brief Recurrent Time handler capable of run a daemon.
 */

#ifndef ZBE_EVENTS_HANDLERS_TIME_DAEMONRECURRENTTIMEHANDLER_H
#define ZBE_EVENTS_HANDLERS_TIME_DAEMONRECURRENTTIMEHANDLER_H

#include <cstdint>
#include <memory>

#include "ZBE/core/entities/avatars/Avatar.h"

#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "ZBE/core/events/handlers/TimeHandler.h"
#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Time handler capable of run a daemon.
 */
class DaemonRecurrentTimeHandler : public TimeHandler {
public:
DaemonRecurrentTimeHandler(const DaemonRecurrentTimeHandler&) = delete; //!< Deleted copy constructor.
void operator=(const DaemonRecurrentTimeHandler&) = delete; //!< Deleted copy constructor.

  /** brief Empty constructor
   */
	DaemonRecurrentTimeHandler() : d(nullptr), teg(nullptr), a(nullptr), id(0), p(0) {}

  /** brief Parametrized constructor
   * param daemon Daemon to be executed
   * param teg TimeEventGenerator to use
   * param avatar Avatar that stores the ticket for the timers generated
   * param id Id to identify the ticket to the timer
   * param period repeat time
   */
	DaemonRecurrentTimeHandler(std::shared_ptr<Daemon> daemon, std::shared_ptr<TimeEventGenerator> teg, std::shared_ptr<Avatar> avatar, uint64_t id, uint64_t period) : d(daemon), teg(teg), a(avatar), id(id), p(period) {}

  /** brief Set the daemon that will be executed when the timers ends.
   *  param daemon The daemon.
   */
	void setDaemon(std::shared_ptr<Daemon> daemon) {this->d = daemon;}

  /** brief Set the time event generator to handle the timers.
   *  param teg The time event generator.
   */
	void setTimeEventGenerator(std::shared_ptr<TimeEventGenerator> teg) {this->teg = teg;}

  /** brief Set the avatar that stores the ticket for the timer.
   *  param avatar The avatar.
   *  param id The id used to store the ticket.
   */
	void setAvatar(std::shared_ptr<Avatar> avatar, uint64_t id) {
	  this->a = avatar;
	  this->id = id;
  }

  /** brief Set the repetition time.
   *  param period The time period until the timers triggers again.
   */
	void setPeriod(uint64_t period) {this->p = period;}


  /** brief Run daemon and re-add the timer.
   *  param time used to calculate next iteration.
   */
	void run(uint64_t time) {
    d->run();
    std::shared_ptr<TimeHandler> th = std::make_shared<DaemonRecurrentTimeHandler>(d, teg, a, id, p);
    std::shared_ptr<TimerTicket> tt = teg->addTimer(th, time + p);
    a->replaceTicket(id, tt);
	}

private:
	std::shared_ptr<Daemon> d;
  std::shared_ptr<TimeEventGenerator> teg;
  std::shared_ptr<Avatar> a;
	uint64_t id;
	uint64_t p;
};

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_TIME_DAEMONRECURRENTTIMEHANDLER_H
