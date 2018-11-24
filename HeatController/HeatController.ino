#include <WiFiServer.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include "configs.h"
#include "strings.h"
#include "logUtil.h"

//ESP8266WebServer server(80);

bool ConnectToAP(const char *ssid, const char *pwd);
void EEWriteStr(const char * str, size_t addr);
size_t EEReadStrSize(const size_t &addr);
void EEReadString(char *buff, size_t addr);

void setup()
{
    LOG_INF("Init");
    Serial.begin(g_serialBaudRate);
    EEPROM.begin(g_eepromSize);
    ConnectToAP("OSI", "Gerda_plazma_2017");
}

void loop()
{
    //LOG_INF("Kek");
    //delay(1000);
}

bool ConnectToAP(const char *ssid, const char *pwd)
{
    LOG_INF("ssid : ");
    LOG_INF(ssid);
    LOG_INF("pwd : ");
    LOG_INF(pwd);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pwd);
    LOG_INF("Connecting...");
    for (size_t i = 0; i < g_reconnectTries; ++i)
    {
        LOG_INF(i);
        if (WiFi.status() == WL_CONNECTED)
        {
            LOG_INF("Connected to AP");
            LOG_INF("IP address: ");
            LOG_INF(WiFi.localIP());
            return true;
        }
        delay(g_reconnectDelay);
    }
    LOG_WRN("Connection failed");
    return false;
}

void EEWriteStr(const char * str, size_t addr)
{
    size_t strSize = strlen(str);
    EEPROM.write(addr++, strSize);
    for (size_t i = 0; i < strSize; i++, addr++)
    {
        EEPROM.write(addr, str[i]);
    }
    EEPROM.write(++addr, 0);
    EEPROM.commit();
}

size_t EEReadStrSize(const size_t &addr)
{
    return EEPROM.read(addr);
}

void EEReadString(char *buff, size_t addr)
{
    size_t strSize = EEReadStrSize(addr);
    ++addr;
    for (size_t i = 0; i < strSize; i++, addr++)
    {
        buff[i] = EEPROM.read(addr);
    }
}