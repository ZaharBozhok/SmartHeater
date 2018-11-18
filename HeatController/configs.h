#pragma once
#ifndef CONFIGS_H
#define CONFIGS_H
typedef uint16_t eepromaddr_t;
typedef uint8_t pin_t;

const eepromaddr_t g_eeSsid = 0;
const eepromaddr_t g_eePwd = 34;

const pin_t g_pinRelay = 12;

const size_t g_serialBaudRate = 9600;
const size_t g_eepromSize = 512;
#endif