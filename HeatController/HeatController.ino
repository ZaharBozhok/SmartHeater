#include <WiFiServer.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include "configs.h"
#include "strings.h"
#include "logUtil.h"


//ESP8266WebServer server(80);

const float g_seconds = 0.25;
const size_t g_ticks = 312500 * g_seconds;

void ConfigurationMode(const char *ssid, const char *pwd);
bool ConnectToAP(const char *ssid, const char *pwd);
void EEWriteStr(const char * str, size_t addr);
size_t EEReadStrSize(const size_t &addr);
void EEReadString(char *buff, size_t addr);
void PinConfiguration(void);

unsigned long lastUsage1 = 0;
void ButtonPressedHandler1(void)
{
    unsigned long currTime = millis();
    if (currTime - lastUsage1 > g_buttIntWindow)
    {
        digitalWrite(g_pinLed1, !digitalRead(g_pinLed1));
        digitalWrite(g_pinRelay1, !digitalRead(g_pinRelay1));
    }
    lastUsage1 = currTime;
}

unsigned long lastUsage2 = 0;
void ButtonPressedHandler2(void)
{
    unsigned long currTime = millis();
    if (currTime - lastUsage2 > g_buttIntWindow)
    {
        digitalWrite(g_pinLed2, !digitalRead(g_pinLed2));
        digitalWrite(g_pinRelay2, !digitalRead(g_pinRelay2));
    }
    lastUsage2 = currTime;
}

void setup()
{
    Serial.begin(g_serialBaudRate);
    EEPROM.begin(g_eepromSize);
    PinConfiguration();
    LOG_INF("Configuration done.");

    attachInterrupt(g_pinButton1, ButtonPressedHandler1, RISING);
    attachInterrupt(g_pinButton2, ButtonPressedHandler2, RISING);
    /*
    if (!ConnectToAP("MikroTik", ""))
    {
        ConfigurationMode(("Heater"+WiFi.macAddress()).c_str(), "");
    }
    */
    LOG_INF("Mac address : ");
    LOG_INF(WiFi.macAddress());
    
}

bool l1 = 0;
bool l2 = 0;

void loop()
{
    /*digitalWrite(g_pinRelay1, HIGH);
    digitalWrite(g_pinRelay2, HIGH);
    LOG_INF("1");
    delay(1000);
    digitalWrite(g_pinRelay1, LOW);
    digitalWrite(g_pinRelay2, LOW);
    LOG_INF("0");
    delay(1000);*/
    /*
    bool b1 = digitalRead(g_pinButton1);
    bool b2 = digitalRead(g_pinButton2);
    if (b1)
    {
        LOG_INF("b1 -> 1");
        l1 = !l1;
        digitalWrite(g_pinLed1, l1);
        digitalWrite(g_pinRelay1, l1);
    }
    if (b2)
    {
        LOG_INF("b2 -> 1");
        l2 = !l2;
        digitalWrite(g_pinLed2, l2);
        digitalWrite(g_pinRelay2, l2);
    }
    delay(100);
    */
}

void PinConfiguration(void)
{
    LOG_INF("");
    pinMode(g_pinLed1, OUTPUT);
    pinMode(g_pinLed2, OUTPUT);
    pinMode(g_pinButton1, INPUT_PULLUP);
    pinMode(g_pinButton2, INPUT_PULLUP);
    pinMode(g_pinRelay1, OUTPUT);
    pinMode(g_pinRelay2, OUTPUT);
    return;
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

void ConfigurationMode(const char *ssid, const char *pwd)
{
    WiFi.softAP(ssid, pwd);
    LOG_INF("Access Point ip address : ");
    LOG_INF(WiFi.softAPIP());
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

//void getMacWithoutDots(char **buff) {
//    uint8_t mac[6];
//    //char macStr[18] = { 0 };
//    wifi_get_macaddr(STATION_IF, mac);
//
//    sprintf(*buff, "%02x%02x%02x%02x%02x%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
//}