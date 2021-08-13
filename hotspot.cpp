#include "hotspot.h"

#include <WiFi.h>

Hotspot::Hotspot() : ap_ssid(NULL), ap_passwd(new String("airquality")), running(false) {}
Hotspot::~Hotspot()
{
    delete (this->ap_ssid);
    delete (this->ap_passwd);
}

void Hotspot::setup()
{
    this->running = true;
    String mac = WiFi.macAddress();
    this->ap_ssid = new String("AirQuality-" + mac.substring(0, 2) + mac[3]);

    WiFi.softAP(this->ap_ssid->c_str(), this->ap_passwd->c_str());
    Serial.println("Access point running.");
    Serial.print("SSID: ");
    Serial.println(this->ap_ssid->c_str());
    Serial.print("Password: ");
    Serial.println(this->ap_passwd->c_str());
    Serial.print("IP address: ");
    Serial.print(WiFi.softAPIP());
    Serial.println("");
    Serial.print("Please connect to http://");
    Serial.println(WiFi.softAPIP());
}

void Hotspot::shutdown()
{
    WiFi.mode(WIFI_OFF);
    WiFi.setSleep(true);
    delay(1);
}

const char *Hotspot::ssid()
{
    return this->ap_ssid != NULL ? this->ap_ssid->c_str() : NULL;
}

const char *Hotspot::password()
{
    return this->ap_passwd != NULL ? this->ap_passwd->c_str() : NULL;
}

bool Hotspot::enabled()
{
    return this->running;
}