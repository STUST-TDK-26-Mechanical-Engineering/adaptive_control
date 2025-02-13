/****************************************************************************************************************************
  AsyncHTTPSRequest_Generic.h
  
  For ESP32, ESP8266 and STM32 with built-in LAN8742A Ethernet (Nucleo-144, DISCOVERY, etc)
  
  AsyncHTTPSRequest is a library for the ESP8266, ESP32 and currently STM32 run built-in Ethernet WebServer
  
  Based on and modified from AsyncHTTPRequest Library (https://github.com/boblemaire/asyncHTTPrequest)
  
  Built by Khoi Hoang https://github.com/khoih-prog/AsyncHTTPSRequest_Generic
  
  Copyright (C) <2018>  <Bob Lemaire, IoTaWatt, Inc.>
  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License 
  as published bythe Free Software Foundation, either version 3 of the License, or (at your option) any later version.
  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
  You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>.  
 
  Version: 1.1.0
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0    K Hoang     21/10/2021 Initial coding to support only ESP32
  1.1.0    K Hoang     23/10/2021 Add support to ESP32-based WT32-ETH01 using LAN8720
 *****************************************************************************************************************************/

#pragma once

#ifndef ASYNC_HTTPS_REQUEST_GENERIC_H
#define ASYNC_HTTPS_REQUEST_GENERIC_H

#if !(ESP32)
  #error This AsyncHTTPSRequest library is currently supporting only ESP32
#endif

#define ASYNC_HTTPS_REQUEST_GENERIC_VERSION   "AsyncHTTPSRequest_Generic v1.1.0"

#include <Arduino.h>

#include "AsyncHTTPSRequest_Debug_Generic.h"

#ifndef DEBUG_IOTA_PORT
  #define DEBUG_IOTA_PORT Serial
#endif

#ifdef DEBUG_IOTA_HTTP
  #define DEBUG_IOTA_HTTP_SET     true
#else
  #define DEBUG_IOTA_HTTP_SET     false
#endif

#define ASYNC_TCP_SSL_ENABLED     true

// KH add for HTTPS
#define SAFE_DELETE(object)         if (object) { delete object;}
#define SAFE_DELETE_ARRAY(object)   if (object) { delete[] object;}

#define ASYNC_HTTP_PREFIX         "HTTP://"
#define ASYNC_HTTP_PORT           80

#define ASYNC_HTTPS_PREFIX        "HTTPS://"
#define ASYNC_HTTPS_PORT          443

#include <functional>
#include <vector>

#define SHA1_SIZE 20
//////

#if ESP32

  //#define ASYNC_TCP_SSL_ENABLED     true
  
  #include <AsyncTCP_SSL.h>
  
  // KH mod
  #define MUTEX_LOCK_NR           if (xSemaphoreTakeRecursive(threadLock,portMAX_DELAY) != pdTRUE) { return;}
  #define MUTEX_LOCK(returnVal)   if (xSemaphoreTakeRecursive(threadLock,portMAX_DELAY) != pdTRUE) { return returnVal;}
  
  #define _AHTTPS_lock       xSemaphoreTakeRecursive(threadLock,portMAX_DELAY)
  #define _AHTTPS_unlock     xSemaphoreGiveRecursive(threadLock)
  
#elif ESP8266

  //#include <ESPAsyncTCP.h>
  #error Not ready for ESP8266 yet
  #include <ESPAsyncTCP_SSL.h>
  
  #define MUTEX_LOCK_NR
  #define MUTEX_LOCK(returnVal)
  
  #define _AHTTPS_lock
  #define _AHTTPS_unlock
  
#elif ( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
       defined(STM32L0) || defined(STM32L1) || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
       defined(STM32WB) || defined(STM32MP1) )
       
  #error Not ready for STM32 yet     
  #include "STM32AsyncTCP_SSL.h"
  
  #define MUTEX_LOCK_NR
  #define MUTEX_LOCK(returnVal)
  #define _AHTTPS_lock
  #define _AHTTPS_unlock
  
#else
  #error Not supported board
#endif

#include <pgmspace.h>
#include <utility/xbuf.h>

