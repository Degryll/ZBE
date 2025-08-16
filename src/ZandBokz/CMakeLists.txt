add_executable(ZANDBOKZ 
    src/zandbokz.cpp
)

if(MSVC)
    target_compile_options(ZANDBOKZ PRIVATE /bigobj)
    set_target_properties(ZANDBOKZ PROPERTIES WIN32_EXECUTABLE OFF)
    set_target_properties(ZANDBOKZ PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
endif()

# Forzar que NO genere .lib de importación
set_target_properties(ZANDBOKZ PROPERTIES
    ENABLE_EXPORTS OFF
    IMPORT_LIBRARY ""
)

target_link_libraries(ZANDBOKZ
    PRIVATE ZBE_LIB
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

get_target_property(exe_type ZANDBOKZ WIN32_EXECUTABLE)
message(STATUS "WIN32_EXECUTABLE for ZANDBOKZ = ${exe_type}")