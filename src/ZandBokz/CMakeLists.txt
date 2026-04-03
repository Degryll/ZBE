find_package(OpenGL REQUIRED)

add_executable(ZANDBOKZ 
    src/zandbokz.cpp
)

# TODO Eliminar dependencias de glew e imgui, y usar las que se encuentran en ZBE_LIB

add_library(glew STATIC IMPORTED) # or STATIC instead of SHARED0

IF (MSVC)
  # target_compile_definitions(ZBE_LIB PRIVATE GLEW_STATIC)
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



target_compile_definitions(ZANDBOKZ PRIVATE
    $<$<CONFIG:Debug>:SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE>
    $<$<CONFIG:Release>:SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_WARN>)
if(MSVC)
    target_compile_definitions(ZANDBOKZ PRIVATE _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT ProgramDatabase)
    target_compile_options(ZANDBOKZ PRIVATE /bigobj)
    set_target_properties(ZANDBOKZ PROPERTIES
        WIN32_EXECUTABLE OFF
        ENABLE_EXPORTS OFF
        IMPORT_LIBRARY ""
    )
    target_link_options(ZANDBOKZ PRIVATE
        /SUBSYSTEM:CONSOLE
        /NOIMPLIB
    )
endif()
# TODO Revisar si es necesario añadir zbe_warnings y zbe_options aquí también
target_link_libraries(ZANDBOKZ
    PRIVATE ZBE_LIB
    PRIVATE imgui
    PRIVATE imgui_backend
    PRIVATE SDL2::SDL2 
    PRIVATE glew
    PRIVATE OpenGL::GL
)

target_include_directories(ZANDBOKZ PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/ZandBokz/include>
)

target_include_directories(ZANDBOKZ SYSTEM PRIVATE
    ${glm_SOURCE_DIR}
    ${SDL2_SOURCE_DIR}
    ${tinygltf_SOURCE_DIR}
    ${vorbis_SOURCE_DIR}/include
    ${ogg_SOURCE_DIR}
    ${libpng_SOURCE_DIR}
)