#define DEBUG_HTTP(format,...)  if(_debug){\
    DEBUG_IOTA_PORT.printf("Debug(%3ld): ", millis()-_requestStartTime);\
    DEBUG_IOTA_PORT.printf_P(PSTR(format),##__VA_ARGS__);}

#define DEFAULT_RX_TIMEOUT 3                    // Seconds for timeout

#define HTTPCODE_CONNECTION_REFUSED  (-1)
#define HTTPCODE_SEND_HEADER_FAILED  (-2)
#define HTTPCODE_SEND_PAYLOAD_FAILED (-3)
#define HTTPCODE_NOT_CONNECTED       (-4)
#define HTTPCODE_CONNECTION_LOST     (-5)
#define HTTPCODE_NO_STREAM           (-6)
#define HTTPCODE_NO_HTTP_SERVER      (-7)
#define HTTPCODE_TOO_LESS_RAM        (-8)
#define HTTPCODE_ENCODING            (-9)
#define HTTPCODE_STREAM_WRITE        (-10)
#define HTTPCODE_TIMEOUT             (-11)

typedef enum
{
  readyStateUnsent      = 0,            // Client created, open not yet called
  readyStateOpened      = 1,            // open() has been called, connected
  readyStateHdrsRecvd   = 2,            // send() called, response headers available
  readyStateLoading     = 3,            // receiving, partial data available
  readyStateDone        = 4             // Request complete, all data available.
} reqStates;
    
class AsyncHTTPSRequest
{
    struct header
    {
      header*   next;
      char*     name;
      char*     value;
      
      header(): next(nullptr), name(nullptr), value(nullptr)
      {};
      
      ~header() 
      {
        SAFE_DELETE_ARRAY(name)
        SAFE_DELETE_ARRAY(value)
        SAFE_DELETE(next)
        //delete[] name;
        //delete[] value;
        //delete next;
      }
    };

    struct  URL 
    {
      char*   scheme;
      char*   user;
      char*   pwd;
      char*   host;
      int     port;
      char*   path;
      char*   query;
      char*   fragment;
      
      URL():  scheme(nullptr), user(nullptr), pwd(nullptr), host(nullptr),
              port(80), path(nullptr), query(nullptr), fragment(nullptr)
      {};
      
      ~URL() 
      {
        SAFE_DELETE_ARRAY(scheme)
        SAFE_DELETE_ARRAY(user)
        SAFE_DELETE_ARRAY(pwd)
        SAFE_DELETE_ARRAY(host)
        SAFE_DELETE_ARRAY(path)
        SAFE_DELETE_ARRAY(query)
        SAFE_DELETE_ARRAY(fragment)
      }
    };

    typedef std::function<void(void*, AsyncHTTPSRequest*, int readyState)> readyStateChangeCB;
    typedef std::function<void(void*, AsyncHTTPSRequest*, size_t available)> onDataCB;

  public:
    AsyncHTTPSRequest();
    ~AsyncHTTPSRequest();


    //External functions in typical order of use:
    //__________________________________________________________________________________________________________*/
    void        setDebug(bool);                                         // Turn debug message on/off
    bool        debug();                                                // is debug on or off?

    bool        open(const char* /*GET/POST*/, const char* URL);        // Initiate a request
    void        onReadyStateChange(readyStateChangeCB, void* arg = 0);  // Optional event handler for ready state change
    // or you can simply poll readyState()
    void        setTimeout(int);                                        // overide default timeout (seconds)

    void        setReqHeader(const char* name, const char* value);      // add a request header
    void        setReqHeader(const char* name, int32_t value);          // overload to use integer value
    
#if (ESP32 || ESP8266)
    void        setReqHeader(const char* name, const __FlashStringHelper* value);
    void        setReqHeader(const __FlashStringHelper *name, const char* value);
    void        setReqHeader(const __FlashStringHelper *name, const __FlashStringHelper* value);
    void        setReqHeader(const __FlashStringHelper *name, int32_t value);
#endif

    bool        send();                                                 // Send the request (GET)
    bool        send(String body);                                      // Send the request (POST)
    bool        send(const char* body);                                 // Send the request (POST)
    bool        send(const uint8_t* buffer, size_t len);                // Send the request (POST) (binary data?)
    bool        send(xbuf* body, size_t len);                           // Send the request (POST) data in an xbuf
    void        abort();                                                // Abort the current operation

    reqStates   readyState();                                           // Return the ready state

    int         respHeaderCount();                                      // Retrieve count of response headers
    char*       respHeaderName(int index);                              // Return header name by index
    char*       respHeaderValue(int index);                             // Return header value by index
    char*       respHeaderValue(const char* name);                      // Return header value by name
    
    bool        respHeaderExists(const char* name);                     // Does header exist by name?
    
#if (ESP32 || ESP8266)
    char*       respHeaderValue(const __FlashStringHelper *name);
    bool        respHeaderExists(const __FlashStringHelper *name);
#endif
    
    String      headers();                                              // Return all headers as String

    void        onData(onDataCB, void* arg = 0);                        // Notify when min data is available
    size_t      available();                                            // response available
    size_t      responseLength();                                       // indicated response length or sum of chunks to date
    int         responseHTTPcode();                                     // HTTP response code or (negative) error code
    String      responseText();                                         // response (whole* or partial* as string)
    
    char*       responseLongText();                                     // response long (whole* or partial* as string)
    
    size_t      responseRead(uint8_t* buffer, size_t len);              // Read response into buffer
    uint32_t    elapsedTime();                                          // Elapsed time of in progress transaction or last completed (ms)
    String      version();                                              // Version of AsyncHTTPSRequest
    //___________________________________________________________________________________________________________________________________

    // KH, for HTTPS
    AsyncHTTPSRequest& setSecure(bool secure);
    AsyncHTTPSRequest& addServerFingerprint(const uint8_t* fingerprint);
    
    //////
    
  private:

    // New in v1.1.1
    bool _requestReadyToSend;
    //////
    
    // New in v1.1.0
    typedef enum  { HTTPmethodGET, HTTPmethodPOST, HTTPmethodPUT, HTTPmethodPATCH, HTTPmethodDELETE, HTTPmethodHEAD, HTTPmethodMAX } HTTPmethod;
    
    HTTPmethod _HTTPmethod;
    
    const char* _HTTPmethodStringwithSpace[HTTPmethodMAX] = {"GET ", "POST ", "PUT ", "PATCH ", "DELETE ", "HEAD "};
    //////
    
    reqStates       _readyState;

    int16_t         _HTTPcode;                  // HTTP response code or (negative) exception code
    bool            _chunked;                   // Processing chunked response
    bool            _debug;                     // Debug state
    uint32_t        _timeout;                   // Default or user overide RxTimeout in seconds
    uint32_t        _lastActivity;              // Time of last activity
    uint32_t        _requestStartTime;          // Time last open() issued
    uint32_t        _requestEndTime;            // Time of last disconnect
    URL*            _URL;                       // -> URL data structure
    char*           _connectedHost;             // Host when connected
    int             _connectedPort;             // Port when connected
    AsyncSSLClient*    _client;                    // ESPAsyncTCP AsyncSSLClient instance
    size_t          _contentLength;             // content-length header value or sum of chunk headers
    size_t          _contentRead;               // number of bytes retrieved by user since last open()
    readyStateChangeCB  _readyStateChangeCB;    // optional callback for readyState change
    void*           _readyStateChangeCBarg;     // associated user argument
    onDataCB        _onDataCB;                  // optional callback when data received
    void*           _onDataCBarg;               // associated user argument

#ifdef ESP32
    SemaphoreHandle_t threadLock;
#endif

    // request and response String buffers and header list (same queue for request and response).

    xbuf*       _request;                       // Tx data buffer
    xbuf*       _response;                      // Rx data buffer for headers
    xbuf*       _chunks;                        // First stage for chunked response
    header*     _headers;                       // request or (readyState > readyStateHdrsRcvd) response headers

    // Protected functions

    header*     _addHeader(const char*, const char*);
    header*     _getHeader(const char*);
    header*     _getHeader(int);
    bool        _buildRequest();
    bool        _parseURL(const char*);
    bool        _parseURL(String);
    void        _processChunks();
    bool        _connect();
    size_t      _send();
    void        _setReadyState(reqStates);
    
#if (ESP32 || ESP8266)    
    char*       _charstar(const __FlashStringHelper *str);
#endif

    // callbacks

    void        _onConnect(AsyncSSLClient*);
    void        _onDisconnect(AsyncSSLClient*);
    void        _onData(void*, size_t);
    void        _onError(AsyncSSLClient*, int8_t);
    void        _onPoll(AsyncSSLClient*);
    bool        _collectHeaders();
    
    // KH New for HTTPS
    bool        _secure;
    bool _tlsBadFingerprint = false;
    std::vector<std::array<uint8_t, SHA1_SIZE>> _secureServerFingerprints;
};

#include "AsyncHTTPSRequest_Impl_Generic.h"

#endif    // ASYNC_HTTPS_REQUEST_GENERIC_H
