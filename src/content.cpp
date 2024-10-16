#include "content.h"
#include "data.h"

#include <cstdio>
#include <sstream>

DataSet *sensor_data;

#ifdef ESP32
class AsyncWebRequest : public WebRequestInterface {
  private:
    AsyncWebServerRequest *request;

  public:
    AsyncWebRequest(AsyncWebServerRequest *req) {
      request = req;
    }

    void send(int code, const char *type, const char *message) {
      request->send(code, type, message);
    }
};
#endif

void setSensorData(DataSet *data) {
  sensor_data = data;
}

#ifdef ESP32
void handleNotFoundAsync(AsyncWebServerRequest *request) {
  AsyncWebRequest req(request);
  handleNotFound(&req);
}

void handleIndexAsync(AsyncWebServerRequest *request) {
  AsyncWebRequest req(request);
  handleIndex(&req);
}

void handleApiAsync(AsyncWebServerRequest* request) {
  AsyncWebRequest req(request);
  handleApi(&req);
}
#endif

void handleNotFound(WebRequestInterface *request){
  request->send(404, "text/plain", "404: Unknown");
}

void handleIndex(WebRequestInterface *request) {
  char page[1024];

  snprintf(page,
           sizeof(page),
           "<html><body>PM2.5: %g</body></html>",
           sensor_data->data()[0]);

  request->send(200, "text/html", page);
}

void handleApi(WebRequestInterface *request) {
  char json[1024];

  snprintf(json, sizeof(json), "{ \"pm2_5\": %g }", sensor_data->data()[0]);

  request->send(200, "application/json", json);
}

void handleMetrics(WebRequestInterface *request) {
  char metrics[1024];

  // print the prometheus help text
  std::stringstream ss;
  ss << "# HELP pm2_5 PM2.5 particulate matter\n";
  ss << "# TYPE pm2_5 gauge\n";
  ss << "pm2_5 " << sensor_data->data()[0] << "\n";

  request->send(200, "text/plain", ss.str().c_str());
}