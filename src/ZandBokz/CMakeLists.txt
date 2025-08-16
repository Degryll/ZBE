# include(GenerateExportHeader)
add_executable(ZANDBOKZ 
  src/zandbokz.cpp
)

IF (MSVC)
  target_compile_options(ZANDBOKZ PRIVATE /bigobj)
ENDIF()

target_link_libraries(ZANDBOKZ
PRIVATE ZBE_LIB
# PRIVATE png #TODO ver si funciona sin este
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

get_target_property(defs_publicas ZANDBOKZ INTERFACE_COMPILE_DEFINITIONS)
get_target_property(defs_privadas ZANDBOKZ COMPILE_DEFINITIONS)

message(STATUS "Definiciones ZANDBOKZ PUBLICAS: ${defs_publicas}")
message(STATUS "Definiciones ZANDBOKZ PRIVADAS: ${defs_privadas}")
