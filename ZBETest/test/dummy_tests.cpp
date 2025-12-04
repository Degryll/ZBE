#if __has_include(<catch2/catch_test_macros.hpp>)
#include <catch2/catch_test_macros.hpp>
#elif __has_include(<catch2/catch.hpp>)
#include <catch2/catch.hpp>
#else
#error "Catch2 not found - please make sure Catch2 is provided by the project dependencies"
#endif

#include "ZBE/core/tools/containers/RsrcDictionary.h"
// TODO: Comprobar que también funciona con clases compiladas.

constexpr int add_constexpr(int a, int b) {
  return a + b;
}

static_assert(add_constexpr(2, 3) == 5, "constexpr add failed");

TEST_CASE("Cosa", "[constexpr]") {
  REQUIRE(add_constexpr(2, 3) == 5);
}