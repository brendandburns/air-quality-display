#ifndef __HOTSPOT_H__
#define __HOTSPOT_H__

#include <Arduino.h>

class Hotspot {
    private:
        String *ap_ssid;
        String *ap_passwd;
        bool running;

    public:
        Hotspot();
        ~Hotspot();

        void setup();
        void shutdown();

        bool enabled();
        const char* ssid();
        const char* password();
};

#endif