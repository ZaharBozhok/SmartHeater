#pragma once
#ifndef CONFIGS_H
#define CONFIGS_H
#include "types.h"

/* Addresses where data will be strored */
const eepromaddr_t g_eeSsid = 0;
const eepromaddr_t g_eePwd = 34;

/* Pin mappings */
const pin_t g_pinLed1 = 16;
const pin_t g_pinLed2 = 13;
const pin_t g_pinButton1 = 14;
const pin_t g_pinButton2 = 12;
const pin_t g_pinRelay1 = 4;
const pin_t g_pinRelay2 = 5;

/* General configs */
const size_t g_serialBaudRate = 9600;
const size_t g_eepromSize = 512;

/* WiFi related configs */
const size_t g_reconnectTries = 10;
const size_t g_reconnectDelay = 2000;

/* Button activity handling */
const size_t g_buttIntWindow = 150; /* To remove contacts chattering (ms)*/

#define DEBUG

#endif