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

#include "ZBE/core/system/system.h"

namespace zbe {

class ZBEAPI BroadcastIH : public InputHandler {
	public:

  	BroadcastIH() : ihs() {}
    ~BroadcastIH() {}

  	void run(uint32_t key, float state) {
      for (auto ih : ihs) {
        ih->run(key, state);
      }
  	}

    void addHandler(std::shared_ptr<InputHandler> ih) {
      ihs.push_back(ih);
    }

	private:
    std::vector<std::shared_ptr<InputHandler> > ihs;

};
}  // namespace zbe

#endif  // ZBE_EVENTS_HANDLERS_INPUT_BROADCASTIH
