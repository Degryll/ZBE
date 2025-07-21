# include(GenerateExportHeader)
add_executable(ZANDBOKZ 
  src/zandbokz.cpp
)
set_target_properties(ZANDBOKZ PROPERTIES
  ENABLE_EXPORTS OFF
  IMPORT_LIBRARY ""
  ARCHIVE_OUTPUT_NAME ""
  RUNTIME_OUTPUT_NAME ZANDBOKZ
)

# IF (WIN32)
#   set_target_properties(glew PROPERTIES
#     IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/extlibs/glew/2.2.0/windows/x64/glew32s.lib"
#     INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/extlibs/glew/2.2.0/include"
#   )
# ELSE()
#   set_target_properties(glew PROPERTIES
#     IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/extlibs/glew/2.2.0/linux/libGLEW.a"
#     INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/extlibs/glew/2.2.0/include"
#   )
# ENDIF()

set_target_properties(ZANDBOKZ PROPERTIES ENABLE_EXPORTS OFF)
set_target_properties(ZANDBOKZ PROPERTIES IMPORT_LIBRARY "")

target_link_libraries(ZANDBOKZ
PRIVATE ZBE_LIB
# PRIVATE png #TODO ver si funciona sin este
)

target_include_directories(ZANDBOKZ PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
target_include_directories(ZANDBOKZ PRIVATE $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)
target_include_directories(ZANDBOKZ PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/ZandBokz/include>)

target_include_directories(ZANDBOKZ SYSTEM PRIVATE ${glm_SOURCE_DIR})
target_include_directories(ZANDBOKZ SYSTEM PRIVATE ${SDL2_SOURCE_DIR})
target_include_directories(ZANDBOKZ SYSTEM PRIVATE ${tinygltf_SOURCE_DIR})
target_include_directories(ZANDBOKZ SYSTEM PRIVATE ${vorbis_SOURCE_DIR}/include)
target_include_directories(ZANDBOKZ SYSTEM PRIVATE ${ogg_SOURCE_DIR})
target_include_directories(ZANDBOKZ SYSTEM PRIVATE ${libpng_SOURCE_DIR})

get_target_property(defs_publicas ZANDBOKZ INTERFACE_COMPILE_DEFINITIONS)
get_target_property(defs_privadas ZANDBOKZ COMPILE_DEFINITIONS)

message(STATUS "Definiciones ZANDBOKZ PUBLICAS: ${defs_publicas}")
message(STATUS "Definiciones ZANDBOKZ PRIVADAS: ${defs_privadas}")
