#include "content.h"
#include "data.h"

DataSet *sensor_data;

void setSensorData(DataSet *data) {
  sensor_data = data;
}

void handleNotFound(AsyncWebServerRequest *request){
  request->send(404, "text/plain", "404: Unknown");
}

void handleIndex(AsyncWebServerRequest *request) {
  char page[1024];

  sprintf(page,
          "<html><body>PM2.5: %g</body></html>",
          sensor_data->data()[0]);

  request->send(200, "text/html", page);
}

void handleApi(AsyncWebServerRequest *request) {
  char json[1024];

  sprintf(json, "{ \"pm2_5\": %g }", sensor_data->data()[0]);

  request->send(200, "application/json", json);
}
