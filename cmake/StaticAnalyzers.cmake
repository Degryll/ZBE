macro(ZBE_enable_cppcheck)
  find_program(CPPCHECK cppcheck)
  if(CPPCHECK)
    # Optional: user can provide CPPCHECK_LIBRARY_DIR to point to a folder
    # that contains cppcheck library configuration files (cfg/std.cfg).
    # Example: -DCPPCHECK_LIBRARY_DIR="C:/tools/cppcheck/cfg"
    if(DEFINED CPPCHECK_LIBRARY_DIR)
      set(CPPCHECK_LIBRARY_ARG --library=${CPPCHECK_LIBRARY_DIR}/std.cfg)
    else()
      # Try to auto-detect a nearby cfg/std.cfg relative to the cppcheck executable
      set(CPPCHECK_LIBRARY_ARG )
      get_filename_component(CPPCHECK_DIR "${CPPCHECK}" DIRECTORY)

      set(_candidate_dirs
          "${CPPCHECK_DIR}/cfg"
          "${CPPCHECK_DIR}/../cfg"
          "${CPPCHECK_DIR}/../../cfg"
          "/usr/share/cppcheck/cfg"
          "/usr/local/share/cppcheck/cfg"
          "/opt/local/share/cppcheck/cfg"
          "$ENV{ProgramFiles}/cppcheck/cfg"
          "C:/Program Files (x86)/cppcheck/cfg"
          "C:/Program Files/cppcheck/cfg"
      )

      foreach(_d IN LISTS _candidate_dirs)
        if(_d STREQUAL "")
          continue()
        endif()
        if(EXISTS "${_d}/std.cfg")
          set(CPPCHECK_LIBRARY_ARG --library=${_d}/std.cfg)
          message(STATUS "cppcheck: found std.cfg at ${_d}/std.cfg")
          break()
        endif()
      endforeach()

      if("${CPPCHECK_LIBRARY_ARG}" STREQUAL "")
        message(WARNING "cppcheck found at ${CPPCHECK} but std.cfg not detected automatically; set -DCPPCHECK_LIBRARY_DIR to the cfg folder to silence this warning")
      endif()
    endif()
    set(SUPPRESS_DIR "*:${CMAKE_CURRENT_BINARY_DIR}/_deps/*.h")
    set(CMAKE_CXX_CPPCHECK ${CPPCHECK}
          # --template=${CPPCHECK_TEMPLATE}
          ${CPPCHECK_LIBRARY_ARG}
          --enable=style,performance,warning,portability
          --inline-suppr
          # We cannot act on a bug/missing feature of cppcheck
          --suppress=cppcheckError
          --suppress=internalAstError
          # if a file does not have an internalAstError, we get an unmatchedSuppression error
          --suppress=unmatchedSuppression
          # noisy and incorrect sometimes
          --suppress=passedByValue
          # ignores code that cppcheck thinks is invalid C++
          --suppress=syntaxError
          --suppress=preprocessorErrorDirective
          --inconclusive
          --suppress=${SUPPRESS_DIR})
  else()
    message(WARNING "cppcheck requested but executable not found")
  endif()
endmacro()

macro(ZBE_enable_clang_tidy target WARNINGS_AS_ERRORS)

  find_program(CLANGTIDY clang-tidy)
  if(CLANGTIDY)
    if(NOT
       CMAKE_CXX_COMPILER_ID
       MATCHES
       ".*Clang")

      get_target_property(TARGET_PCH ${target} INTERFACE_PRECOMPILE_HEADERS)

      if("${TARGET_PCH}" STREQUAL "TARGET_PCH-NOTFOUND")
        get_target_property(TARGET_PCH ${target} PRECOMPILE_HEADERS)
      endif()

      if(NOT ("${TARGET_PCH}" STREQUAL "TARGET_PCH-NOTFOUND"))
        message(
          SEND_ERROR
            "clang-tidy cannot be enabled with non-clang compiler and PCH, clang-tidy fails to handle gcc's PCH file")
      endif()
    endif()

    # construct the clang-tidy command line
    set(CLANG_TIDY_OPTIONS
        ${CLANGTIDY}
        -extra-arg=-Wno-unknown-warning-option
        -extra-arg=-Wno-ignored-optimization-argument
        -extra-arg=-Wno-unused-command-line-argument
        -p)
    # set standard
    if(NOT
       "${CMAKE_CXX_STANDARD}"
       STREQUAL
       "")
      if("${CLANG_TIDY_OPTIONS_DRIVER_MODE}" STREQUAL "cl")
        set(CLANG_TIDY_OPTIONS ${CLANG_TIDY_OPTIONS} -extra-arg=/std:c++${CMAKE_CXX_STANDARD})
      else()
        set(CLANG_TIDY_OPTIONS ${CLANG_TIDY_OPTIONS} -extra-arg=-std=c++${CMAKE_CXX_STANDARD})
      endif()
    endif()

    # set warnings as errors
    if(${WARNINGS_AS_ERRORS})
      list(APPEND CLANG_TIDY_OPTIONS -warnings-as-errors=*)
    endif()

    message("Also setting clang-tidy globally")
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_OPTIONS})
  else()
    message(${WARNING_MESSAGE} "clang-tidy requested but executable not found")
  endif()
endmacro()

macro(ZBE_enable_include_what_you_use)
  find_program(INCLUDE_WHAT_YOU_USE include-what-you-use)
  if(INCLUDE_WHAT_YOU_USE)
    set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${INCLUDE_WHAT_YOU_USE})
  else()
    message(${WARNING_MESSAGE} "include-what-you-use requested but executable not found")
  endif()
endmacro()
