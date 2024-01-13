/**
 * Copyright 2012 Batis Degryll Ludo
 * @file CommonFactories.cpp
 * @since 2019-02-20
 * @date 2019-02-20
 * @author Ludo Degryll Batis
 * @brief Daemon capable of load all common factories.
 */

#include "ZBE/factories/CommonFactories.h"

#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/factories/implementations/behaviors/StateLTEraserBhvFtry.h"
#include "ZBE/factories/implementations/behaviors/StateSetterBhvFtry.h"

#include "ZBE/factories/implementations/daemons/BehaviorDmnFtry.h"
#include "ZBE/factories/implementations/daemons/MainLoopExitFtry.h"
#include "ZBE/factories/implementations/daemons/MainLoopFtry.h"
#include "ZBE/factories/implementations/daemons/MasterDmnFtry.h"
#include "ZBE/factories/implementations/daemons/StateMachineDmnFtry.h"

//#include "ZBE/factories/implementations/events/generators/InteractionEvGnFtry.h"

#include "ZBE/factories/implementations/events/handlers/input/BroadcastIHFtry.h"
#include "ZBE/factories/implementations/events/handlers/input/DaemonClickIHFtry.h"
#include "ZBE/factories/implementations/events/handlers/input/DaemonIHFtry.h"
#include "ZBE/factories/implementations/events/handlers/input/InputToValueFtry.h"

#include "ZBE/factories/implementations/events/handlers/time/DaemonTimeHandlerFtry.h"
#include "ZBE/factories/implementations/events/handlers/time/TicketEraserFtry.h"

#include "ZBE/factories/implementations/events/handlers/actuators/DmnSelectorAtorFtry.h"
#include "ZBE/factories/implementations/events/handlers/actuators/StateChangerAtorFtry.h"

namespace zbe {

void CommonFactories::load() {
//   auto& factories = RsrcStore<Factory>::getInstance();
// //------------------------------------ COMMON ----------------------------------
//   // --- Daemons
//   //  factories.insert("DmnFtry.BehaviorDmnFtry", std::make_shared<BehaviorDmnFtry>());
//   factories.insert("MainLoopExitFtry", std::make_shared<MainLoopExitFtry>());
//   factories.insert("MainLoopFtry", std::make_shared<MainLoopFtry>());
//   factories.insert("MasterDmnFtry", std::make_shared<MasterDmnFtry>());
//   factories.insert("StateMachineDmnFtry", std::make_shared<StateMachineDmnFtry>());
//
//   // --- Events
//   // --- --- Event generators
//   //  factories.insert("EvGnFtry.InteractionEvGnFtry", std::make_shared<InteractionEvGnFtry>());
//   // --- --- Event time handlers
//   factories.insert("BroadcastIHFtry", std::make_shared<BroadcastIHFtry>());
//   factories.insert("DaemonClickIHFtry", std::make_shared<DaemonClickIHFtry>());
//   factories.insert("DaemonIHFtry", std::make_shared<DaemonIHFtry>());
//   factories.insert("InputToValueFtry", std::make_shared<InputToValueFtry>());
//   // --- --- Event time handlers
//   factories.insert("DaemonRecurrentTimeHandlerFtry", std::make_shared<DaemonRecurrentTimeHandlerFtry>());
//   factories.insert("DaemonTimeHandlerFtry", std::make_shared<DaemonTimeHandlerFtry>());
//   factories.insert("TicketEraserFtry", std::make_shared<TicketEraserFtry>());
// //------------------------------------- EXTRA ----------------------------------
//
//   TFAECDrawablesFtry -> ZBE
//   SDLWindowFtry -> SDL
//   JSONImgDefLoaderFtry -> JSON
//   SDLImgLoaderFtry -> SDL
//   ResourcesFtry -> BASE
//   MainLoopFtry -> BASE
//   ValueUFtry -> BASE (ValueIFtry, ValueFFtry, ...)
//   SDLSysTimeFtry -> SDL
//   BasicPreLoopSDLDaemonFtry -> SDL
//   BasicPostLoopSDLDaemonFtry -> SDL
//   TimeEventGeneratorFtry -> BASE
//   MainExitDaemonFry -> BASE
//   DaemonTimeHandlerFtry -> BASE
//   SpriteSheetSDLDrawerFtry -> SDL
//   BehaviorDmnFtry -> ZBE
//   SmplAnimSprtFtry -> ZBE
//   Allyour -> BASE //are belong to us
}

}  // namespace zbe
