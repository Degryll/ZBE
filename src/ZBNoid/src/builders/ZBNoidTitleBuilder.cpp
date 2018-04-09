/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ZBNoidTitleBuilder.cpp
 * @since 2017-12-08
 * @date 2017-12-08
 * @author Degryll Ludo Batis
 * @brief Defines a builder that creates the title screen.
 */

#include "builders/ZBNoidTitleBuilder.h"

#include <memory>

#include "ZBNoid.h"

namespace zombienoid {

std::shared_ptr<zbe::Daemon> ZBNoidTitleBuilder::build() {
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

  auto drawerDaemon = std::make_shared<BehaviorDaemon<TicketedFAEC<AnimatedSprite>, AnimatedSprite > >(std::make_shared<SpriteSheetSDLDrawer<AnimatedSprite> >(window) , ZBNCfg::TITLE_BUTTONS_AS_LIST);
  auto writerDaemon = std::make_shared<BehaviorDaemon<TicketedFAEC<SingleTextSprite>, SingleTextSprite > >(std::make_shared<SingleTextSDLDrawer>(window) , ZBNCfg::TITLE_BUTTONS_TS_LIST);
  drawMaster->addDaemon(drawerDaemon);
  drawMaster->addDaemon(writerDaemon);

  // Buttons
  std::shared_ptr<Daemon> startButton = std::make_shared<MainLoopExit>(mainLoop, ZBNCfg::rmVInt64.get(ZBNCfg::GAMESTATE), START);
  std::shared_ptr<Daemon> exitButton = std::make_shared<MainLoopExit>(mainLoop, ZBNCfg::rmVInt64.get(ZBNCfg::GAMESTATE), END);

  ButtonBuilder::aButton()
    .withBroadcastHI(brdcstHI)
    .withMouseX(xvalue)
    .withMouseY(yvalue)
    .withArea(Region2D({462.0, 150.0}, {100.0, 50.0}))
    .withDaemon(startButton)
    .withGraphics(ZBNCfg::BUTTON_SS)
    .withText("START")
    .withTextGraphics(rsrcIDDic->getId(ZBNCfg::TEXT_FONT))
    .inDrawList(ZBNCfg::TITLE_BUTTONS_AS_LIST)
    .inTextList(ZBNCfg::TITLE_BUTTONS_TS_LIST)
  .build();

  ButtonBuilder::aButton()
    .withBroadcastHI(brdcstHI)
    .withMouseX(xvalue)
    .withMouseY(yvalue)
    .withArea(Region2D({462.0, 210.0}, {100.0, 50.0}))
    .withDaemon(exitButton)
    .withGraphics(ZBNCfg::BUTTON_SS)
    .withText("EXIT")
    .withTextGraphics(rsrcIDDic->getId(ZBNCfg::TEXT_FONT))
    .inDrawList(ZBNCfg::TITLE_BUTTONS_AS_LIST)
    .inTextList(ZBNCfg::TITLE_BUTTONS_TS_LIST)
  .build();

  return mainLoop;
}

}  // namespace zombienoid
