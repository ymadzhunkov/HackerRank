#include "CyclicHash.h"
#include <iostream>
#include <parts/doctest_fwd.h>

TEST_CASE("Test hashing some string") {
    const char *a = "TwoTwoThreeTwoT";
    const int n = 4;
    CyclicHash hf(n, 32);
    auto v = hf.init(a);
    int count = 0;
    for (int i = n; a[i] != '\0'; i++)
        if (v == hf.update(a[i - n], a[i])) count++;
    REQUIRE(count == 2);
}
