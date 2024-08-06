include(cmake/CPM.cmake)
include(ExternalProject)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(myproject_setup_dependencies)

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

  # if(NOT TARGET CLI11::CLI11)
  #   cpmaddpackage("gh:CLIUtils/CLI11@2.3.2")
  # endif()

  # if(NOT TARGET ftxui::screen)
  #   cpmaddpackage("gh:ArthurSonzogni/FTXUI@5.0.0")
  # endif()

  # if(NOT TARGET tools::tools)
  #   cpmaddpackage("gh:lefticus/tools#update_build_system")
  # endif()

  cpmaddpackage("gh:nlohmann/json@3.11.3")

  cpmaddpackage("gh:g-truc/glm#1.0.1")

  cpmaddpackage("gh:ocornut/imgui@1.90.7")

  cpmaddpackage("gh:kcat/openal-soft#1.23.1")

  cpmaddpackage("gh:syoyo/tinygltf@2.8.22")

  cpmaddpackage("gh:nemtrif/utfcpp@4.0.5")
  
  # ------- LODEPNG START -------
  # cpmaddpackage(
  #   NAME lodePNG
  #   GITHUB_REPOSITORY lvandeve/lodepng
  #   GIT_TAG ed3c5f14b136c936d615ee3b38aaa7e7e642f12c)

# Descargar y configurar lodepng
ExternalProject_Add(
  lodepng
  GIT_REPOSITORY https://github.com/lvandeve/lodepng.git
  GIT_TAG master
  PREFIX ${CMAKE_BINARY_DIR}/_deps/lodepng-src
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  # CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lodepng-install
  # BUILD_BYPRODUCTS ${CMAKE_BINARY_DIR}/lodepng-install/lib/liblodepng.a
)

# message("CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR})

# # Añadir lodepng como una biblioteca IMPORTED
# # add_library(lodepng STATIC IMPORTED)
# # add_dependencies(lodepng lodepng_project)

# set_target_properties(lodepng PROPERTIES
#   IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/lodepng-install/lib/liblodepng.a
#   INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_BINARY_DIR}/lodepng-install/include
# )
#   # include(GNUInstallDirs)
  
#   # install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

  # -----------------------------
  cpmaddpackage("gh:libsdl-org/SDL#release-2.30.6")
  
  cpmaddpackage("gh:libsdl-org/SDL_image#release-2.8.2")
  
  # cpmaddpackage("gh:xiph/opusfile@0.12")

  # cpmaddpackage("gh:libsdl-org/SDL_mixer#release-2.8.0")

  cpmaddpackage("gh:libsdl-org/SDL_net#release-2.2.0")

  cpmaddpackage("gh:libsdl-org/SDL_ttf#release-2.22.0")    

# ChaiScript-6.1.0 
# X - > GLEW 
# V - > glm 
# googletest 
# V - > imgui-1.76 
# V - > json 
# V - > lodePNG 
# V - > OALSoft 
# V - > SDL2
# V - > SDL2_image 
# V - > SDL2_mixer 
# V - > SDL2_net 
# V - > SDL2_ttf
# E - > stb_image
# E - > stb_vorbis
# tinygltf
# X - > tinyobjloader
# V - > utf8cpp
# X - > Vulkan
# X - > Vulkan/1.1.77.0

endfunction()
