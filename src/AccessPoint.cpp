#include <Arduino.h>

#include <WiFi.h>
#include <WiFiAP.h>

#include "AccessPoint.h"

const char *ssid = "OpenTank-AP";
const char *password = "UltimateTonk";

bool startAP()
{
    return WiFi.softAP(ssid, password, 1, 0, 1);
}

IPAddress getIP()
{
    return WiFi.softAPIP();
}