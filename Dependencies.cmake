include(cmake/CPM.cmake)

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
  
  cpmaddpackage(
    NAME lodePNG
    GITHUB_REPOSITORY lvandeve/lodepng
    GIT_TAG ed3c5f14b136c936d615ee3b38aaa7e7e642f12c)
  
  cpmaddpackage(
    NAME SDL3
    GITHUB_REPOSITORY libsdl-org/SDL
    GIT_TAG 27728db41d12b1fdf91c296905a24d087424fc47)
  
  cpmaddpackage(
    NAME SDL3_image
    GITHUB_REPOSITORY libsdl-org/SDL_image
    GIT_TAG 8eff782fa33d795c9ea1ac42dbe7e17cc9874c78)
  
  cpmaddpackage(
    NAME SDL3_mixer
    GITHUB_REPOSITORY libsdl-org/SDL_mixer
    GIT_TAG 9c5ccc06a8701eb593628e4772fa8c32909e301f)
  
  cpmaddpackage(
    NAME SDL3_net
    GITHUB_REPOSITORY libsdl-org/SDL_net
    GIT_TAG 635c365de6c331730901bf88ee1b66f716fd1dfc)

  cpmaddpackage(
    NAME SDL3_ttf
    GITHUB_REPOSITORY libsdl-org/SDL_ttf
    GIT_TAG df316fa22ea8ac84c53c8e78030b46ac81925df3)
    

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
