#define CATCH_CONFIG_COUNTER
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "store.h"
#pragma comment(lib, "WS2_32.lib")

TEST_CASE("test")
{
    Notebook note{
        .name = "Huawei", .year = 2024, .ram = 16, .ssd = 512, .price = 50'000 };
    Store store{ .arr = {note} };
    store.write();
    store.arr.clear();
    store.read();
    REQUIRE(store.arr.size() == 1u);
    REQUIRE(store.arr[0] == note);
}
