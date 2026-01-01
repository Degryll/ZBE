/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ZandBokz.cpp
 * @since 2018-03-30
 * @date 2018-03-30
 * @author Ludo
 * @brief Main file for ZandBokz game.
 */


 #define SDL_MAIN_HANDLED
#include <iostream>
#include <string>

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

#include "ZBE/OAL/daemons/OALContextDaemon.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

int main(int /*argc*/, char** /*argv*/) {

  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/zbe.log", 1024*1024*10, 10);
  auto logger = std::make_shared<spdlog::logger>("multi_sink", spdlog::sinks_init_list{console_sink, rotating_sink});

  spdlog::set_default_logger(logger);

  // // TODO logs de prueba aquí.
  // SPDLOG_TRACE("This is a trace message.");
  // SPDLOG_DEBUG("This is a debug message.");
  // SPDLOG_INFO("This is an info message.");
  // SPDLOG_WARN("This is a warning message.");
  // SPDLOG_ERROR("This is an error message.");
  // SPDLOG_CRITICAL("This is a critical message.");

  using namespace zbe;
  using namespace zandbokz;
  using namespace std::string_literals;

  init(RsrcDictionary<ZBE_K>::getInstance());
  printf("Hello ZandBokz\n");
  JSONAppLoader appLoader;

  appLoader.setFactoryStore(&RsrcStore<Factory>::getInstance());
  appLoader.setConfigStore(&RsrcStore<nlohmann::json>::getInstance());
  appLoader.setV2DStore(&RsrcDictionary<Vector2D>::getInstance());
  appLoader.setV3DStore(&RsrcDictionary<Vector3D>::getInstance());
  appLoader.setIntStore(&RsrcDictionary<int64_t>::getInstance());
  appLoader.setUIntStore(&RsrcDictionary<uint64_t>::getInstance());
  appLoader.setFloatStore(&RsrcDictionary<float>::getInstance());
  appLoader.setDoubleStore(&RsrcDictionary<double>::getInstance());
  appLoader.setStringStore(&RsrcDictionary<std::string>::getInstance());
  appLoader.setCallableStore(&RsrcStore<Funct<void>>::getInstance());

  auto& factories = RsrcStore<Factory>::getInstance();

  BaseFactories::load(factories);
  printf("Base loaded %d\n", factories.contains("SimpleValueFtry"));
  OGLFactories::load(factories);
  printf("OGL %d\n", factories.contains("SimpleValueFtry"));
  GLTFFactories::load(factories);
  printf("GLTF %d\n", factories.contains("SimpleValueFtry"));
  OALFactories::load(factories);
  printf("OAL %d\n", factories.contains("SimpleValueFtry"));
  ZBEFactories::load(factories);
  printf("ZBE %d\n", factories.contains("SimpleValueFtry"));
  JSONFactories::load(factories);
  printf("JSON %d\n", factories.contains("SimpleValueFtry"));
  ZandBokzFactories::load(factories);
  printf("ZandBokz %d\n", factories.contains("SimpleValueFtry"));
  SDLFactories::load(factories);
  printf("SDL %d\n", factories.contains("SimpleValueFtry"));

  // TODO llevar a factoria
  OALContextDaemon oalContextDmn;
  oalContextDmn.run();

  std::cout << SysError::getFirstErrorString() << "\n";
  
  appLoader.load("data/ZandBokz/app/main_002.json");
  std::cout << SysError::getFirstErrorString() << "\n";
  // Run App.
  auto d = RsrcStore<Daemon>::getInstance().get("Daemon.Main");
  std::cout << SysError::getFirstErrorString() << "\n";
  d->run();
  return 0;


    // Flujo del juego
      // Llamar a la primera carga de factorias basicas.
      // Cargar primera aplicacion: zandbokz.
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
      // Declarar factorias para:
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
