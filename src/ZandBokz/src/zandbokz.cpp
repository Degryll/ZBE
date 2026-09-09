/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ZandBokz.cpp
 * @since 2018-03-30
 * @date 2018-03-30
 * @author Ludo
 * @brief Main file for ZandBokz game.
 */


 #define SDL_MAIN_HANDLED
#include <chrono>
#include <ctime>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "ZBE/core/zbe.h"
#include "ZBE/factories/BaseFactories.h"
#include "ZBE/factories/ZBEFactories.h"
#include "ZBE/glTF/GLTFFactories.h"
#include "ZBE/JSON/factories/JSONFactories.h"
#include "ZBE/SDL/factories/SDLFactories.h"
#include "ZBE/OGL/factories/OGLFactories.h"
#include "ZBE/OAL/factories/OALFactories.h"
#include "ZBE/ImGui/factories/ImGuiFactories.h"

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

// #include <SDL.h>
// #include <GL/glew.h>
// #include "imgui.h"
// #include "backends/imgui_impl_sdl2.h"
// #include "backends/imgui_impl_opengl3.h"
// #include <stdio.h>

namespace {

void archivePreviousLog() {
  namespace fs = std::filesystem;
  const fs::path logPath{"logs/zbe.log"};

  if (!fs::exists(logPath)) {
    return;
  }

  const auto now = std::chrono::system_clock::now();
  const auto time = std::chrono::system_clock::to_time_t(now);
  std::tm localTime{};
#ifdef _WIN32
  localtime_s(&localTime, &time);
#else
  localtime_r(&time, &localTime);
#endif

  std::ostringstream suffix;
  suffix << std::put_time(&localTime, "%Y%m%d-%H%M%S")
         << '-' << std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000;
  const fs::path archivedPath = logPath.parent_path() / ("zbe.log." + suffix.str());

  fs::rename(logPath, archivedPath);
}

} // namespace

int main(int /*argc*/, char** /*argv*/) {
//   // 1. Inicializar SDL con video
//     if (SDL_Init(SDL_INIT_VIDEO) != 0)
//     {
//         printf("Error inicializando SDL: %s\n", SDL_GetError());
//         return -1;
//     }

//     // Configurar OpenGL
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

//     // 2. Crear ventana
//     SDL_Window* window = SDL_CreateWindow("Dear ImGui + SDL2 + GLEW",
//         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
//         1280, 720,
//         SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
//     if (!window)
//     {
//         printf("Error creando ventana: %s\n", SDL_GetError());
//         return -1;
//     }

//     // 3. Crear contexto OpenGL
//     SDL_GLContext gl_context = SDL_GL_CreateContext(window);
//     SDL_GL_MakeCurrent(window, gl_context);
//     SDL_GL_SetSwapInterval(1); // V-Sync

//     // 4. Inicializar GLEW
//     glewExperimental = GL_TRUE;
//     if (glewInit() != GLEW_OK)
//     {
//         printf("Error inicializando GLEW\n");
//         return -1;
//     }

//     // 5. Inicializar ImGui
//     IMGUI_CHECKVERSION();
//     ImGui::CreateContext();
//     ImGuiIO& io = ImGui::GetIO(); (void)io;

//     ImGui::StyleColorsDark();
//     ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
//     ImGui_ImplOpenGL3_Init("#version 460");

//     // 6. Loop principal
//     bool show_demo_window = true;
//     bool running = true;
//     while (running)
//     {
//         SDL_Event event;
//         while (SDL_PollEvent(&event))
//         {
//             ImGui_ImplSDL2_ProcessEvent(&event);
//             if (event.type == SDL_QUIT)
//                 running = false;
//         }

//         // Iniciar frame ImGui
//         ImGui_ImplOpenGL3_NewFrame();
//         ImGui_ImplSDL2_NewFrame();
//         ImGui::NewFrame();

//         // Mostrar ventana demo
//         if (show_demo_window)
//             ImGui::ShowDemoWindow(&show_demo_window);

//         // Render
//         ImGui::Render();
//         int display_w, display_h;
//         SDL_GL_GetDrawableSize(window, &display_w, &display_h);
//         glViewport(0, 0, display_w, display_h);
//         glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
//         glClear(GL_COLOR_BUFFER_BIT);
//         ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

//         SDL_GL_SwapWindow(window);
//     }

//     // 7. Limpieza
//     ImGui_ImplOpenGL3_Shutdown();
//     ImGui_ImplSDL2_Shutdown();
//     ImGui::DestroyContext();

//     SDL_GL_DeleteContext(gl_context);
//     SDL_DestroyWindow(window);
//     SDL_Quit();

//     return 0;
  archivePreviousLog();
  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/zbe.log", 1024*1024*100, 10);
  auto logger = std::make_shared<spdlog::logger>("multi_sink", spdlog::sinks_init_list{console_sink, rotating_sink});

  spdlog::set_default_logger(logger);
  spdlog::default_logger()->set_level(spdlog::level::trace);

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
  SPDLOG_TRACE("Hello ZandBokz\n");
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
  SPDLOG_INFO("Base loaded");
  OGLFactories::load(factories);
  SPDLOG_INFO("OGL");
  GLTFFactories::load(factories);
  SPDLOG_INFO("GLTF");
  OALFactories::load(factories);
  SPDLOG_INFO("OAL");
  ZBEFactories::load(factories);
  SPDLOG_INFO("ZBE");
  JSONFactories::load(factories);
  SPDLOG_INFO("JSON");
  ZandBokzFactories::load(factories);
  SPDLOG_INFO("ZandBokz");
  SDLFactories::load(factories);
  SPDLOG_INFO("SDL");
  ImGuiFactories::load(factories);
  SPDLOG_INFO("ImGui");

  // TODO llevar a factoria
  OALContextDaemon oalContextDmn;
  oalContextDmn.run();
  
  appLoader.load("data/ZandBokz/app/main_002.json");
  // Run App.
  auto d = RsrcStore<Daemon>::getInstance().get("Daemon.Main");
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
