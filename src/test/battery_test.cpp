#include "catch_amalgamated.hpp"

#include "battery.h"
#include "mock_arduino.h"

TEST_CASE("Basic Battery Works", "[battery]")
{
    setAnalogValue(0);

    Battery* b = Battery::battery();
    b->init();
    REQUIRE(b->volts() == 0);
    REQUIRE(!b->charging());
}

TEST_CASE("Battery with voltage works", "[battery]")
{
    setAnalogValue(2048);

    Battery* b = Battery::battery();
    b->init();
    REQUIRE(b->volts() == 3.630886555f);
    REQUIRE(!b->charging());
}

TEST_CASE("Battery with percentage works", "[battery]")
{
    Battery* b = Battery::battery();
    b->init();

    for (int i = 0; i < 10; i++) {
        setAnalogValue(1900 + i * 100);
        b->loop();
    }
    REQUIRE(b->percentage() == 90);
}

TEST_CASE("Battery charging works", "[battery]")
{
    Battery* b = Battery::battery();
    b->init();

    setAnalogValue(3000);
    REQUIRE(b->charging());
}