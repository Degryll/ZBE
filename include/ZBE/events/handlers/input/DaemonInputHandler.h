/**
 * Copyright 2012 Batis Degryll Ludo
 * @file DaemonInputHandler.h
 * @since 2017-10-29
 * @date 2018-02-25
 * @author Batis Degrill Ludo
 * @brief Input handler capable of run a daemon.
 */

#ifndef ZBE_EVENTS_HANDLERS_INPUT_DAEMONINPUTHANDLER_H
#define ZBE_EVENTS_HANDLERS_INPUT_DAEMONINPUTHANDLER_H


#include <memory>

#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/daemons/Daemon.h"

namespace zbe {

/** \brief Input handler capable of run a daemon.
 */
class DaemonInputHandler : public InputHandler {
public:

 /** \brief Constructs a DaemonInputHandler from a daemon.
	*  \param daemon daemon to be executed.
	*/
	DaemonInputHandler(std::shared_ptr<Daemon> daemon):d(daemon) {}

	/** \brief run daemon.
	 *  \param state not used
	 */
	void run(uint32_t, float) {
    d->run();
	}

private:
	std::shared_ptr<Daemon> d;
};

}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_INPUT_DAEMONINPUTHANDLER_H
