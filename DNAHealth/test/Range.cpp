#include "Range.h"
#include <parts/doctest_fwd.h>

TEST_CASE("Test negative values") {
    Range r;
    r.add(-10);
    REQUIRE(r.min == -10);
    REQUIRE(r.max == -10);
}
