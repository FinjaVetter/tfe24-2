#include "../myvector.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("MyVector basic functionality") {
    MyVector v;

    SECTION("initial size is zero") {
        REQUIRE(v.size() == 0);
    }

    SECTION("push_back increases size and stores values") {
        v.push_back(10);
        v.push_back(20);
        v.push_back(30);
        REQUIRE(v.size() == 3);
        REQUIRE(v.at(0) == 10);
        REQUIRE(v[1] == 20);
        REQUIRE(v.at(2) == 30);
    }

    SECTION("resize increases size and default initializes new elements") {
        v.push_back(5);
        v.resize(5);
        REQUIRE(v.size() == 5);
        REQUIRE(v.at(0) == 5);
        for (unsigned int i = 1; i < v.size(); ++i) {
            REQUIRE(v.at(i) == 0);
        }
    }

    SECTION("clear resets the vector size") {
        v.push_back(42);
        v.clear();
        REQUIRE(v.size() == 0);
    }

    SECTION("at throws out_of_range for invalid indexes") {
        REQUIRE_THROWS_AS(v.at(0), std::out_of_range);
        v.push_back(1);
        REQUIRE_NOTHROW(v.at(0));
        REQUIRE_THROWS_AS(v.at(100), std::out_of_range);
    }
}
