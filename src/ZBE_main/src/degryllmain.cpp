#include "degryllmain.h"

//#include <cstdio>
//#include <cstdint>
//#include <memory>
//#include <string>
//#include <vector>
//
//#include <imgui.h>
//#include <imgui_impl_sdl.h>
//#include <imgui_impl_opengl3.h>
//
//#include <SDL3/SDL.h>
//#include <SDL3_ttf/SDL_ttf.h>
//
//#include <GL/glew.h>
//
//#include <chaiscript/chaiscript.hpp>
//
////#include "ZBE/core/zbe.h"
//#include "ZBE/core/entities/Entity.h"
//#include "ZBE/core/entities/avatars/Avatar.h"
//#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
//#include "ZBE/SDL/OGL/SDLOGLWindow.h"
//#include "ZBE/SDL/OGL/ImGui/SDLOGLImGuiWindow.h"
//
//#include "ZBE/core/tools/shared/Value.h"
//#include "ZBE/core/tools/shared/implementations/SimpleValue.h"
////#include "ZBE/core/events/handlers/InputHandler.h"
////#include "ZBE/core/entities/avatars/Avatar.h"
//
//#include "ZBE/core/tools/containers/TicketedForwardList.h"
//
//#include "ZBE/core/daemons/MainLoop.h"
//#include "ZBE/core/daemons/Daemon.h"
//#include "ZBE/core/daemons/DaemonMaster.h"
//#include "ZBE/core/daemons/Punishers.h"
//
//#include "ZBE/core/io/Input.h"
//
////#include "ZBE/core/events/generators/util/InputStatusManager.h"
//#include "ZBE/core/events/generators/InputEventGenerator.h"
////#include "ZBE/core/events/generators/TimeEventGenerator.h"
//
//#include "ZBE/SDL/tools/SDLTimer.h"
//#include "ZBE/OGL/daemons/SimpleImGuiTest.h"
//#include "ZBE/SDL/daemons/BasicPreLoopSDLDaemon.h"
//#include "ZBE/SDL/daemons/BasicPostLoopSDLDaemon.h"
//#include "ZBE/SDL/drawers/ConsoleTextSDLDrawer.h"
//#include "ZBE/SDL/drawers/SingleSpriteSDLDrawer.h"
//#include "ZBE/core/daemons/MainLoopExit.h"
//#include "ZBE/events/handlers/input/DaemonIH.h"
//#include "ZBE/events/handlers/input/AddText.h"
//#include "ZBE/events/handlers/input/ExecuteCommandIH.h"
//#include "ZBE/events/handlers/input/RemoveGlyphIH.h"
//#include "ZBE/events/handlers/input/ScrollIH.h"
//
//#include "ZBE/core/tools/math/math.h"
//#include "ZBE/core/system/SysTime.h"
//#include "ZBE/behaviors/CustomMotion.h"
//
//#include "ZBE/SDL/starters/SDL_Starter.h"
//
//#include "ZBE/ImGui/daemons/ImGuiPreLoopDaemon.h"
//#include "ZBE/ImGui/daemons/ImGuiPostLoopDaemon.h"
//#include "ZBE/SDL/events/SDLEventWatcher.h"
//#include "ZBE/SDL/events/KeyMouseEventWatcher.h"
//#include "ZBE/ImGui/events/ImGuiEventWatcher.h"
//
//#include "ZBE/entities/implementations/Console.h"

//class ChaiWarp {
//public:
//  ChaiWarp(std::shared_ptr<zbe::Value<zbe::Vector2D > > vv) : vv(vv) {}
//
//  void setX(double x) {
//    zbe::Vector2D aux(vv->get());
//    aux.x = x;
//    vv->set(aux);
//  }
//
//  void setY(double y) {
//    zbe::Vector2D aux(vv->get());
//    aux.y = y;
//    vv->set(aux);
//  }
//
//  void incrementX(double x) {
//    zbe::Vector2D aux(vv->get());
//    aux.x = aux.x + x;
//    vv->set(aux);
//  }
//
//  void incrementY(double y) {
//    zbe::Vector2D aux(vv->get());
//    aux.y = aux.y + y;
//    vv->set(aux);
//  }
//
//private:
//  std::shared_ptr<zbe::Value<zbe::Vector2D > > vv;
//};
//
//class ChaiWarpBhv {
//public:
//  ChaiWarpBhv(std::shared_ptr<zbe::CustomMotion<2> > cm) : cm(cm) {}
//
//  void setFunction(std::function<void(double &posx, double &posy, double &velx, double &vely, double &acelx, double &acely, double time)> f) {
//    cm->setFunction(f);
//  }
//
//private:
//  std::shared_ptr<zbe::CustomMotion<2> > cm;
//};
//
//void test2(double &posx, double &, double &velx, double &, double &acelx, double &, double time) {
//  acelx = 100.0 * (500.0 - 2.0 * posx + 140.0) / (500.0 - 140.0);
//  velx = velx + (acelx * time);
//  posx = posx + (velx * time);
//}
//
//void test(double &posx, double &, double &velx, double &, double &, double &, double time) {
//  posx = posx + (velx * time);
//  if (posx > 500) {
//    posx = 140 + posx - 500;
//  }
//}

