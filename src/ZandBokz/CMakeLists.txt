add_executable(ZANDBOKZ 
    src/zandbokz.cpp
)

target_compile_definitions(ZANDBOKZ PRIVATE _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING)

if(MSVC)
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
target_link_libraries(ZANDBOKZ
    PRIVATE ZBE_LIB
    PRIVATE dbghelp
)

# Copiar automáticamente TODAS las DLL necesarias al lado del exe
# if (WIN32)
#     add_custom_command(TARGET ZANDBOKZ POST_BUILD
#         COMMAND ${CMAKE_COMMAND} -E copy_if_different
#             $<TARGET_RUNTIME_DLLS:ZANDBOKZ>
#             $<TARGET_FILE_DIR:ZANDBOKZ>
#         COMMAND_EXPAND_LISTS
#     )
# endif()

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

# --- Debug: comprobar si el ejecutable está generando import library ---
get_target_property(outimplib ZANDBOKZ IMPORT_LIBRARY)
if(outimplib)
    message(WARNING "X ZANDBOKZ está configurado con IMPORT_LIBRARY='${outimplib}' (puede estar tratándose como DLL)")
else()
    message(STATUS "V ZANDBOKZ no genera import library (es un ejecutable puro)")
endif()

# También mostrar WIN32_EXECUTABLE para confirmar
get_target_property(exe_type ZANDBOKZ WIN32_EXECUTABLE)
message(STATUS "WIN32_EXECUTABLE for ZANDBOKZ = ${exe_type}")