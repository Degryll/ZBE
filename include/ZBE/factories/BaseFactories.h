/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseFactories.h
 * @since 2019-09-12
 * @date 2019-09-12
 * @author Ludo Degryll Batis
 * @brief Daemon capable of load all base factories.
 */

#ifndef ZBE_FACTORIES_BASEFACTORIES_H_
#define ZBE_FACTORIES_BASEFACTORIES_H_

#include <string>

#include "ZBE/factories/Factory.h"
#include "ZBE/factories/implementations/RsrcFtry.h"
#include "ZBE/factories/implementations/entities/EntityFtry.h"
#include "ZBE/factories/implementations/GenericFtry.h"
#include "ZBE/factories/implementations/daemons/BehaviorDmnFtry.h"
#include "ZBE/factories/implementations/daemons/MainLoopExitFtry.h"
#include "ZBE/factories/implementations/daemons/MainLoopFtry.h"
#include "ZBE/factories/implementations/daemons/MasterDmnFtry.h"
#include "ZBE/factories/implementations/daemons/StateMachineDmnFtry.h"
#include "ZBE/factories/implementations/daemons/RsrcFolderLoaderDmnFtry.h"
#include "ZBE/factories/implementations/events/handlers/input/BroadcastIHFtry.h"
#include "ZBE/factories/implementations/events/handlers/input/DaemonClickIHFtry.h"
#include "ZBE/factories/implementations/events/handlers/input/DaemonIHFtry.h"
#include "ZBE/factories/implementations/events/handlers/input/InputToValueFtry.h"
#include "ZBE/factories/implementations/events/handlers/time/DaemonRecurrentTimeHandlerFtry.h"
#include "ZBE/factories/implementations/events/handlers/time/DaemonTimeHandlerFtry.h"
#include "ZBE/factories/implementations/events/handlers/time/TicketEraserFtry.h"
#include "ZBE/factories/implementations/events/handlers/actuators/DmnSelectorAtorFtry.h"
#include "ZBE/factories/implementations/events/handlers/actuators/StateChangerAtorFtry.h"
#include "ZBE/factories/implementations/events/generators/TimeEventGnFtry.h"

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/core/daemons/VoidDaemon.h"
#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Daemon capable of load all base factories.
 */
class ZBEAPI BaseFactories : public Daemon {
public:
  ~BaseFactories() {}

  /** \brief It will Load the factories calling the load method.
  */
  void run() {
    load();
  };

  /** \brief It loads all factories.
  */
  static void load(){
    auto& factories = RsrcStore<Factory>::getInstance();

    RsrcStore<ContextTime>::getInstance().insert("ContextTime.DEFAULT", SysTime::getInstance());
    RsrcStore<Daemon>::getInstance().insert("Daemon.DEFAULT", std::make_shared<VoidDaemon>());

    // --- Entities
    factories.insert("EntityFtry", std::make_shared<EntityFtry>());

    // --- Values
    factories.insert("ValueUFtry", std::make_shared<GenericFtry<Value<uint64_t>,SimpleValue<uint64_t>> >("ValueU","SimpleValueU"));
    factories.insert("ValueIFtry", std::make_shared<GenericFtry<Value<int64_t>,SimpleValue<int64_t> > >("ValueI","SimpleValueI"));
    factories.insert("ValueDFtry", std::make_shared<GenericFtry<Value<double>,SimpleValue<double> > >("ValueD","SimpleValueD"));
    factories.insert("ValueFFtry", std::make_shared<GenericFtry<Value<float>,SimpleValue<float> > >("ValueF","SimpleValueF"));

    factories.insert("ValueSFtry", std::make_shared<GenericFtry<Value<std::string>,SimpleValue<std::string> > >("ValueS","SimpleValueS"));
    factories.insert("ValueV2DFtry", std::make_shared<GenericFtry<Value<Vector2D>,SimpleValue<Vector2D> > >("ValueV2D","SimpleValueV2D"));
    factories.insert("ValueV3DFtry", std::make_shared<GenericFtry<Value<Vector3D>,SimpleValue<Vector3D> > >("ValueV3D","SimpleValueV3S"));

    // --- Daemons
    factories.insert("MainLoopExitFtry", std::make_shared<MainLoopExitFtry>());
    factories.insert("MainLoopFtry", std::make_shared<MainLoopFtry>());
    factories.insert("MasterDmnFtry", std::make_shared<MasterDmnFtry>());
    factories.insert("StateMachineDmnFtry", std::make_shared<StateMachineDmnFtry>());
    factories.insert("RsrcFolderLoaderDmnFtry", std::make_shared<RsrcFolderLoaderDmnFtry>());

    // --- Events
    // --- --- Event generators
    factories.insert("TimeEventGnFtry", std::make_shared<TimeEventGnFtry>());

    // --- --- Event input handlers
    factories.insert("BroadcastIHFtry", std::make_shared<BroadcastIHFtry>());
    factories.insert("DaemonClickIHFtry", std::make_shared<DaemonClickIHFtry>());
    factories.insert("DaemonIHFtry", std::make_shared<DaemonIHFtry>());
    factories.insert("InputToValueFtry", std::make_shared<InputToValueFtry>());
    // --- --- Event time handlers
    factories.insert("DaemonRecurrentTimeHandlerFtry", std::make_shared<DaemonRecurrentTimeHandlerFtry>());
    factories.insert("DaemonTimeHandlerFtry", std::make_shared<DaemonTimeHandlerFtry>());
    factories.insert("TicketEraserFtry", std::make_shared<TicketEraserFtry>());

    // --- Others
    factories.insert("RsrcFtry", std::make_shared<RsrcFtry>());


    // RsrcFolderLoaderDmnFtry -> BASE
    // MainLoopFtry -> BASE
    // MainLoopExitFtry -> BASE
    // ValueUFtry -> BASE (ValueIFtry, ValueFFtry, ...)
    //
    // TimeEventGnFtry -> BASE
    // DaemonTimeHandlerFtry -> BASE
    //
    // BehaviorDmnFtry -> BASE
  }

};

}  // namespace zbe

#endif  // ZBE_FACTORIES_BASEFACTORIES_H_