//class SDLWindow2 {
//public:
//  SDLWindow2(const char* title, int x, int y, int width, int height, Uint32 window_flags = 0, Uint32 renderer_flags = 0)
//  : sdl(zbe::SDL_Starter::getInstance(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER)),
//    window(SDL_CreateWindow(title, x, y, width, height, window_flags | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI)),
//    renderer(SDL_CreateRenderer(window, -1, renderer_flags)),
//    gl_context(SDL_GL_CreateContext(window)) {
//
////    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
////      printf("Error: %s\n", SDL_GetError());
////      return;
////    }
////    //SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
////    window_flags = window_flags | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
////    window = SDL_CreateWindow(title, x, y, width, height, window_flags);
////    renderer = SDL_CreateRenderer(window, -1, renderer_flags);
////    //gl_context = SDL_GL_CreateContext(window);
//
//  }
//
//  SDL_Window* getSDL_Window() {
//    return window;
//  }
//
//  SDL_GLContext getGLContext() {
//    return gl_context;
//  }
//
//private:
//  zbe::SDL_Starter &sdl;
//  SDL_Window* window;
//  SDL_Renderer* renderer;
//  SDL_GLContext gl_context;
//};

//class IMWindow : public zbe::SDLOGLWindow {
//public:
//  IMWindow(const char* title, int x, int y, int width, int height, Uint32 window_flags = 0, Uint32 rederer_flags = 0) : SDLOGLWindow(title, x, y, width, height, window_flags | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI, rederer_flags)/*, gl_context(SDL_GL_CreateContext(this->getSDL_Window()))*/, io() {
//    const char* glsl_version = "#version 130";
//
//    // Setup Dear ImGui context
//    IMGUI_CHECKVERSION();
//    ImGui::CreateContext();
//    io = ImGui::GetIO(); (void)io;
//    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
//    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
//
//    // Setup Dear ImGui style
//    ImGui::StyleColorsDark();
//    //ImGui::StyleColorsClassic();
//
//    // Setup Platform/Renderer bindings
//    ImGui_ImplSDL2_InitForOpenGL(this->getSDL_Window(), this->getGLContext());
//    ImGui_ImplOpenGL3_Init(glsl_version);
//  }
//
//  int getDisplayX() {
//    return (int)io.DisplaySize.x;
//  }
//
//  int getDisplayY() {
//    return (int)io.DisplaySize.y;
//  }
//
//private:
//  ImGuiIO io;
//};

