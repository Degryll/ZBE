/**
 * Copyright 2015 Batis Degryll Ludo
 * @file BroadcastIH.h
 * @since 2018-04-23
 * @date 2018-04-23
 * @author Batis Degryll Ludo
 * @brief Input handler that stores other handlers and, when called, broadcasts the call to all stored handlers.
 * of the loaded image definition.
 */

#ifndef ZBE_EVENTS_HANDLERS_INPUT_BROADCASTIH
#define ZBE_EVENTS_HANDLERS_INPUT_BROADCASTIH

#include <vector>

#include "ZBE/core/events/handlers/InputHandler.h"

namespace zbe {

class BroadcastIH : public InputHandler {
	public:

  	BroadcastIH() : ihs() {}
    ~BroadcastIH() {}

  	void run(float status) {
      for (auto ih : ihs){
        ih->run(status);
      }
  	}

    void addHandler(std::shared_ptr<InputHandler> ih){
      ihs.push_back(ih);
    }

	private:
    std::vector<std::shared_ptr<InputHandler> > ihs;

};
}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_INPUT_BROADCASTIH
