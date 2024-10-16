#ifndef __CONTENT_H__
#define __CONTENT_H__

#ifdef ESP32
#include <ESPAsyncWebServer.h>
#endif

#include "data.h"

class WebRequestInterface {
    public:
        virtual void send(int code, const char *type, const char *message) = 0;
};

void setSensorData(DataSet *data);
void handleNotFound(WebRequestInterface *request);
void handleIndex(WebRequestInterface *request);
void handleApi(WebRequestInterface *request);
void handleMetrics(WebRequestInterface *request);

#ifdef ESP32
void handleNotFoundAsync(AsyncWebServerRequest *request);
void handleIndexAsync(AsyncWebServerRequest *request);
void handleApiAsync(AsyncWebServerRequest *request);
#endif

#endif