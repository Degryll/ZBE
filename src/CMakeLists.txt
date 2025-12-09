include_directories(ZBE)
add_subdirectory(ZBE)
link_directories(ZBE)
add_subdirectory(ZandBokz)

if(BUILD_TESTING)
  message(AUTHOR_WARNING "Building Tests.")
  add_subdirectory(ZBETest)
endif()