include(cmake/CPM.cmake)
include(FetchContent)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(ZBE_setup_dependencies)

  find_package(ZLIB REQUIRED)
  # For each dependency, see if it's
  # already been provided to us by a parent project

  if(NOT TARGET fmtlib::fmtlib)
    cpmaddpackage("gh:fmtlib/fmt#9.1.0")
  endif()

  if(NOT TARGET spdlog::spdlog)
    cpmaddpackage(
      NAME
      spdlog
      VERSION
      1.11.0
      GITHUB_REPOSITORY
      "gabime/spdlog"
      OPTIONS
      "SPDLOG_FMT_EXTERNAL ON")
  endif()

  if(NOT TARGET Catch2::Catch2WithMain)
    cpmaddpackage("gh:catchorg/Catch2@3.3.2")
  endif()

  cpmaddpackage("gh:nlohmann/json@3.11.3")

  cpmaddpackage("gh:g-truc/glm#1.0.1")

  cpmaddpackage("gh:ocornut/imgui@1.90.7")

  if (imgui_ADDED)
    # imgui has no CMake support, so we create our own target

    file(GLOB imgui_sources "${imgui_SOURCE_DIR}/*.cpp")
    file(GLOB imgui_sources_cpp "${imgui_SOURCE_DIR}/misc/cpp/*.cpp")

    list(REMOVE_ITEM imgui_sources "${imgui_SOURCE_DIR}/imgui_demo.cpp")

    set(IMGUI_DIR ${imgui_SOURCE_DIR})
    set(IMGUI_INCLUDE_DIR ${imgui_SOURCE_DIR})
    set(IMGUI_SOURCES ${imgui_sources} ${imgui_sources_cpp})
  endif()
#--------------
cpmaddpackage("gh:kcat/openal-soft#1.23.1")

cpmaddpackage("gh:syoyo/tinygltf@2.8.22")
if(tinygltf_ADDED)
  set_target_properties(tinygltf PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

cpmaddpackage("gh:nemtrif/utfcpp@4.0.5")

cpmaddpackage("gh:pnggroup/libpng@1.6.43")

CPMAddPackage(
  NAME SDL2
  GITHUB_REPOSITORY libsdl-org/SDL
  GIT_TAG release-2.30.10
  OPTIONS
  "SDL_STATIC OFF"
  "SDL_SHARED ON"
  "SDL_TEST OFF"
  "SDL2_DISABLE_SDL2MAIN ON"
  "SDL2_DISABLE_INSTALL ON"
  "SDL2_DISABLE_UNINSTALL ON"
)

CPMAddPackage(
  NAME SDL2_image
  GITHUB_REPOSITORY libsdl-org/SDL_image
  GIT_TAG release-2.8.2
  OPTIONS
  "SDL2IMAGE_INSTALL OFF"
  "SDL2IMAGE_SAMPLES OFF"
  "BUILD_SHARED_LIBS ON"
)

CPMAddPackage(
  NAME SDL2_net
  GITHUB_REPOSITORY libsdl-org/SDL_net
  GIT_TAG release-2.2.0
  OPTIONS
  "SDL2TTF_INSTALL OFF"
  "SDL2TTF_SAMPLES OFF"
  "BUILD_SHARED_LIBS ON"
)

CPMAddPackage(
  NAME SDL2_ttf
  GITHUB_REPOSITORY libsdl-org/SDL_ttf
  GIT_TAG release-2.22.0
  OPTIONS
  "SDL2NET_INSTALL OFF"
  "SDL2NET_SAMPLES OFF"
  "BUILD_SHARED_LIBS ON"
)

# OGG

# Descargar Ogg primero
CPMAddPackage(
    NAME ogg
    GITHUB_REPOSITORY xiph/ogg
    GIT_TAG v1.3.5
)
set(OGG_INCLUDE_DIR ${libogg_SOURCE_DIR}/include)
set(OGG_INCLUDE_DIRS ${OGG_INCLUDE_DIR} ${libogg_BINARY_DIR}/include)
set(OGG_LIBRARY $<TARGET_FILE:ogg>)

# Descargar Vorbis después (que depende de Ogg)
CPMAddPackage(
    NAME vorbis
    GITHUB_REPOSITORY xiph/vorbis
    GIT_TAG v1.3.7
)

endfunction()
