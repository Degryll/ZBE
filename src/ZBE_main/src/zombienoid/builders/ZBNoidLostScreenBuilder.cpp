/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ZBNoidLostScreenBuilder.cpp
 * @since 2017-12-08
 * @date 2017-12-08
 * @author Degryll Ludo Batis
 * @brief Defines a builder that creates the win screen.
 */

#include "zombienoid/builders/ZBNoidLostScreenBuilder.h"

#include <memory>

#include "zombienoid/ZBNoid.h"

namespace zombienoid {

std::shared_ptr<zbe::Daemon> ZBNoidLostScreenBuilder::build() {
  using namespace zbe;

  std::shared_ptr<DaemonMaster> preLoop(new DaemonMaster());
  std::shared_ptr<Daemon> postLoop = std::make_shared<BasicPostLoopSDLDaemon>(window);
  std::shared_ptr<DaemonMaster> eventGenerator(new DaemonMaster());
  std::shared_ptr<DaemonMaster> commonBehaviorMaster(new DaemonMaster());
  std::shared_ptr<DaemonMaster> reactBehaviorMaster(new DaemonMaster());
  std::shared_ptr<DaemonMaster> drawMaster(new DaemonMaster());;

  std::shared_ptr<MainLoop> mainLoop = std::make_shared<MainLoop>(preLoop, postLoop, eventGenerator, commonBehaviorMaster, reactBehaviorMaster, drawMaster);

  // Pre & post loop.
  std::shared_ptr<Daemon> prlsdl = std::make_shared<BasicPreLoopSDLDaemon>(window);
  std::shared_ptr<Daemon> prltd = std::make_shared<BasicPreLoopTimeDaemon>();
  preLoop->addDaemon(prlsdl);
  preLoop->addDaemon(prltd);

  // Event generators
  std::shared_ptr<InputEventGenerator> ieg(new InputEventGenerator(inputBuffer, ZBNCfg::INPUTEVENT));
  eventGenerator->addDaemon(ieg);

  std::shared_ptr<Value<double> > xvalue = std::make_shared<SimpleValue<double> >();
  std::shared_ptr<Value<double> > yvalue = std::make_shared<SimpleValue<double> >();

  ieg->addHandler(ZBEK_MOUSE_OFFSET_X, new InputToValue(xvalue));
  ieg->addHandler(ZBEK_MOUSE_OFFSET_Y, new InputToValue(yvalue));
  BroadcastIH* brdcstHI = new BroadcastIH();
  ieg->addHandler(ZBEK_MOUSE_LEFT, brdcstHI);

  auto drawerDaemon = std::make_shared<BehaviorDaemon<AnimatedSprite, TicketedFAEC<AnimatedSprite> > >(std::make_shared<SpriteSheetSDLDrawer<AnimatedSprite> >(window) , ZBNCfg::LOST_BUTTONS_AS_LIST);
  auto writerDaemon = std::make_shared<BehaviorDaemon<SingleTextSprite, TicketedFAEC<SingleTextSprite> > >(std::make_shared<SingleTextSDLDrawer>(window) , ZBNCfg::LOST_BUTTONS_TS_LIST);
  drawMaster->addDaemon(drawerDaemon);
  drawMaster->addDaemon(writerDaemon);

  // Buttons
  std::shared_ptr<Daemon> goMainTitle = std::make_shared<MainLoopExit>(mainLoop, ZBNCfg::rmVInt64.get(ZBNCfg::GAMESTATE), MAINTITLE);

  ButtonBuilder::aButton()
    .withBroadcastHI(brdcstHI)
    .withMouseX(xvalue)
    .withMouseY(yvalue)
    .withArea(Region2D({442.0, 150.0}, {140.0, 80.0}))
    .withDaemon(goMainTitle)
    .withGraphics(ZBNCfg::BUTTON_SS)
    .withText("YOU LOSE!")
    .withTextGraphics(rsrcIDDic->getId(ZBNCfg::TEXT_FONT))
    .inDrawList(ZBNCfg::LOST_BUTTONS_AS_LIST)
    .inTextList(ZBNCfg::LOST_BUTTONS_TS_LIST)
  .build();

  return mainLoop;
}

}  // namespace zombienoid