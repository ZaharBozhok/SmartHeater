#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include "configs.h"
#include "strings.h"

ESP8266WebServer server(80);

bool connectToAP(const char *ssid, const char *pwd)
{
    WiFi.mode(WIFI_STA);
    //WiFi.setAutoReconnect(true);
    //Serial.print("Password : ");
    //Serial.println(pwd);
    WiFi.begin(ssid, pwd);
    //Serial.print("Connecting to ");
    //Serial.print(savedAPssid);
    //Serial.println("...");
    for (int i = 0; i < 10; i++)
    {
        //Serial.print("Try #");
        //Serial.print(i + 1);
        //Serial.println("...");
        if (WiFi.status() == WL_CONNECTED)
        {
            //Serial.println("WiFi connected");
            //Serial.println("IP address: ");
            //Serial.println(WiFi.localIP());
            return true;
        }
        delay(2000);
    }
    return false;
}


void setup()
{
    Serial.begin(g_serialBaudRate);
    EEPROM.begin(g_eepromSize);
    if (connectToAP() == false);
}

void loop()
{

}