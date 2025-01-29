# include(GenerateExportHeader)


add_executable(ZANDBOKZ 
  src/zandbokz.cpp
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

target_link_libraries(ZANDBOKZ
PRIVATE ZBE_LIB
PRIVATE png #TODO ver si funciona sin este
)

target_include_directories(ZANDBOKZ PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
target_include_directories(ZANDBOKZ PUBLIC $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)
target_include_directories(ZANDBOKZ PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/ZandBokz/include>)

target_include_directories(ZANDBOKZ SYSTEM PRIVATE ${glm_SOURCE_DIR})
target_include_directories(ZANDBOKZ SYSTEM PRIVATE ${SDL2_SOURCE_DIR})
target_include_directories(ZANDBOKZ SYSTEM PRIVATE ${tinygltf_SOURCE_DIR})


# target_compile_features(ZANDBOKZ PUBLIC cxx_std_20)

# set_target_properties(ZANDBOKZ PROPERTIES VERSION ${PROJECT_VERSION} CXX_VISIBILITY_PRESET hidden VISIBILITY_INLINES_HIDDEN YES) 
