include(cmake/CPM.cmake)
include(FetchContent)

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

  cpmaddpackage("gh:pnggroup/libpng@1.6.43")

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
