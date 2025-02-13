include(cmake/SystemLink.cmake)
include(cmake/LibFuzzer.cmake)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)


macro(ZBE_supports_sanitizers)
  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)
    set(SUPPORTS_UBSAN ON)
  else()
    set(SUPPORTS_UBSAN OFF)
  endif()

  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
    set(SUPPORTS_ASAN OFF)
  else()
    set(SUPPORTS_ASAN ON)
  endif()
endmacro()

macro(ZBE_setup_options)
  option(ZBE_ENABLE_HARDENING "Enable hardening" ON)
  option(ZBE_ENABLE_COVERAGE "Enable coverage reporting" OFF)
  cmake_dependent_option(
    ZBE_ENABLE_GLOBAL_HARDENING
    "Attempt to push hardening options to built dependencies"
    ON
    ZBE_ENABLE_HARDENING
    OFF)

  ZBE_supports_sanitizers()

  if(NOT PROJECT_IS_TOP_LEVEL OR ZBE_PACKAGING_MAINTAINER_MODE)
    option(ZBE_ENABLE_IPO "Enable IPO/LTO" OFF)
    option(ZBE_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
    option(ZBE_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(ZBE_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
    option(ZBE_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(ZBE_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
    option(ZBE_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(ZBE_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(ZBE_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(ZBE_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
    option(ZBE_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
    option(ZBE_ENABLE_PCH "Enable precompiled headers" OFF)
    option(ZBE_ENABLE_CACHE "Enable ccache" OFF)
  else()
    option(ZBE_ENABLE_IPO "Enable IPO/LTO" ON)
    option(ZBE_WARNINGS_AS_ERRORS "Treat Warnings As Errors" ON)
    option(ZBE_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(ZBE_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${SUPPORTS_ASAN})
    option(ZBE_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(ZBE_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${SUPPORTS_UBSAN})
    option(ZBE_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(ZBE_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(ZBE_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(ZBE_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
    option(ZBE_ENABLE_CPPCHECK "Enable cpp-check analysis" ON)
    option(ZBE_ENABLE_PCH "Enable precompiled headers" OFF)
    option(ZBE_ENABLE_CACHE "Enable ccache" ON)
  endif()

  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      ZBE_ENABLE_IPO
      ZBE_WARNINGS_AS_ERRORS
      ZBE_ENABLE_USER_LINKER
      ZBE_ENABLE_SANITIZER_ADDRESS
      ZBE_ENABLE_SANITIZER_LEAK
      ZBE_ENABLE_SANITIZER_UNDEFINED
      ZBE_ENABLE_SANITIZER_THREAD
      ZBE_ENABLE_SANITIZER_MEMORY
      ZBE_ENABLE_UNITY_BUILD
      ZBE_ENABLE_CLANG_TIDY
      ZBE_ENABLE_CPPCHECK
      ZBE_ENABLE_COVERAGE
      ZBE_ENABLE_PCH
      ZBE_ENABLE_CACHE)
  endif()

  ZBE_check_libfuzzer_support(LIBFUZZER_SUPPORTED)
  if(LIBFUZZER_SUPPORTED AND (ZBE_ENABLE_SANITIZER_ADDRESS OR ZBE_ENABLE_SANITIZER_THREAD OR ZBE_ENABLE_SANITIZER_UNDEFINED))
    set(DEFAULT_FUZZER ON)
  else()
    set(DEFAULT_FUZZER OFF)
  endif()

  option(ZBE_BUILD_FUZZ_TESTS "Enable fuzz testing executable" ${DEFAULT_FUZZER})

endmacro()

macro(ZBE_global_options)
  if(ZBE_ENABLE_IPO)
    include(cmake/InterproceduralOptimization.cmake)
    ZBE_enable_ipo()
  endif()

  ZBE_supports_sanitizers()

  if(ZBE_ENABLE_HARDENING AND ZBE_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR ZBE_ENABLE_SANITIZER_UNDEFINED
       OR ZBE_ENABLE_SANITIZER_ADDRESS
       OR ZBE_ENABLE_SANITIZER_THREAD
       OR ZBE_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    message("${ZBE_ENABLE_HARDENING} ${ENABLE_UBSAN_MINIMAL_RUNTIME} ${ZBE_ENABLE_SANITIZER_UNDEFINED}")
    ZBE_enable_hardening(ZBE_options ON ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()
endmacro()

macro(ZBE_local_options)
  if(PROJECT_IS_TOP_LEVEL)
    include(cmake/StandardProjectSettings.cmake)
  endif()

  add_library(ZBE_warnings INTERFACE)
  add_library(ZBE_options INTERFACE)

  include(cmake/CompilerWarnings.cmake)
  ZBE_set_project_warnings(
    ZBE_warnings
    ${ZBE_WARNINGS_AS_ERRORS}
    ""
    ""
    ""
    "")

  if(ZBE_ENABLE_USER_LINKER)
    include(cmake/Linker.cmake)
    ZBE_configure_linker(ZBE_options)
  endif()

  include(cmake/Sanitizers.cmake)
  ZBE_enable_sanitizers(
    ZBE_options
    ${ZBE_ENABLE_SANITIZER_ADDRESS}
    ${ZBE_ENABLE_SANITIZER_LEAK}
    ${ZBE_ENABLE_SANITIZER_UNDEFINED}
    ${ZBE_ENABLE_SANITIZER_THREAD}
    ${ZBE_ENABLE_SANITIZER_MEMORY})

  set_target_properties(ZBE_options PROPERTIES UNITY_BUILD ${ZBE_ENABLE_UNITY_BUILD})

  if(ZBE_ENABLE_PCH)
    target_precompile_headers(
      ZBE_options
      INTERFACE
      <vector>
      <string>
      <utility>)
  endif()

  if(ZBE_ENABLE_CACHE)
    include(cmake/Cache.cmake)
    ZBE_enable_cache()
  endif()

  include(cmake/StaticAnalyzers.cmake)
  if(ZBE_ENABLE_CLANG_TIDY)
    ZBE_enable_clang_tidy(ZBE_options ${ZBE_WARNINGS_AS_ERRORS})
  endif()

  if(ZBE_ENABLE_CPPCHECK)
    ZBE_enable_cppcheck(${ZBE_WARNINGS_AS_ERRORS} "" # override cppcheck options
    )
  endif()

  if(ZBE_ENABLE_COVERAGE)
    include(cmake/Tests.cmake)
    ZBE_enable_coverage(ZBE_options)
  endif()

  if(ZBE_WARNINGS_AS_ERRORS)
    check_cxx_compiler_flag("-Wl,--fatal-warnings" LINKER_FATAL_WARNINGS)
    if(LINKER_FATAL_WARNINGS)
      # This is not working consistently, so disabling for now
      # target_link_options(ZBE_options INTERFACE -Wl,--fatal-warnings)
    endif()
  endif()

  if(ZBE_ENABLE_HARDENING AND NOT ZBE_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR ZBE_ENABLE_SANITIZER_UNDEFINED
       OR ZBE_ENABLE_SANITIZER_ADDRESS
       OR ZBE_ENABLE_SANITIZER_THREAD
       OR ZBE_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    ZBE_enable_hardening(ZBE_options OFF ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()

endmacro()