int degryllmain2(int, char*[]) {
//   const int WINDOWPOSX = 50;
//   const int WINDOWPOSY = 50;
//   const int WIDHT = 640;
//   const int HEIGHT = 480;
//   std::shared_ptr<zbe::SDLOGLImGuiWindow> window = std::make_shared<zbe::SDLOGLImGuiWindow>("Console", WINDOWPOSX, WINDOWPOSY, WIDHT, HEIGHT);
//
//   zbe::SDLEventDispatcher& sdlEDispatcher = zbe::SDLEventDispatcher::getInstance();
//   std::shared_ptr<zbe::SDLEventWatcher> watcher1 = std::make_shared<zbe::ImGuiEventWatcher>();
//   std::shared_ptr<zbe::SDLEventWatcher> watcher2 = std::make_shared<zbe::KeyMouseEventWatcher>();
//   sdlEDispatcher.addWatcher(watcher1);
//   sdlEDispatcher.addWatcher(watcher2);
//
//   std::shared_ptr<zbe::InputBuffer> inputBuffer = sdlEDispatcher.getInputBuffer();
//   std::shared_ptr<zbe::InputTextBuffer> inputTextBuffer = sdlEDispatcher.getInputTextBuffer();
//
//   std::shared_ptr<zbe::Daemon> preLoopSDL = std::make_shared<zbe::BasicPreLoopSDLDaemon>(window);
//   std::shared_ptr<zbe::ImGuiPreLoopDaemon> imguipre =std::make_shared<zbe::ImGuiPreLoopDaemon>(window);
//
//   std::shared_ptr<zbe::Daemon> postLoopSDL = std::make_shared<zbe::BasicPostLoopSDLDaemon>(window);
//   std::shared_ptr<zbe::ImGuiPostLoopDaemon> imguipos =std::make_shared<zbe::ImGuiPostLoopDaemon>(window);
//
//   std::shared_ptr<zbe::SimpleImGuiTest> imguidrawer =std::make_shared<zbe::SimpleImGuiTest>(window);
//
//   bool show_demo_window = true;
//   bool show_another_window = false;
//   //ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
//   float fps[100];
//   for(auto& f : fps) {
//    f = .0f;
//   }
//   char InputBuf[256] = "";
//
//   // Main loop
//   bool done = false;
//   while (!done)
//   {
//     // Poll and handle events (inputs, window resize, etc.)
//     // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
//     // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
//     // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
//     // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
// //    SDL_Event event;
// //    while (SDL_PollEvent(&event)) {
// //      ImGui_ImplSDL2_ProcessEvent(&event);
// //      if (event.type == SDL_QUIT)
// //        done = true;
// //      if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window->getSDL_Window()))
// //        done = true;
// //    }
//
//     //sdlEDispatcher.run();
//     preLoopSDL->run();
//     imguipre->run();
// //    SDL_Event event;
// //    while (SDL_PollEvent(&event)) {
// //      ImGui_ImplSDL2_ProcessEvent(&event);
// //    }
//     imguidrawer->run();
// //    // Start the Dear ImGui frame
// //    ImGui_ImplOpenGL3_NewFrame();
// //    ImGui_ImplSDL2_NewFrame(window->getSDL_Window());
// //    ImGui::NewFrame();
// //
// //    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
// //    if (show_demo_window)
// //      ImGui::ShowDemoWindow(&show_demo_window);
// //
// //    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
// //    {
// //      static float f = 0.0f;
// //      static int counter = 0;
// //
// //      ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
// //
// //      ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
// //      ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
// //      ImGui::Checkbox("Another Window", &show_another_window);
// //
// //      ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
// //      ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
// //
// //      if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
// //        counter++;
// //      ImGui::SameLine();
// //      ImGui::Text("counter = %d", counter);
// //
// //      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
// //      //const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
// //      for(int i = 0; i < 99; i++) {
// //        fps[i] = fps[i+1];
// //      }
// //      fps[99] = ImGui::GetIO().Framerate;
// //      ImGui::PlotLines("FPS", fps, IM_ARRAYSIZE(fps));
// //
// //      ImGui::Separator();
// //
// //      const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing(); // 1 separator, 1 input text
// //      ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar); // Leave room for 1 separator + 1 InputText
// //      ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4,1)); // Tighten spacing
// //
// //      ImGui::TextUnformatted("Hola");
// //      ImGui::TextUnformatted("comando1");
// //      ImGui::TextUnformatted("comando con parametros");
// //      ImGui::TextUnformatted("chai print(\"Hola\")");
// //      ImGui::TextUnformatted("file data\\scripts\\hello.chai");
// //      ImGui::TextUnformatted(InputBuf);
// //      ImGui::TextUnformatted("Adios");
// //
// //      if (ImGui::InputText("Input", InputBuf, IM_ARRAYSIZE(InputBuf))){
// //          ;
// ////        char* s = InputBuf;
// ////        Strtrim(s);
// ////        if (s[0])
// ////            ExecCommand(s);
// ////        strcpy(s, "");
// ////        reclaim_focus = true;
// //      }
// //
// //      ImGui::PopStyleVar();
// //      ImGui::EndChild();
// //      ImGui::End();
// //    }
// //
// //    // 3. Show another simple window.
// //    if (show_another_window) {
// //      ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
// //      ImGui::Text("Hello from another window!");
// //      if (ImGui::Button("Close Me"))
// //          show_another_window = false;
// //      ImGui::End();
// //    }
//
//     postLoopSDL->run();
// //    // Rendering
// //    ImGui::Render();
// //    glViewport(0, 0, window->getDisplayX(), window->getDisplayY());
// //    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
// //    glClear(GL_COLOR_BUFFER_BIT);
// //    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
// //    SDL_GL_SwapWindow(window->getSDL_Window());
//     imguipos->run();
//   }
//
//   // Cleanup
//   ImGui_ImplOpenGL3_Shutdown();
//   ImGui_ImplSDL2_Shutdown();
//   ImGui::DestroyContext();
//
//   SDL_GL_DeleteContext(window->getGLContext());
//   SDL_DestroyWindow(window->getSDL_Window());
//   SDL_Quit();

  return 0;
}

