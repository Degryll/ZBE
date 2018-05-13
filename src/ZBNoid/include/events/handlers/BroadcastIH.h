#ifndef ZOMBIENOID_EVENTS_HANDLERS_BROADCASTIH
#define ZOMBIENOID_EVENTS_HANDLERS_BROADCASTIH

#include <vector>

#include "ZBE/core/events/handlers/InputHandler.h"

namespace zombienoid {

class BroadcastIH : public zbe::InputHandler {
	public:

  	BroadcastIH() : ihs() {}
    ~BroadcastIH() {}

  	void run(uint32_t key, float status) {
      for (auto ih : ihs){
        ih->run(key, status);
      }
  	}

    void addHandler(std::shared_ptr<InputHandler> ih){
      ihs.push_back(ih);
    }

	private:
    std::vector<std::shared_ptr<InputHandler> > ihs;

};
} //namespace zombienoid

#endif //ZOMBIENOID_EVENTS_HANDLERS_BROADCASTIH
