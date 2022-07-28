/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ZandBokz.cpp
 * @since 2018-03-30
 * @date 2018-03-30
 * @author Ludo
 * @brief Main file for ZandBokz game.
 */

#include <iostream>

#include "ZBE/core/zbe.h"
#include "ZBE/factories/BaseFactories.h"
#include "ZBE/factories/ZBEFactories.h"
#include "ZBE/glTF/GLTFFactories.h"
#include "ZBE/JSON/factories/JSONFactories.h"
#include "ZBE/SDL/factories/SDLFactories.h"
#include "ZBE/OGL/factories/OGLFactories.h"
#include "ZBE/OAL/factories/OALFactories.h"
#include "ZBE/resources/loaders/implementations/JSONAppLoader.h"

#include "ZBE/core/events/interactionSystem.h"
#include "ZBE/core/events/interactionFunctions.h"
#include "ZBE/core/events/shapes.h"
#include "ZBE/core/events/traits.h"

#include "ZBE/JSON/JSONFactory.h"

#include "zandbokz.h"
#include "ZandBokzFactories.h"
#include "ZandBokzInteractionSystem.h"

int main(int /*argc*/, char** /*argv*/) {

   using namespace zbe;
   using namespace zandbokz;
   using namespace std::string_literals;

   init();
   printf("Hello ZandBokz\n");
   BaseFactories::load();
   printf("Base loaded\n");
   SDLFactories::load();
   printf("SDL\n");
   OGLFactories::load();
   printf("OGL\n");
   GLTFFactories::load();
   printf("GLTF\n");
   OALFactories::load();
   printf("OAL\n");
   ZBEFactories::load();
   printf("ZBE\n");
   JSONFactories::load();
   printf("JSON\n");
   ZandBokzFactories::load();
   printf("ZandBokz\n");

   // Esto deberia ir a un ZandBokzFactories.h
   // template <typename Selector, typename Overloaded, typename IData, typename ActorType, typename ReactorType, typename ...Shapes>
   using ZandBokzOverloaded = zbe::overloaded<zbe::MovingSphereFunctor>;
   using ZandBokzSelector = zbe::BaseSelector<zbe::InteractionSelector<zbe::CollisionData3D, ZandBokzOverloaded, zbe::MovingSphere>, ZandBokzOverloaded, zbe::MovingSphereFunctor>;
   using Solid = zbe::EmptyTrait;

   using ActorType = zbe::Actor<zbe::CollisionData3D, Solid>;
   using ReactorType = zbe::Reactor<zbe::CollisionData3D, Solid>;

   auto& factories = RsrcStore<Factory>::getInstance();
   factories.insert("MovingSphereCollideEventGeneratorFtry", std::make_shared<InteractionEventGeneratorFtry<ZandBokzSelector, ZandBokzOverloaded, zbe::CollisionData3D, ActorType, ReactorType, zbe::MovingSphere> >());
   // Load App.
   std::cout << SysError::getFirstErrorString() << "\n";
   JSONAppLoader appLoader;
   appLoader.load("data/ZandBokz/app/main_001.json");
   std::cout << SysError::getFirstErrorString() << "\n";
   // Run App.
   auto d = RsrcStore<Daemon>::getInstance().get("Daemon.Main");
   std::cout << SysError::getFirstErrorString() << "\n";
   d->run();
   return 0;


    // Flujo del juego
      // Llamar a la primera carga de factorias basicas. (CommonFactories)
      // Cargar primera aplicacion: LoadScreen.
        // Devolvera un demonio que cargara lo minimo para:
          // Pintar un pantalla de carga
            // Instanciar pintadores
            // Cargar carpetas de recursos
          // Cargar la siguiente aplicacion.
            // Factoria propias del juego.
            // Instaciar demonios RsrcLoader para segunda aplicacion

      // Cargar segunda aplicacion: Menu.
        // Tenemos factorias para las cosas que crean menus?

      // Cargar segunda aplicacion: juego.

    // Desarrollos necesarios
      // Cambiar factories por general? Necesitamos cargar assets en esa fase.
      // Factorias de ContextTime:SubordinateTime
      // Avatares nuevos: Todos construidos a partir de un Entity.
      // Declarar en CommonFactories factorias para:
        // values X
        // listas V
      // cambiar el campo "lists" del main.json por "containers" e incluir en el factorias de values.
      // Tenemos un demonio vacio?
      // Factorias sistema de menus
      // Factorias BasicPreLoopSDLDaemon/BasicPostLoopSDLDaemon
      // Quizas todas las factorias de entidades iniciales deban dejar tickets de estas en un RsrcStore de tickets.

    // Desarrollos deseados
      // Expandir interfaz de RsrcLoader para poder preguntar estado.
      // * Cada RsrcLoader es responsable de anotar su estado. struct done/total/msgId
      // Agregar descripcion a factoria en json
      // CommonResources incluye recursos por defecto en RsrcStores.
        // Ejemplo: "ContexTime.SysTime" siempre contiene el singleto de SysTime. (Quizas justo este ejemplo sea malo. No podemos jugarnosla a meter SysTime en un shared_ptr)
        // ... pues resulta que SysTime::getInstance() devuelve uns shared_ptr.

    // Chorrandeces
      // La pantalla de carga dice tontas mientras pasan las barras de progreso.
}