int degryllmain(int, char*[]) {
//   const int WINDOWPOSX = 50;
//   const int WINDOWPOSY = 50;
//   const int WIDHT = 1280;
//   const int HEIGHT = 768;
//   const int FONTSIZE = 14;
//   const int FONTWHITE = 192;
//   const int FONTOPACITY = 255;
//   const uint64_t INPUTEVENT = 1;
//   const uint64_t TEXTEVENT = 2;
//
//   auto chai = std::make_shared<chaiscript::ChaiScript>();
//
//   chai->eval(R"(
//     //puts(helloWorld("Bob"));
//     print("ChaiScript funcionando!");
//   )");
//
// //  std::shared_ptr<zbe::SDLOGLWindow> window = std::make_shared<zbe::SDLOGLWindow>("Console", WINDOWPOSX, WINDOWPOSY, WIDHT, HEIGHT);
// //  std::shared_ptr<zbe::SDLOGLWindow> window = std::make_shared<zbe::SDLOGLWindow>("Console", WINDOWPOSX, WINDOWPOSY, WIDHT, HEIGHT);
//   std::shared_ptr<zbe::SDLOGLImGuiWindow> window = std::make_shared<zbe::SDLOGLImGuiWindow>("Console", WINDOWPOSX, WINDOWPOSY, WIDHT, HEIGHT);
//
//   auto is = window->getImgStore();
//   auto gid = is->loadImg("data/images/degryll/isotetris/sueloG.png");
//   auto fs = window->getFontStore();
//   auto fid = fs->loadFont("data/fonts/Hack-Regular.ttf", FONTSIZE, {FONTWHITE, FONTWHITE, FONTWHITE, FONTOPACITY});
//
// //  IMGUI_CHECKVERSION();
// //  ImGui::CreateContext();
// //  ImGuiIO& io = ImGui::GetIO(); (void)io;
// //  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
// //  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
//
// //  // Setup Dear ImGui style
// //  ImGui::StyleColorsDark();
// //  //ImGui::StyleColorsClassic();
// //  ImGui_ImplSDL2_Init(window->getSDL_Window());
// //  //io.Fonts->AddFontFromFileTTF("data\\fonts\\Hack-Regular.ttf", 16.0f);
//
// //  ImGui_ImplSDL2_NewFrame(window->getSDL_Window());
// //  ImGui::NewFrame();
// //
// //  ImGui::Begin("Hello, world!");
// //  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
// //  ImGui::End();
// //  ImGui::Render();
//
//   std::shared_ptr<zbe::DaemonMaster> pre = std::make_shared<zbe::DaemonMaster>();
//   std::shared_ptr<zbe::DaemonMaster> post = std::make_shared<zbe::DaemonMaster>();
//   std::shared_ptr<zbe::DaemonMaster> event = std::make_shared<zbe::DaemonMaster>();
//   std::shared_ptr<zbe::DaemonMaster> common = std::make_shared<zbe::DaemonMaster>();
//   std::shared_ptr<zbe::DaemonMaster> react = std::make_shared<zbe::DaemonMaster>();
//   std::shared_ptr<zbe::DaemonMaster> draw = std::make_shared<zbe::DaemonMaster>();
//   std::shared_ptr<zbe::MainLoop> loop = std::make_shared<zbe::MainLoop>(pre, post, event, common, react, draw);
//
//   std::shared_ptr<zbe::Daemon> preLoopSDL = std::make_shared<zbe::BasicPreLoopSDLDaemon>(window);
//   pre->addDaemon(preLoopSDL);
//   std::shared_ptr<zbe::ImGuiPreLoopDaemon> imguipre =std::make_shared<zbe::ImGuiPreLoopDaemon>(window);
//   pre->addDaemon(imguipre);
//
// //  std::shared_ptr<zbe::Daemon> postLoopSDL = std::make_shared<zbe::BasicPostLoopSDLDaemon>(window);
// //  post->addDaemon(postLoopSDL);
//
//   std::shared_ptr<zbe::ImGuiPostLoopDaemon> imguipos =std::make_shared<zbe::ImGuiPostLoopDaemon>(window);
//   post->addDaemon(imguipos);
//
//   auto sysTimer = std::make_shared<zbe::SDLTimer>(true);
//   std::shared_ptr<zbe::SysTime> sysTime = zbe::SysTime::getInstance();
//   sysTime->setSystemTimer(sysTimer);
//
//   zbe::SDLEventDispatcher& sdlEDispatcher = zbe::SDLEventDispatcher::getInstance();
//   std::shared_ptr<zbe::SDLEventWatcher> watcher1 = std::make_shared<zbe::ImGuiEventWatcher>();
//   std::shared_ptr<zbe::SDLEventWatcher> watcher2 = std::make_shared<zbe::KeyMouseEventWatcher>();
//   sdlEDispatcher.addWatcher(watcher1);
//   sdlEDispatcher.addWatcher(watcher2);
//
//   std::shared_ptr<zbe::InputBuffer> inputBuffer = sdlEDispatcher.getInputBuffer();
//   std::shared_ptr<zbe::InputTextBuffer> inputTextBuffer = sdlEDispatcher.getInputTextBuffer();
//
//   std::shared_ptr<zbe::Value<uint64_t> > fidv = std::make_shared<zbe::SimpleValue<uint64_t> >(fid);
//   std::shared_ptr<zbe::Value<std::string> > vc = std::make_shared<zbe::SimpleValue<std::string> >();
//   std::shared_ptr<zbe::Value<int64_t> > vl = std::make_shared<zbe::SimpleValue<int64_t> >();
//   std::shared_ptr<zbe::Value<std::vector<std::string> > > vh = std::make_shared<zbe::SimpleValue<std::vector<std::string> > >();
//   std::shared_ptr<zbe::Console> console = std::make_shared<zbe::Console>(fidv, vc, vl, vh);
//   std::shared_ptr<zbe::TextHandler> addText = std::make_shared<zbe::AddText>(vc, vl, vh);
//
//   std::shared_ptr<zbe::Value<uint64_t> > gidv = std::make_shared<zbe::SimpleValue<uint64_t> >(gid);
//   std::shared_ptr<zbe::Value<zbe::Vector2D > > sizev = std::make_shared<zbe::SimpleValue<zbe::Vector2D > >(zbe::Vector2D{16.0, 9.0});
//   std::shared_ptr<zbe::Value<zbe::Vector2D > > acelv = std::make_shared<zbe::SimpleValue<zbe::Vector2D > >(zbe::Vector2D{0.0, 0.0});
//   std::shared_ptr<zbe::Value<zbe::Vector2D > > velv = std::make_shared<zbe::SimpleValue<zbe::Vector2D > >(zbe::Vector2D{100.0, 0.0});
//   std::shared_ptr<zbe::Value<zbe::Vector2D > > posv = std::make_shared<zbe::SimpleValue<zbe::Vector2D > >(zbe::Vector2D{320.0, 300.0});
//   std::shared_ptr<zbe::Entity> prota = std::make_shared<zbe::Entity>();
//   prota->setUint(1, gidv);
//   prota->setVector2D(1, sizev);
//   prota->setVector2D(2, acelv);
//   prota->setVector2D(3, velv);
//   prota->setVector2D(4, posv);
//
//   chai->add(chaiscript::fun(&ChaiWarp::setX), "setX");
//   chai->add(chaiscript::fun(&ChaiWarp::setY), "setY");
//   chai->add(chaiscript::fun(&ChaiWarp::incrementX), "incrementX");
//   chai->add(chaiscript::fun(&ChaiWarp::incrementY), "incrementY");
//   ChaiWarp chaiacel(acelv);
//   chai->add(chaiscript::var(&chaiacel), "acelv");
//   ChaiWarp chaivel(velv);
//   chai->add(chaiscript::var(&chaivel), "velv");
//   ChaiWarp chaipos(posv);
//   chai->add(chaiscript::var(&chaipos), "posv");
//
//   std::shared_ptr<zbe::InputEventGenerator> ieg = std::make_shared<zbe::InputEventGenerator>(inputBuffer, inputTextBuffer, TEXTEVENT, addText);
//   std::shared_ptr<zbe::MappedInputStatusManager> ism = std::make_shared<zbe::MappedInputStatusManager>(INPUTEVENT);
//   ieg->addManager(ism);
//
//   event->addDaemon(ieg);
//
//   auto exitv = std::make_shared<zbe::SimpleValue<int64_t> >();
//   std::shared_ptr<zbe::Daemon> exitd = std::make_shared<zbe::MainLoopExit>(loop, exitv, 42);
//   zbe::DaemonIH exitih(exitd);
//   ism->addHandler(zbe::ZBEK_ESCAPE, &exitih);
//
//   // [TODO] input manager recibe un puntero, deberia ser un shared_ptr
//   zbe::ExecuteCommandIH execute(chai, vc, vl, vh);
//   ism->addHandler(zbe::ZBEK_RETURN, &execute);
//   zbe::RemoveGlyphIH del(vc);
//   ism->addHandler(zbe::ZBEK_BACKSPACE, &del);
//   zbe::ScrollIH scroll(vl, vh);
//   ism->addHandler(zbe::ZBEK_MOUSE_WHEEL_Y, &scroll);
//
//   std::array<uint64_t, 4> l{ {1, 1, 1, 1} };
//   std::shared_ptr<zbe::MAvatar<uint64_t, std::string, int64_t, std::vector<std::string> > > cavatar = std::make_shared<zbe::MBaseAvatar<uint64_t, std::string, int64_t, std::vector<std::string> > >(console, l);
//   auto cdl = std::make_shared<zbe::TicketedForwardList<zbe::MAvatar<uint64_t, std::string, int64_t, std::vector<std::string> > > >();
//   cdl->push_front(cavatar);
//   std::shared_ptr<zbe::Daemon> drawerDaemon = std::make_shared<zbe::BehaviorDaemon<zbe::TicketedForwardList<zbe::MAvatar<uint64_t, std::string, int64_t, std::vector<std::string> > >, uint64_t, std::string, int64_t, std::vector<std::string> > >(std::make_shared<zbe::ConsoleTextDrawer>(window), cdl);
//   draw->addDaemon(drawerDaemon);
//
//   std::array<uint64_t, 3> a1{ {1, 1, 4} };
//   std::shared_ptr<zbe::MAvatar<uint64_t, zbe::Vector2D, zbe::Vector2D > > protadraw = std::make_shared<zbe::MBaseAvatar<uint64_t, zbe::Vector2D, zbe::Vector2D > >(prota, a1);
//   auto pdl = std::make_shared<zbe::TicketedForwardList<zbe::MAvatar<uint64_t, zbe::Vector2D, zbe::Vector2D> > >();
//   pdl->push_front(protadraw);
//   std::shared_ptr<zbe::Daemon> drawerDaemon2 = std::make_shared<zbe::BehaviorDaemon<zbe::TicketedForwardList<zbe::MAvatar<uint64_t, zbe::Vector2D, zbe::Vector2D> >, uint64_t, zbe::Vector2D, zbe::Vector2D> >(std::make_shared<zbe::SingleSpriteSDLDrawer>(window), pdl);
//   draw->addDaemon(drawerDaemon2);
//
//   std::shared_ptr<zbe::SimpleImGuiTest> imguidrawer =std::make_shared<zbe::SimpleImGuiTest>(window);
//   draw->addDaemon(imguidrawer);
//
//   std::array<uint64_t, 3> a2{ {2, 3, 4} };
//   std::shared_ptr<zbe::MAvatar<zbe::Vector2D, zbe::Vector2D, zbe::Vector2D > > protamove = std::make_shared<zbe::MBaseAvatar<zbe::Vector2D, zbe::Vector2D, zbe::Vector2D > >(prota, a2);
//   auto pml = std::make_shared<zbe::TicketedForwardList<zbe::MAvatar<zbe::Vector2D, zbe::Vector2D, zbe::Vector2D> > >();
//   pml->push_front(protamove);
//   auto movebehavior = std::make_shared<zbe::CustomMotion<2> >();
//   movebehavior->setFunction(test);
//   std::shared_ptr<zbe::Daemon> moveDaemon = std::make_shared<zbe::BehaviorDaemon<zbe::TicketedForwardList<zbe::MAvatar<zbe::Vector2D, zbe::Vector2D, zbe::Vector2D> >, zbe::Vector2D, zbe::Vector2D, zbe::Vector2D> >(movebehavior, pml);
//   common->addDaemon(moveDaemon);
//
//   ChaiWarpBhv chaicm(movebehavior);
//   chai->add(chaiscript::fun(&ChaiWarpBhv::setFunction), "setFunction");
//   chai->add(chaiscript::var(&chaicm), "movebehavior");
//   chai->add(chaiscript::fun(&test), "test");
//   chai->add(chaiscript::fun(&test2), "test2");
//
//   loop->run();

  return 0;
}
