/**
 * Copyright 2012 Batis Degryll Ludo
 * @file DaemonTimeHandler.h
 * @since 2017-10-25
 * @date 2017-10-25
 * @author Batis Degrill Ludo
 * @brief Time handler capable of run a daemon.
 */

#ifndef ZBE_EVENTS_HANDLERS_TIME_DAEMONTIMEHANDLER_H
#define ZBE_EVENTS_HANDLERS_TIME_DAEMONTIMEHANDLER_H

#include "ZBE/core/events/handlers/TimeHandler.h"

#include "ZBE/core/daemons/Daemon.h"

namespace zbe {

class DaemonTimeHandler : public TimeHandler {
  public:
	DaemonTimeHandler(const DaemonTimeHandler&) = delete;
	void operator=(const DaemonTimeHandler&) = delete;

  	DaemonTimeHandler(std::shared_ptr<Daemon> daemon):d(daemon) {}

  	void run(uint64_t) {
      d->run();
  	}

  private:
  	std::shared_ptr<Daemon> d;
};

} //namespace zbe

#endif //ZBE_EVENTS_HANDLERS_TIME_DAEMONTIMEHANDLER_H
