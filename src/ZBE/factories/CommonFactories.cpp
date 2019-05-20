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

#include "ZBE/factories/implementations/events/handlers/time/DaemonRecurrentTimeHandlerFtry.h"
#include "ZBE/factories/implementations/events/handlers/time/DaemonTimeHandlerFtry.h"
#include "ZBE/factories/implementations/events/handlers/time/TicketEraserFtry.h"

#include "ZBE/factories/implementations/events/handlers/actuators/DmnSelectorAtorFtry.h"
#include "ZBE/factories/implementations/events/handlers/actuators/StateChangerAtorFtry.h"

namespace zbe {

void CommonFactories::load() {
  auto& factories = RsrcStore<Factory>::getInstance();

  // --- Daemons
//  factories.insert("DmnFtry.BehaviorDmnFtry", std::make_shared<BehaviorDmnFtry>());
  factories.insert("DmnFtry.MainLoopExitFtry", std::make_shared<MainLoopExitFtry>());
  factories.insert("DmnFtry.MainLoopFtry", std::make_shared<MainLoopFtry>());
  factories.insert("DmnFtry.MasterDmnFtry", std::make_shared<MasterDmnFtry>());
  factories.insert("DmnFtry.StateMachineDmnFtry", std::make_shared<StateMachineDmnFtry>());

  // --- Events
  // --- --- Event generators
//  factories.insert("EvGnFtry.InteractionEvGnFtry", std::make_shared<InteractionEvGnFtry>());
  // --- --- Event time handlers
  factories.insert("IHFtry.BroadcastIHFtry", std::make_shared<BroadcastIHFtry>());
  factories.insert("IHFtry.DaemonClickIHFtry", std::make_shared<DaemonClickIHFtry>());
  factories.insert("IHFtry.DaemonIHFtry", std::make_shared<DaemonIHFtry>());
  factories.insert("IHFtry.InputToValueFtry", std::make_shared<InputToValueFtry>());
  // --- --- Event time handlers
  factories.insert("THFtry.DaemonRecurrentTimeHandlerFtry", std::make_shared<DaemonRecurrentTimeHandlerFtry>());
  factories.insert("THFtry.DaemonTimeHandlerFtry", std::make_shared<DaemonTimeHandlerFtry>());
  factories.insert("THFtry.TicketEraserFtry", std::make_shared<TicketEraserFtry>());

}

}  // namespace zbe
