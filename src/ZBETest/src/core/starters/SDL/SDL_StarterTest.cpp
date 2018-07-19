#include "gtest/gtest.h"

#include "ZBE/SDL/starters/SDL_Starter.h"

TEST(SDL_Starter, CheckSubsystems) {
  zbe::SDL_Starter &sdl1 = zbe::SDL_Starter::getInstance(SDL_INIT_VIDEO);

  Uint32 ssi = SDL_WasInit(SDL_INIT_EVERYTHING);

  EXPECT_FALSE(ssi & SDL_INIT_TIMER) << "TIMER is not initialized.";
  EXPECT_FALSE(ssi & SDL_INIT_AUDIO) << "AUDIO is not initialized.";
  EXPECT_TRUE(ssi & SDL_INIT_VIDEO) << "VIDEO is initialized.";
  EXPECT_FALSE(ssi & SDL_INIT_JOYSTICK) << "JOYSTICK is not initialized.";
  EXPECT_FALSE(ssi & SDL_INIT_HAPTIC) << "HAPTIC is not initialized.";
  EXPECT_FALSE(ssi & SDL_INIT_GAMECONTROLLER) << "GAMECONTROLLER is not initialized.";
  EXPECT_TRUE(ssi & SDL_INIT_EVENTS) << "EVENTS is initialized.";
  EXPECT_FALSE(ssi == SDL_INIT_EVERYTHING) << "EVERYTHING is not initialized.";

  //zbe::SDL_Starter &sdl2 = zbe::SDL_Starter::getInstance(SDL_INIT_AUDIO);
  zbe::SDL_Starter::getInstance(SDL_INIT_AUDIO);
  ssi = SDL_WasInit(SDL_INIT_EVERYTHING);

  EXPECT_FALSE(ssi & SDL_INIT_TIMER) << "TIMER is not initialized.";
  EXPECT_TRUE(ssi & SDL_INIT_AUDIO) << "AUDIO is initialized.";
  EXPECT_TRUE(ssi & SDL_INIT_VIDEO) << "VIDEO is initialized.";
  EXPECT_FALSE(ssi & SDL_INIT_JOYSTICK) << "JOYSTICK is not initialized.";
  EXPECT_FALSE(ssi & SDL_INIT_HAPTIC) << "HAPTIC is not initialized.";
  EXPECT_FALSE(ssi & SDL_INIT_GAMECONTROLLER) << "GAMECONTROLLER is not initialized.";
  EXPECT_TRUE(ssi & SDL_INIT_EVENTS) << "EVENTS is initialized.";
  EXPECT_FALSE(ssi == SDL_INIT_EVERYTHING) << "EVERYTHING is not initialized.";

  sdl1.quitSubSystem(SDL_INIT_VIDEO);
  //sdl2.quitSubSystem(SDL_INIT_VIDEO);
  ssi = SDL_WasInit(SDL_INIT_EVERYTHING);

  EXPECT_FALSE(ssi & SDL_INIT_TIMER) << "TIMER is not initialized.";
  EXPECT_TRUE(ssi & SDL_INIT_AUDIO) << "AUDIO is initialized.";
  EXPECT_FALSE(ssi & SDL_INIT_VIDEO) << "VIDEO is not initialized.";
  EXPECT_FALSE(ssi & SDL_INIT_JOYSTICK) << "JOYSTICK is not initialized.";
  EXPECT_FALSE(ssi & SDL_INIT_HAPTIC) << "HAPTIC is not initialized.";
  EXPECT_FALSE(ssi & SDL_INIT_GAMECONTROLLER) << "GAMECONTROLLER is not initialized.";
  EXPECT_FALSE(ssi & SDL_INIT_EVENTS) << "EVENTS is initialized.";
  EXPECT_FALSE(ssi == SDL_INIT_EVERYTHING) << "EVERYTHING is not initialized.";

  sdl1.quit();
  ssi = SDL_WasInit(SDL_INIT_EVERYTHING);

  EXPECT_FALSE(ssi & SDL_INIT_TIMER) << "TIMER is not initialized.";
  EXPECT_FALSE(ssi & SDL_INIT_AUDIO) << "AUDIO is not initialized.";
  EXPECT_FALSE(ssi & SDL_INIT_VIDEO) << "VIDEO is not initialized.";
  EXPECT_FALSE(ssi & SDL_INIT_JOYSTICK) << "JOYSTICK is not initialized.";
  EXPECT_FALSE(ssi & SDL_INIT_HAPTIC) << "HAPTIC is not initialized.";
  EXPECT_FALSE(ssi & SDL_INIT_GAMECONTROLLER) << "GAMECONTROLLER is not initialized.";
  EXPECT_FALSE(ssi & SDL_INIT_EVENTS) << "EVENTS is not initialized.";
  EXPECT_FALSE(ssi == SDL_INIT_EVERYTHING) << "EVERYTHING is not initialized.";

  zbe::SDL_Starter &sdl3 = zbe::SDL_Starter::getInstance(SDL_INIT_EVERYTHING);
  ssi = SDL_WasInit(SDL_INIT_EVERYTHING);

  EXPECT_TRUE(ssi & SDL_INIT_TIMER) << "TIMER is initialized.";
  EXPECT_TRUE(ssi & SDL_INIT_AUDIO) << "AUDIO is initialized.";
  EXPECT_TRUE(ssi & SDL_INIT_VIDEO) << "VIDEO is initialized.";
  EXPECT_TRUE(ssi & SDL_INIT_JOYSTICK) << "JOYSTICK is initialized.";
  EXPECT_TRUE(ssi & SDL_INIT_HAPTIC) << "HAPTIC is initialized.";
  EXPECT_TRUE(ssi & SDL_INIT_GAMECONTROLLER) << "GAMECONTROLLER is initialized.";
  EXPECT_TRUE(ssi & SDL_INIT_EVENTS) << "EVENTS is initialized.";
  EXPECT_TRUE(ssi == SDL_INIT_EVERYTHING) << "EVERYTHING is initialized.";

  sdl3.quit();
}
