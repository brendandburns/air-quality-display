#include "catch_amalgamated.hpp"

#include "aqi.h"

TEST_CASE( "Measure works", "[aqi]" )
{
    REQUIRE(measure(4) == GOOD);
    REQUIRE(measure(20) == MODERATE);
    REQUIRE(measure(40) == USG);
    REQUIRE(measure(120) == UNHEALTHY);
    REQUIRE(measure(245) == VERY_UNHEALTHY);
    REQUIRE(measure(400) == HAZARDOUS);
}

TEST_CASE( "Calculate AQI works", "[aqi]")
{
    REQUIRE(calculateAqi(14) == 53.795795441f);
    REQUIRE(calculateAqi(34) == 83.225219727f);
    REQUIRE(calculateAqi(120) == 171.675674438f);
    REQUIRE(calculateAqi(245) == 295.549560547f);
    REQUIRE(calculateAqi(400) == 449.153137207f);
}

TEST_CASE( "Apply adjustment works", "[aqi]" )
{
    REQUIRE(applyAdjustment(14, WOODSMOKE) == 8);
    REQUIRE(applyAdjustment(25, NONE) == 25);
}