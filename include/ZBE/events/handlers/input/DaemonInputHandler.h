/**
 * Copyright 2012 Batis Degryll Ludo
 * @file DaemonInputHandler.h
 * @since 2017-10-29
 * @date 2017-10-29
 * @author Batis Degrill Ludo
 * @brief Input handler capable of run a daemon.
 */

#ifndef ZBE_EVENTS_HANDLERS_INPUT_DAEMONINPUTHANDLER_H
#define ZBE_EVENTS_HANDLERS_INPUT_DAEMONINPUTHANDLER_H

#include "ZBE/core/events/handlers/InputHandler.h"

#include "ZBE/core/daemons/Daemon.h"

namespace zbe {

class DaemonInputHandler : public InputHandler {
  public:
	DaemonInputHandler(const DaemonInputHandler&) = delete;
	void operator=(const DaemonInputHandler&) = delete;

  	DaemonInputHandler(std::shared_ptr<Daemon> daemon):d(daemon) {}

  	void run(float) {
      d->run();
  	}

  private:
  	std::shared_ptr<Daemon> d;
};

} //namespace zbe

#endif //ZBE_EVENTS_HANDLERS_INPUT_DAEMONINPUTHANDLER_H
