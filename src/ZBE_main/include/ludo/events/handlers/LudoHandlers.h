/**
 * Copyright 2012 Batis Degryll Ludo
 * @file LudoHandlers.h
 * @since 2017-02-25
 * @date 2017-02-25
 * @author Ludo
 * @brief Collection of zbe::InputHandler && zbe::TimeHandler for ludomain.
 */
#ifndef LUDO_EVENTS_HANDLERS_LUDOHANDLERS
#define LUDO_EVENTS_HANDLERS_LUDOHANDLERS

#include "ZBE/core/tools/containers/ListManager.h"
#include "ZBE/core/events/handlers/InputHandler.h"
#include "ZBE/core/events/handlers/TimeHandler.h"
#include "ZBE/SDL/starters/SDL_Starter.h"

namespace ludo {
/** \brief Actuator capable of making a BouncerCollisioner bounce in a Bounceable.
 */
template <typename R>
class LudoBallBouncer: public zbe::Actuator<zbe::Bouncer<2>, R> {
  public:
    void act(zbe::VoidReactObject<R>*) {
      zbe::Bouncer<2> * gb = zbe::Actuator<zbe::Bouncer<2>, R>::getCollisioner();
      zbe::CollisionData * cd = zbe::Actuator<zbe::Bouncer<2>, R>::getCollisionData();
      zbe::Vector<2> n = gb->getPosition() - cd->getPoint();
      gb->addNormal(n);
    }
};


class GraphicsSet : public zbe::InputHandler {
  public:
	GraphicsSet(const GraphicsSet&) = delete;
	void operator=(const GraphicsSet&) = delete;

  	GraphicsSet(uint64_t graphics, uint64_t id): graphics(graphics), id(id){
  	}

  	void run(float status) {
      if( status > 0.5f) {
        zbe::ListManager<std::forward_list<SetableGraphics*> >& lmSG = zbe::ListManager<std::forward_list<SetableGraphics*> >::getInstance();
        std::forward_list<SetableGraphics*>* setableGs = lmSG.get(id);
        for(auto sg : (*setableGs)){
            sg->setGraphics(graphics);
        }
      }
  	}

  private:
    uint64_t graphics;
    uint64_t id;
};
} //namespace ludo

#endif //LUDO_EVENTS_HANDLERS_LUDOHANDLERS
