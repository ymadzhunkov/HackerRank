#include "problem.h"
#include <parts/doctest_fwd.h>

TEST_CASE("Test 3 genes of length 4") {
    std::vector<std::string> genes = { "daka", "baka",
                                       "kaba" };
    std::vector<int> health = { 2, 3, 4 };
    Problem p(std::move(genes), std::move(health));
    REQUIRE(p.sum_health(0, 1, "dakabaka") == 5);
    REQUIRE(p.sum_health(0, 2, "dakabaka") == 9);
}

TEST_CASE("Test 3 genes of length 2") {
    std::vector<std::string> genes = { "da", "ba",
                                       "ka" };
    std::vector<int> health = { 2, 3, 4 };
    Problem p(std::move(genes), std::move(health));
    REQUIRE(p.sum_health(0, 1, "dakabaka") == 5);
    REQUIRE(p.sum_health(0, 2, "dakabaka") == 13);
    
}
