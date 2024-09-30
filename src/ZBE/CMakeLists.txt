include(GenerateExportHeader)


add_library(ZBE_LIB 
  JSON/JSONFactory.cpp
  JSON/graphics/JSONGraphicsLoaders.cpp
  JSON/resources/JSONOGLModelSheetLoaders.cpp
  JSON/resources/JSONMultiSpriteSheetLoader.cpp
  JSON/resources/JSONGLSLProgramLoaderFtry.cpp
  JSON/resources/JSONGLSLProgramLoader.cpp
  JSON/resources/JSONAudioDefLoader.cpp
  OAL/daemons/OALContextDaemon.cpp
  OAL/players/Sound3DOALPlayer.cpp
  OAL/resources/OALAudioLoader.cpp
  OAL/system/OALAudioStore.cpp
  OAL/tools/OALUtils.cpp
  OGL/daemons/ShadersSetter.cpp
  OGL/graphics/implementations/OGLModelSheets.cpp
  SDL/OGL/SDLOGLWindow.cpp
  SDL/OGL/daemons/OGLPreDrawer.cpp
  SDL/OGL/factories/daemons/OGLPreDrawFtry.cpp
  SDL/OGL/factories/daemons/OGLPostDrawFtry.cpp
  SDL/daemons/SDLWindowDaemon.cpp
  SDL/daemons/SDLOGLWindowDaemon.cpp
  SDL/daemons/IOPreLoopSDL.cpp
  SDL/drawers/SingleSpriteSDLDrawer.cpp
  SDL/factories/SDLWindowDmnFtry.cpp
  SDL/factories/SDLOGLWindowDmnFtry.cpp
  SDL/factories/daemons/BasicPreLoopSDLDaemonFtry.cpp
  SDL/factories/daemons/BasicPostLoopSDLDaemonFtry.cpp
  SDL/factories/drawers/SingleTextSDLDrawerFtry.cpp
  SDL/factories/resources/SDLImgLoaderFtry.cpp
  SDL/factories/system/SDLWindowFtry.cpp
  SDL/factories/system/SDLSysTimeFtry.cpp
  SDL/factories/system/SDLOGLWindowFtry.cpp
  SDL/starters/SDL_Starter.cpp
  SDL/system/SDLWindow.cpp
  SDL/system/SDLSocket.cpp
  SDL/system/SDLNetDispatcher.cpp
  SDL/tools/SDLTimer.cpp
  behaviors/SineOscillator.cpp
  behaviors/BulletCreatorBhv.cpp
  core/zbe.cpp
  core/daemons/StateMachineDaemon.cpp
  core/daemons/MainLoop.cpp
  core/daemons/DaemonMaster.cpp
  core/entities/Entity.cpp
  core/events/TextEvent.cpp
  core/events/InputEvent.cpp
  core/events/EventStore.cpp
  core/events/generators/TimeEventGenerator.cpp
  core/events/generators/NetEventGenerator.cpp
  core/events/generators/InputEventGenerator.cpp
  core/io/FileHandler.cpp
  core/system/SysIdGenerator.cpp
  core/system/SysError.cpp
  core/system/Logger.cpp
  core/tools/math/Vector.cpp
  core/tools/math/collisions/intersections.cpp
  core/tools/shared/implementations/SimpleValue.cpp
  core/tools/text/utf8.cpp
  core/tools/time/ContextTime.cpp
  daemons/RsrcLoaderDmn.cpp
  daemons/RsrcFolderLoaderDmn.cpp
  entities/builders/builders.cpp
  events/handlers/input/TicketTogglerIH.cpp
  events/handlers/input/ParametricActivatorIH.cpp
  events/handlers/input/KeyDownTicketEnablerIH.cpp
  events/handlers/input/ActivatorIH.cpp
  factories/implementations/RsrcFtry.cpp
  factories/implementations/behaviors/StateSetterBhvFtry.cpp
  factories/implementations/behaviors/StateLTEraserBhvFtry.cpp
  factories/implementations/daemons/StateMachineDmnFtry.cpp
  factories/implementations/daemons/RsrcLoaderDmnFtry.cpp
  factories/implementations/daemons/RsrcFolderLoaderDmnFtry.cpp
  factories/implementations/daemons/MasterDmnFtry.cpp
  factories/implementations/daemons/MainLoopFtry.cpp
  factories/implementations/daemons/MainLoopExitFtry.cpp
  factories/implementations/entities/EntityFtry.cpp
  factories/implementations/events/generators/TimeEventGnFtry.cpp
  factories/implementations/events/handlers/input/InputToValueFtry.cpp
  factories/implementations/events/handlers/input/DaemonIHFtry.cpp
  factories/implementations/events/handlers/input/DaemonClickIHFtry.cpp
  factories/implementations/events/handlers/input/BroadcastIHFtry.cpp
  factories/implementations/events/handlers/time/TicketEraserFtry.cpp
  factories/implementations/events/handlers/time/DaemonTimeHandlerFtry.cpp
  glTF/resources/GlTFResourceLoader.cpp
  resources/contextname.cpp
  resources/loaders/RsrcFolderLoader.cpp
  resources/loaders/implementations/JSONAppLoader.cpp
  sytem/SystemResources.cpp
  tools/graphics/CameraFtry.cpp
  tools/graphics/Camera.cpp
)

add_library(myproject::ZBE_LIB ALIAS ZBE_LIB)

add_library(glew STATIC IMPORTED) # or STATIC instead of SHARED
IF (WIN32)
  set_target_properties(glew PROPERTIES
    IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/extlibs/glew/2.2.0/windows/x64/glew32s.lib"
    INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/extlibs/glew/2.2.0/include"
  )
ELSE()
  set_target_properties(glew PROPERTIES
    IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/extlibs/glew/2.2.0/linux/libGLEW.a"
    INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/extlibs/glew/2.2.0/include"
  )
ENDIF()

target_link_libraries(ZBE_LIB PRIVATE 
  myproject_options myproject_warnings
  SDL2
  SDL2_image 
  SDL2_net
  SDL2_ttf
  nlohmann_json::nlohmann_json
  glm
  tinygltf
  glew
)

set(WARNING_GUARD SYSTEM)

target_include_directories(ZBE_LIB ${WARNING_GUARD} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                                           $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)
target_include_directories(ZBE_LIB PRIVATE ${PROJECT_SOURCE_DIR}/extlibs/stb)

target_include_directories(ZBE_LIB SYSTEM PUBLIC ${imgui_SOURCE_DIR})

target_compile_features(ZBE_LIB PUBLIC cxx_std_20)

set_target_properties(
  ZBE_LIB
  PROPERTIES VERSION ${PROJECT_VERSION}
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES)

generate_export_header(ZBE_LIB EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/ZBE/zbe.h)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(ZBE_LIB PUBLIC SAMPLE_LIBRARY_STATIC_DEFINE)
endif()
