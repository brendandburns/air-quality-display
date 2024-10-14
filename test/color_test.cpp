#include "catch_amalgamated.hpp"

#include "colors.h"
#include "mock/mock_arduino.h"

TEST_CASE("Foreground color works", "[colors]")
{
    uint16_t pm2_5 = 0;
    AirQualityColors colors(&pm2_5);

    REQUIRE(colors.foreground() == TFT_BLACK);
    pm2_5 = 300;
    REQUIRE(colors.foreground() == TFT_WHITE);
}