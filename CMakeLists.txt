cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 20)

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w")

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
# when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS OFF)

project(
  ZBE
  VERSION 0.4.0
  DESCRIPTION "A nice & cool game engine"
  HOMEPAGE_URL "https://github.com/Degryll/ZBE"
  LANGUAGES CXX C)

# Forzar el uso del runtime DLL en MSVC para evitar conflictos de runtime
if(MSVC)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
  add_compile_definitions(_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING)
endif()

include(cmake/PreventInSourceBuilds.cmake)

include(ProjectOptions.cmake)
ZBE_setup_options()
ZBE_global_options()

# Disable tests for all dependencies
set(BUILD_TESTING OFF CACHE BOOL "Build testing" FORCE)

include(Dependencies.cmake)
ZBE_setup_dependencies()

# Re-enable tests for ZBE only
set(BUILD_TESTING ON CACHE BOOL "Build testing" FORCE)

# Enable CTest so that add_test() calls are registered globally
enable_testing()

ZBE_local_options()

# don't know if this should be set globally from here or not...
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

set(GIT_SHA
    "Unknown"
    CACHE STRING "SHA this build was generated from")
string(
  SUBSTRING "${GIT_SHA}"
            0
            8
            GIT_SHORT_SHA)

target_compile_features(ZBE_options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

add_library(ZBE::ZBE_options ALIAS ZBE_options)
add_library(ZBE::ZBE_warnings ALIAS ZBE_warnings)

#add_library(ZBE::ZBE_options INTERFACE IMPORTED)
#add_library(ZBE::ZBE_warnings INTERFACE IMPORTED)

add_subdirectory(src)

if(ZBE_BUILD_FUZZ_TESTS) # TODO hacer test borrosos.
  message(AUTHOR_WARNING "Building Fuzz Tests, using fuzzing sanitizer https://www.llvm.org/docs/LibFuzzer.html")
  if (NOT ZBE_ENABLE_ADDRESS_SANITIZER AND NOT ZBE_ENABLE_THREAD_SANITIZER)
    message(WARNING "You need asan or tsan enabled for meaningful fuzz testing")
  endif()
  add_subdirectory(fuzz_test)

endif()

# If MSVC is being used, and ASAN is enabled, we need to set the debugger environment
# so that it behaves well with MSVC's debugger, and we can run the target from visual studio
if(MSVC)
  get_all_installable_targets(all_targets)
  message("all_targets=${all_targets}")
  set_target_properties(${all_targets} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=$(VC_ExecutablePath_x64);%PATH%")
endif()

# set the startup project for the "play" button in MSVC
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT intro)

if(CMAKE_SKIP_INSTALL_RULES)
  return()
endif()

include(cmake/PackageProject.cmake)


# TODO averiguar si esto nos puede ayudar con la instalación y el packaging
# # Add other targets that you want installed here, by default we just package the one executable
# # we know we want to ship
# ZBE_package_project(
#   TARGETS
#   intro
#   ZBE_options
#   ZBE_warnings
#   # FIXME: this does not work! CK
#   # PRIVATE_DEPENDENCIES_CONFIGURED project_options project_warnings
# )

# Experience shows that explicit package naming can help make it easier to sort
# out potential ABI related issues before they start, while helping you
# track a build to a specific GIT SHA
set(CPACK_PACKAGE_FILE_NAME
    "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-${GIT_SHORT_SHA}-${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}"
)

include(CPack)