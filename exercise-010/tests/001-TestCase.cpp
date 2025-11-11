#include "../myvector.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("MyVector basic functionality") {
    MyVector v;

    SECTION("initial size is zero") {
        REQUIRE(v.size() == 0);
    }
    // ... weitere Tests ...
}
