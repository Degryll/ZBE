/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ZBNoidTitleBuilder.cpp
 * @since 2017-12-08
 * @date 2017-12-08
 * @author Degryll Ludo Batis
 * @brief Defines a daemon that ends the game if the number of lifes reaches 0 in zombienoid game.
 */

#include "zombienoid/daemons/ZBNoidTitleBuilder.h"

#include <memory>

#include "ZBE/core/system/MainLoop.h"
#include "ZBE/core/system/SysIdGenerator.h"
#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/daemons/MainLoopExit.h"
#include "ZBE/core/zbe.h"

#include "ZBE/events/handlers/input/InputToValue.h"

#include "ZBE/SDL/drawers/SpriteSheetSDLDrawer.h"
#include "ZBE/SDL/drawers/SingleTextSDLDrawer.h"

#include "zombienoid/ZBNoid.h"


namespace zombienoid {

void ZBNoidTitleBuilder::run() {
  using namespace zbe;
  // ResourceManager's
  ResourceManager<Daemon>& daemonRsrc = ResourceManager<Daemon>::getInstance();
  ResourceManager<Behavior<AnimatedSprite> >& asDrawerRsrc = ResourceManager<Behavior<AnimatedSprite> >::getInstance();
  ResourceManager<Behavior<SingleTextSprite> >& stsDrawerRsrc = ResourceManager<Behavior<SingleTextSprite> >::getInstance();
  // Common daemons
  std::shared_ptr<Daemon> preLoop = daemonResource.get(preLoopId);
  std::shared_ptr<Daemon> postLoop = daemonResource.get(postLoopId);
  // Event generators
  std::shared_ptr<DaemonMaster> eventGenerator(new DaemonMaster());
  eventGenerator->addDaemon(ieg);
  auto xvalue = std::make_shared<Value<double> >();
  auto yvalue = std::make_shared<Value<double> >();

  ieg->addHandler(ZBEK_MOUSE_OFFSET_X, new InputToValue(xvalue));
  ieg->addHandler(ZBEK_MOUSE_OFFSET_Y, new InputToValue(yvalue));

  // Empty behaviors
  std::shared_ptr<DaemonMaster> commonBehaviorMaster(new DaemonMaster());
  std::shared_ptr<DaemonMaster> reactBehaviorMaster(new DaemonMaster());
  // Drawing
  auto asDrawList = std::make_shared<TicketedFAEC<AnimatedSprite> >();
  auto spsDrawList = std::make_shared<TicketedFAEC<SingleTextSprite> >();
  uint64_t asDrwListId = SysIdGenerator::getId();
  uint64_t spsDrwListId = SysIdGenerator::getId();

  auto drawerDaemon = std::make_shared<BehaviorDaemon<AnimatedSprite, TicketedFAEC<AnimatedSprite> > >(asDrawerRsrc.get(asDrawerId), asDrwListId));
  auto writerDaemon = std::make_shared<BehaviorDaemon<SingleTextSprite, TicketedFAEC<SingleTextSprite> > >(stsDrawerRsrc.get(spsDrawerId), spsDrwListId));
  std::shared_ptr<DaemonMaster> drawMaster(new DaemonMaster());
  drawMaster->addDaemon(drawerDaemon);
  drawMaster->addDaemon(writerDaemon);

  std::shared_ptr<MainLoop> mainLoop = std::make_shared<MainLoop>(preLoop, postLoop, eventGenerator, commonBehaviorMaster, reactBehaviorMaster, drawMaster);

  // Buttons
  std::shared_ptr<Daemon> startButton = std::make_shared<MainLoopExit>(mainLoop, GAME_START_VALUE, exit);
  std::shared_ptr<Daemon> exitButton = std::make_shared<MainLoopExit>(mainLoop, GAME_EXIT_VALUE, exit);

  ButtonBuilder::aButton()
    .withInputEventGenerator(ieg)
    .withMouseX(xvalue)
    .withMouseY(yvalue)
    .withArea({462.0, 50.0, 100.0, 50.0})
    .withDaemon(startButton)
    .withGraphics(spriteSheetID)
    .withText("START")
    .withTextGraphics(fontID)
    .inDrawList(asDrwListId)
    .inTextList(spsDrwListId)
  .build();

  ButtonBuilder::aButton()
    .withInputEventGenerator(ieg)
    .withMouseX(xvalue)
    .withMouseY(yvalue)
    .withArea({462.0, 110.0, 100.0, 50.0})
    .withDaemon(exitButton)
    .withGraphics(spriteSheetID)
    .withText("EXIT")
    .withTextGraphics(fontID)
    .inDrawList(asDrwListId)
    .inTextList(spsDrwListId)
  .build();
}

}  // namespace zombienoid
