# Enable CTest integration
include(CTest)

# Test sources
set(TEST_SOURCES
  test/core/entities/EntityTest.cpp
  test/core/tools/containers/RsrcStoreTest.cpp
)

# Create test executable
add_executable(ZBETest ${TEST_SOURCES})
# Include project headers
target_include_directories(ZBETest PRIVATE ${CMAKE_SOURCE_DIR}/include)
# Link project options and main library (defined in the main project)
target_link_libraries(ZBETest PRIVATE ZBE::ZBE_options ZBE_LIB)

# Prefer Catch2's provided main if available
if(TARGET Catch2::Catch2WithMain)
  target_link_libraries(ZBETest PRIVATE Catch2::Catch2WithMain)
elseif(TARGET Catch2::Catch2)
  target_link_libraries(ZBETest PRIVATE Catch2::Catch2)
else()
  message(WARNING "Catch2 target not present. Ensure Catch2 is added as a dependency for tests.")
endif()

# Register the test with CTest.
# If Catch2's CMake integration is available we can auto-discover and register
# individual test cases so `ctest` will list/run them separately.
add_test(NAME ZBETest COMMAND ZBETest)
# TODO: ¿Como hacemos que liste, en la salida, todos los TEST_CASE pasados?
# ctest -R ZBETest -V
# cmake .. -DBUILD_TESTING=ON && cmake --build . -- -j$(nproc) 2>&1 | tail -10