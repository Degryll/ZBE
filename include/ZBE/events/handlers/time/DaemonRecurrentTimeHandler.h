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

#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "ZBE/core/events/handlers/TimeHandler.h"
#include "ZBE/core/daemons/Daemon.h"

namespace zbe {

/** \brief Time handler capable of run a daemon.
 */
class DaemonRecurrentTimeHandler : public TimeHandler {
public:
DaemonRecurrentTimeHandler(const DaemonRecurrentTimeHandler&) = delete; //!< Deleted copy constructor.
void operator=(const DaemonRecurrentTimeHandler&) = delete; //!< Deleted copy constructor.

  /** brief Parametrized constructor
   * param daemon Daemon to be executed
   * param teg TimeEventGenerator to use
   * param period repeat time
   */
	DaemonRecurrentTimeHandler(std::shared_ptr<Daemon> daemon, std::shared_ptr<TimeEventGenerator> teg, uint64_t period):d(daemon), teg(teg), p(period) {}

  /** brief Run daemon and re-add the timer.
   *  param time used to calculate next iteration.
   */
	void run(uint64_t time) {
    d->run();
    std::shared_ptr<TimeHandler> t = std::make_shared<DaemonRecurrentTimeHandler>(d, teg, p);
    teg->addTimer(t,time + p);
	}

private:
	std::shared_ptr<Daemon> d;
  std::shared_ptr<TimeEventGenerator> teg;
	uint64_t p;
};

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_TIME_DAEMONRECURRENTTIMEHANDLER_H
