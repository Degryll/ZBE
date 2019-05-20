/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SingleTextSDLDrawerFtry.cpp
 * @since 2019-03-19
 * @date 2019-03-19
 * @author Ludo Degryll Batis
 * @brief Factory for Single Text SDL Drawer.
 */
#include "ZBE/SDL/factories/drawers/SingleTextSDLDrawerFtry.h"

namespace zbe {

  void SingleTextSDLDrawerFtry::create(std::string name, uint64_t) {
   using namespace std::string_literals;

   std::shared_ptr<SingleTextSDLDrawer> ss = std::make_shared<SingleTextSDLDrawer>();
   drawerRsrc.insert("Drawer."s + name, ss);
   STSDLDrawerRsrc.insert("STSDLDrawer."s + name, ss);
 }

 void SingleTextSDLDrawerFtry::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);

  if(cfg) {
    auto j = *cfg;
    if (j["window"].is_string()){
     std::string windowName = j["window"].get<std::string>();
     auto w = windowRsrc.get(windowName);

     auto ssd = STSDLDrawerRsrc.get("STSDLDrawer."s + name);
     ssd->setWindow(w);

    } else {
      SysError::setError("SingleTextSDLDrawer config for "s + j["limit"].get<std::string>() + ": must be a string."s);
    }
  } else {
    SysError::setError("SingleTextSDLDrawer config for "s + name + " not found."s);
  }
 }
}  // namespace zbe
