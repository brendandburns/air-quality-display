#ifndef __CONTENT_H__
#define __CONTENT_H__

#include <ESPAsyncWebServer.h>
#include "data.h"

void setSensorData(DataSet *data);
void handleNotFound(AsyncWebServerRequest *request);
void handleIndex(AsyncWebServerRequest *request);
void handleApi(AsyncWebServerRequest *request);

#endif