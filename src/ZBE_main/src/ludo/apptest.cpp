#include "ludo/apptest.h"

#include <iostream>
#include <cstdio>

#include "ZBE/core/zbe.h"
#include "ZBE/factories/BaseFactories.h"
#include "ZBE/factories/ZBEFactories.h"
#include "ZBE/glTF/GLTFFactories.h"
#include "ZBE/JSON/factories/JSONFactories.h"
#include "ZBE/SDL/factories/SDLFactories.h"
#include "ZBE/OGL/factories/OGLFactories.h"
#include "ZBE/resources/loaders/implementations/JSONAppLoader.h"

namespace ludo {
int apptest(int /*argc*/, char** /*argv*/) {
   using namespace zbe;
   printf("Hello ludo app\n");
   BaseFactories::load();
   SDLFactories::load();
   OGLFactories::load();
   GLTFFactories::load();
   ZBEFactories::load();
   JSONFactories::load();
   // Load App.
   std::cout << SysError::getFirstErrorString() << "\n";
   JSONAppLoader appLoader;
   appLoader.load("data/ludoapp/app//ludo_001.json");
   std::cout << SysError::getFirstErrorString() << "\n";
   // Run App.
   auto d = RsrcStore<Daemon>::getInstance().get("Daemon.Main");
   std::cout << SysError::getFirstErrorString() << "\n";
   d->run();
   return 0;
}

} //namespace Ludo
