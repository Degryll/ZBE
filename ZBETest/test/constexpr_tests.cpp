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

TEST_CASE("constexpr add works", "[constexpr]") {
  REQUIRE(add_constexpr(2, 3) == 4);
}

TEST_CASE("RsrcDictionary insert and get", "[containers]") {
  auto& dict = zbe::RsrcDictionary<std::string>::getInstance();
  dict.clear();

  dict.insert("player_sprite", "assets/player.png");
  REQUIRE(dict.contains("player_sprite"));
  REQUIRE(dict.get("player_sprite") == "assets/player.png");
}

TEST_CASE("RsrcDictionary get non-existent resource", "[containers]") {
  auto& dict = zbe::RsrcDictionary<std::string>::getInstance();
  dict.clear();

  std::string result = dict.get("non_existent");
  REQUIRE(result == "");
}

TEST_CASE("RsrcDictionary contains", "[containers]") {
  auto& dict = zbe::RsrcDictionary<std::string>::getInstance();
  dict.clear();

  dict.insert("resource_a", "value_a");
  REQUIRE(dict.contains("resource_a"));
  REQUIRE_FALSE(dict.contains("resource_b"));
}

TEST_CASE("RsrcDictionary remove", "[containers]") {
  auto& dict = zbe::RsrcDictionary<std::string>::getInstance();
  dict.clear();

  dict.insert("temp_resource", "temporary");
  REQUIRE(dict.contains("temp_resource"));

  std::string removed = dict.remove("temp_resource");
  REQUIRE(removed == "temporary");
  REQUIRE_FALSE(dict.contains("temp_resource"));
}

TEST_CASE("RsrcDictionary with uint64_t (NameRsrcDictionary)", "[containers]") {
  auto& dict = zbe::NameRsrcDictionary::getInstance();
  dict.clear();

  dict.insert("sound_effect_1", 1001u);
  dict.insert("sound_effect_2", 1002u);

  REQUIRE(dict.get("sound_effect_1") == 1001u);
  REQUIRE(dict.get("sound_effect_2") == 1002u);
}

TEST_CASE("IdRsrcDictionary insert and get", "[containers]") {
  auto& dict = zbe::IdRsrcDictionary::getInstance();
  dict.clear();

  dict.insert(10, 100);
  REQUIRE(dict.get(10) == 100);
}

TEST_CASE("IdRsrcDictionary remove", "[containers]") {
  auto& dict = zbe::IdRsrcDictionary::getInstance();
  dict.clear();

  dict.insert(20, 200);
  REQUIRE(dict.get(20) == 200);

  uint64_t removed = dict.remove(20);
  REQUIRE(removed == 200);
  REQUIRE(dict.get(20) == 0);
}
