#if __has_include(<catch2/catch_test_macros.hpp>)
#include <catch2/catch_test_macros.hpp>
#elif __has_include(<catch2/catch.hpp>)
#include <catch2/catch.hpp>
#else
#error "Catch2 not found - please make sure Catch2 is provided by the project dependencies"
#endif

#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/system/SysError.h"

#include <memory>

namespace zbe {

TEST_CASE("RsrcStore basic operations", "[RsrcStore]") {
    RsrcStore<int>& store = RsrcStore<int>::getInstance();
    store.clear();  // Clear the store before each test

    SECTION("Insert and get by id") {
        auto resource = std::make_shared<int>(42);
        store.insert(1, resource);
        auto retrieved = store.get(1);
        REQUIRE(retrieved != nullptr);
        REQUIRE(*retrieved == 42);
    }

    SECTION("Insert with name") {
        auto resource = std::make_shared<int>(100);
        uint64_t id = store.insert("test_resource", resource);
        auto retrieved = store.get(id);
        REQUIRE(retrieved != nullptr);
        REQUIRE(*retrieved == 100);
        auto retrievedByName = store.get("test_resource");
        REQUIRE(retrievedByName == retrieved);
    }

    SECTION("Insert without id") {
        auto resource = std::make_shared<int>(200);
        uint64_t id = store.insert(resource);
        auto retrieved = store.get(id);
        REQUIRE(retrieved != nullptr);
        REQUIRE(*retrieved == 200);
    }

    SECTION("Contains by id") {
        auto resource = std::make_shared<int>(300);
        store.insert(2, resource);
        REQUIRE(store.contains(2) == true);
        REQUIRE(store.contains(3) == false);
    }

    SECTION("Contains by name") {
        auto resource = std::make_shared<int>(400);
        store.insert("named_resource", resource);
        REQUIRE(store.contains("named_resource") == true);
        REQUIRE(store.contains("nonexistent") == false);
    }

    SECTION("Remove by id") {
        auto resource = std::make_shared<int>(500);
        store.insert(3, resource);
        auto removed = store.remove(3);
        REQUIRE(removed != nullptr);
        REQUIRE(*removed == 500);
        REQUIRE(store.contains(3) == false);
    }

    SECTION("Remove by name") {
        auto resource = std::make_shared<int>(600);
        store.insert("to_remove", resource);
        auto removed = store.remove("to_remove");
        REQUIRE(removed != nullptr);
        REQUIRE(*removed == 600);
        REQUIRE(store.contains("to_remove") == false);
    }

    SECTION("Get non-existent id") {
        auto retrieved = store.get(999);
        REQUIRE(retrieved == nullptr);
        // Check if SysError is set, but since it's static, maybe not necessary
    }

    SECTION("Insert duplicate id") {
        auto resource1 = std::make_shared<int>(700);
        auto resource2 = std::make_shared<int>(800);
        store.insert(4, resource1);
        store.insert(4, resource2);  // Should fail
        auto retrieved = store.get(4);
        REQUIRE(*retrieved == 700);  // Original should remain
    }

    SECTION("Clear store") {
        auto resource = std::make_shared<int>(900);
        store.insert(5, resource);
        store.clear();
        REQUIRE(store.contains(5) == false);
    }
}

}  // namespace zbe
