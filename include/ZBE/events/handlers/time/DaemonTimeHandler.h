/**
 * Copyright 2012 Batis Degryll Ludo
 * @file DaemonTimeHandler.h
 * @since 2017-10-25
 * @date 2018-02-25
 * @author Batis Degrill Ludo
 * @brief Time handler capable of run a daemon.
 */

#ifndef ZBE_EVENTS_HANDLERS_TIME_DAEMONTIMEHANDLER_H
#define ZBE_EVENTS_HANDLERS_TIME_DAEMONTIMEHANDLER_H

#include <cstdint>
#include <memory>

#include "ZBE/core/events/handlers/TimeHandler.h"
#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/core/system/system.h"

namespace zbe {

class DaemonTimeHandler : public TimeHandler {
public:
DaemonTimeHandler(const DaemonTimeHandler&) = delete; //!< Avoid copy.
void operator=(const DaemonTimeHandler&) = delete; //!< Avoid copy.

  /** brief Parametrized constructor
   * param daemon Daemon to be executed
   */
	DaemonTimeHandler(std::shared_ptr<Daemon> daemon) : d(daemon) {}

  /** brief Run daemon
   *  param time not used
   */
	void run(uint64_t) {
    d->run();
	}

private:
	std::shared_ptr<Daemon> d;
};

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_TIME_DAEMONTIMEHANDLER_H
