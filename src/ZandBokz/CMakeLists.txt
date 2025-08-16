add_executable(ZANDBOKZ 
  src/zandbokz.cpp
)

IF (MSVC)
  target_compile_options(ZANDBOKZ PRIVATE /bigobj)
ENDIF()

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