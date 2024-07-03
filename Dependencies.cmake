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
    GIT_TAG 982feb7a65aef15e4cff157120808f439a9abdc4)
  
  cpmaddpackage(
    NAME SDL3_image
    GITHUB_REPOSITORY libsdl-org/SDL_image
    GIT_TAG 60013b1f94676e38d15c57de3e5cd36483c78187)
  
  cpmaddpackage(
    NAME SDL3_mixer
    GITHUB_REPOSITORY libsdl-org/SDL_mixer
    GIT_TAG 9fdb00fa64df5f084a78fae56a9f13b40d4ef85c)
  
  cpmaddpackage(
    NAME SDL3_net
    GITHUB_REPOSITORY libsdl-org/SDL_net
    GIT_TAG 8dffdd6ca620c6a991fa4dbec5495f6e0a955b2a)

  cpmaddpackage(
    NAME SDL3_ttf
    GITHUB_REPOSITORY libsdl-org/SDL_ttf
    GIT_TAG ad1ecab775ac285ba7546b6ee90252549a25452c)
    

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
