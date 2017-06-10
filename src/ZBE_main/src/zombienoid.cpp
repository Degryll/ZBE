#include "zombienoid.h"

#include <memory>

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/daemons/DaemonMaster.h"

#include "ZBE/core/events/generators/InputEventGenerator.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "ZBE/core/events/generators/InteractionEventGenerator.h"
#include "ZBE/core/events/generators/util/BaseCollisionSelector.h"

#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/entities/avatars/Collisionator.h"

#include "ZBE/core/tools/containers/ListJoint.h"
#include "ZBE/core/tools/containers/TicketedForwardList.h"

#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/core/io/InputBuffer.h"

#include "ZBE/SDL/system/SDLWindow.h"
#include "ZBE/SDL/system/SDLEventDispatcher.h"

#include "ZBE/SDL/tools/SDLTimer.h"



namespace zombienoid {

class ZombieBallReactor;

using namespace zbe;

template <typename T>
using TicketedFAE = TicketedForwardList<AvatarEntity<T> >;

template <typename T>
using JointAE = ListTicketedJoint<TicketedFAE<T>, std::shared_ptr<AvatarEntity<T> > >;
using InteractionGenerator = InteractionEventGenerator<
      ZombieBallReactor, CollisionSelector<ZombieBallReactor>,
      JointAE<Collisioner<ZombieBallReactor> >,
  		JointAE<Collisionator<ZombieBallReactor> >
    >;

int zombienoidmain(int, char*[]) {
  enum {
    WIDTH = 1024,
    HEIGHT = 768
  };
  const int INPUTEVENT = SysIdGenerator::getId();
  const int TIMEEVENT = SysIdGenerator::getId();

  const int COLLISIONEVENT = SysIdGenerator::getId();
  const int CTJOINT = SysIdGenerator::getId();

  SDLWindow window(WIDTH, HEIGHT);

  std::shared_ptr<DaemonMaster> eventGenerator(new DaemonMaster());

  SDLEventDispatcher& sdlEDispatcher = SDLEventDispatcher::getInstance();
  InputBuffer* inputBuffer = sdlEDispatcher.getInputBuffer();
  std::shared_ptr<InputEventGenerator> ieg(new InputEventGenerator(inputBuffer, INPUTEVENT));

  std::shared_ptr<TimeEventGenerator> teg(new TimeEventGenerator(TIMEEVENT));

  std::shared_ptr<InteractionGenerator> iaeg(new InteractionGenerator(CTJOINT, COLLISIONEVENT, new BaseCollisionSelector<ZombieBallReactor>()));

  eventGenerator->addDaemon(ieg);
  eventGenerator->addDaemon(teg);
  eventGenerator->addDaemon(iaeg);

  ResourceManager<JointAE<Collisionator<ZombieBallReactor> > >& lmjctz = ResourceManager<JointAE<Collisionator<ZombieBallReactor> > >::getInstance();
  //std::shared_ptr<JointAE<Collisionator<ZombieBallReactor> > > ctJoint(new JointAE<Collisionator<ZombieBallReactor> >());
  std::shared_ptr<JointAE<Collisionator<ZombieBallReactor> > > ctJoint (new JointAE<Collisionator<ZombieBallReactor> >());
  lmjctz.insert(CTJOINT, ctJoint);

  Timer *sysTimer = new SDLTimer(true);
  SysTime &sysTime = SysTime::getInstance();
  sysTime.setSystemTimer(sysTimer);


  return 0;
}

} //namespace zombieBall
