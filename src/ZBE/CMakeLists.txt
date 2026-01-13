# include(GenerateExportHeader)
find_package(PNG REQUIRED)
find_package(OpenGL REQUIRED)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)

add_library(ZBE_LIB SHARED
  JSON/JSONFactory.cpp
  JSON/graphics/JSONGraphicsLoaders.cpp
  OAL/daemons/OALContextDaemon.cpp
  OAL/players/Sound3DOALPlayer.cpp
  OAL/resources/OALAudioLoader.cpp
  OAL/system/OALAudioStore.cpp
  OAL/tools/OALUtils.cpp
  OGL/graphics/implementations/OGLModelSheets.cpp
  SDL/OGL/SDLOGLWindow.cpp
  SDL/daemons/SDLWindowDaemon.cpp
  SDL/daemons/SDLOGLWindowDaemon.cpp
  SDL/daemons/IOPreLoopSDL.cpp
  SDL/drawers/SingleSpriteSDLDrawer.cpp
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
  core/system/SysIdGenerator.cpp
  core/system/SysError.cpp
  core/tools/math/Vector.cpp
  core/tools/math/collisions/intersections.cpp
  core/tools/text/utf8.cpp
  core/tools/time/ContextTime.cpp
  daemons/RsrcLoaderDmn.cpp
  daemons/RsrcFolderLoaderDmn.cpp
  glTF/resources/GlTFResourceLoader.cpp
  resources/contextnames.cpp
  resources/loaders/RsrcFolderLoader.cpp
  resources/loaders/implementations/JSONAppLoader.cpp
  tools/graphics/Camera.cpp
)

list(APPEND CMAKE_CXX_CPPCHECK --exclude=../../extlibs/stb/)

add_library(ZBE::ZBE_LIB ALIAS ZBE_LIB)

add_library(glew STATIC IMPORTED) # or STATIC instead of SHARED

target_compile_definitions(ZBE_LIB PRIVATE _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING)
target_compile_definitions(ZBE_LIB PRIVATE SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)

IF (MSVC)
  # target_compile_definitions(ZBE_LIB PRIVATE GLEW_STATIC)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT ProgramDatabase)
  target_compile_definitions(ZBE_LIB PRIVATE ZBE_EXPORTS)
  target_compile_options(ZBE_LIB PRIVATE /bigobj)
  set_target_properties(glew PROPERTIES
    IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/extlibs/glew/2.2.0/windows/x64/glew32.lib"
    INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/extlibs/glew/2.2.0/include"
  )
ELSE()
  set_target_properties(glew PROPERTIES
    IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/extlibs/glew/2.2.0/linux/libGLEW.a"
    INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/extlibs/glew/2.2.0/include"
  )
ENDIF()

target_link_libraries(ZBE_LIB PRIVATE ZLIB::ZLIB)

target_link_libraries(ZBE_LIB
  PUBLIC ZBE_options
  PUBLIC ZBE_warnings
  PUBLIC SDL2
  PUBLIC SDL2_image 
  PUBLIC SDL2_net
  PUBLIC SDL2_ttf
  PUBLIC nlohmann_json::nlohmann_json
  PUBLIC tinygltf
  PUBLIC PNG::PNG
  PUBLIC glew
  PUBLIC OpenGL::GL
  PUBLIC glm
  PUBLIC OpenAL
  PUBLIC ogg
  PUBLIC vorbis
  PUBLIC vorbisfile
  PUBLIC spdlog::spdlog
)

message(STATUS "PNG includes: ${PNG_INCLUDE_DIRS}")
message(STATUS "PNG libraries: ${PNG_LIBRARIES}")

# TODO revisar cual es la carpeta correcta en la que deshabilitar los warnings
target_include_directories(ZBE_LIB PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
target_include_directories(ZBE_LIB PUBLIC $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)
                                                
target_include_directories(ZBE_LIB SYSTEM PRIVATE ${imgui_SOURCE_DIR})
target_include_directories(ZBE_LIB SYSTEM PRIVATE ${glm_SOURCE_DIR})
target_include_directories(ZBE_LIB SYSTEM PRIVATE ${SDL2_net_SOURCE_DIR})
target_include_directories(ZBE_LIB SYSTEM PRIVATE ${tinygltf_SOURCE_DIR})
target_include_directories(ZBE_LIB SYSTEM PRIVATE ${vorbis_SOURCE_DIR}/include)
target_include_directories(ZBE_LIB SYSTEM PRIVATE ${ogg_SOURCE_DIR})
target_include_directories(ZBE_LIB SYSTEM PRIVATE ${libpng_SOURCE_DIR})
# target_include_directories(ZBE_LIB SYSTEM PRIVATE ${nlohmann_SOURCE_DIR}/include)
# target_include_directories(ZBE_LIB SYSTEM PRIVATE /media/ludo/D4D679EDD679D06A/workspace/ZBE/build/_deps/json-src/include)

get_target_property(defs_publicas ZBE_LIB INTERFACE_COMPILE_DEFINITIONS)
get_target_property(defs_privadas ZBE_LIB COMPILE_DEFINITIONS)

message(STATUS "Definiciones ZBE_LIB PUBLICAS: ${defs_publicas}")
message(STATUS "Definiciones ZBE_LIB PRIVADAS: ${defs_privadas}")