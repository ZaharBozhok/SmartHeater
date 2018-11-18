#pragma once
#ifndef LOGUTIL_H
#define LOGUTIL_H

//define log types
#define INFO_t  "INFO"
#define DEBUG_t "DEBG"
#define WARN_t  "WARN"
#define ERRO_t  "ERRO"

//log func
#define _LOG(x) std::cout<<(x);

//log function
#define LOG(msg, type) _LOG("[") _LOG(type) _LOG("] "); _LOG(__FILE__) _LOG(":") _LOG(__LINE__) _LOG("->") _LOG(__func__) _LOG(" : ") _LOG(msg) _LOG('\n');

#define LOG_ERR(msg) LOG(msg,ERRO_t)

#ifdef DEBUG
//log subfunctions
#define LOG_INF(msg) LOG(msg,INFO_t)
#define LOG_DBG(msg) LOG(msg,DEBUG_t)
#define LOG_WRN(msg) LOG(msg,WARN_t)


#ifdef DEBUG

#else
#define LOG(x)
#define LOG_INF(msg)
#define LOG_DBG(msg)
#define LOG_WRN(msg)
#define LOG_ERR(msg)
#endif

#endif