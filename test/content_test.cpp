#include "catch_amalgamated.hpp"

#include "content.h"

class MockWebRequest : public WebRequestInterface {
    public:
        int code;
        char type[1024];
        char message[1024];

        void send(int code, const char *type, const char *message) {
            this->code = code;
            strcpy(this->type, type);
            strcpy(this->message, message);
        }
};

TEST_CASE( "Handle not found", "[content]" )
{
    char message[1024];
    MockWebRequest request;

    handleNotFound(&request);

    REQUIRE(request.code == 404);
    REQUIRE(strcmp(request.type, "text/plain") == 0);
    REQUIRE(strcmp(request.message, "404: Unknown") == 0);
}

TEST_CASE("Metrics works", "[content]")
{
    MockWebRequest request;
    DataSet data(1);
    data.addDataPoint(48.0);
    setSensorData(&data);

    handleMetrics(&request);

    REQUIRE(request.code == 200);
    REQUIRE(strcmp(request.type, "text/plain") == 0);

    char* line = strtok(request.message, "\n");
    REQUIRE(strcmp(line, "# HELP pm2_5 PM2.5 particulate matter") == 0);
    line = strtok(NULL, "\n");
    REQUIRE(strcmp(line, "# TYPE pm2_5 gauge") == 0);
    line = strtok(NULL, "\n");
    REQUIRE(strcmp(line, "pm2_5 48") == 0);
}