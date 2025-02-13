/****************************************************************************************************************************
  WebServer_WT32_ETH01.h - Dead simple web-server.
  For Ethernet shields using WT32_ETH01 (ESP32 + LAN8720)

  WebServer_WT32_ETH01 is a library for the Ethernet LAN8720 in WT32_ETH01 to run WebServer

  Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Built by Khoi Hoang https://github.com/khoih-prog/WebServer_WT32_ETH01
  Licensed under MIT license

  Original author:
  @file       Esp8266WebServer.h
  @author     Ivan Grokhotkov
  
  Version: 1.4.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      05/07/2021 Initial coding for WT32_ETH01 (ESP32 + LAN8720)
  1.1.0   K Hoang      06/07/2021 Add SSL support and HTTPS, MQTTS examples
  1.2.0   K Hoang      12/07/2021 Add common code to library. Working only with core v1.0.6-
  1.3.0   K Hoang      23/10/2021 Making compatible with breaking core v2.0.0+
  1.4.0   K Hoang      27/11/2021 Auto detect ESP32 core version
 *****************************************************************************************************************************/

#pragma once

#ifndef WEBSERVER_WT32_ETH01_H
#define WEBSERVER_WT32_ETH01_H

//#if !defined(USING_CORE_ESP32_CORE_V200_PLUS)
#if ( ( defined(ESP_ARDUINO_VERSION_MAJOR) && (ESP_ARDUINO_VERSION_MAJOR >= 2) ) && ( ARDUINO_ESP32_GIT_VER != 0x46d5afb1 ) )
  #define USING_CORE_ESP32_CORE_V200_PLUS      true
  //#warning Using code for ESP32 core v2.0.0+ in WebServer_WT32_ETH01.h
  #define WEBSERVER_WT32_ETH01_VERSION      "WebServer_WT32_ETH01 v1.4.0 for core v2.0.0+"
#else
  //#warning Using code for ESP32 core v1.0.6- in WebServer_WT32_ETH01.h
  #define WEBSERVER_WT32_ETH01_VERSION      "WebServer_WT32_ETH01 v1.4.0 for core v1.0.6-"
#endif

#if ESP32
  #warning Using ESP32 architecture for WebServer_WT32_ETH01
  #define BOARD_NAME      "WT32-ETH01"
#else  
  #error This code is designed to run on ESP32 platform! Please check your Tools->Board setting.
#endif

#include <Arduino.h>

#include "WebServer_WT32_ETH01_Debug.h"

// defined here before #include <ETH.h> to override

// I²C-address of Ethernet PHY (0 or 1 for LAN8720, 31 for TLK110)
#ifndef ETH_PHY_ADDR
  #define ETH_PHY_ADDR        1
#endif

// Type of the Ethernet PHY (LAN8720 or TLK110)
//typedef enum { ETH_PHY_LAN8720, ETH_PHY_TLK110, ETH_PHY_RTL8201, ETH_PHY_DP83848, ETH_PHY_DM9051, ETH_PHY_KSZ8081, ETH_PHY_MAX } eth_phy_type_t;

#ifndef ETH_PHY_TYPE
  #define ETH_PHY_TYPE    ETH_PHY_LAN8720
#endif

// Pin# of the enable signal for the external crystal oscillator (-1 to disable for internal APLL source)
#ifndef ETH_PHY_POWER
  #define ETH_PHY_POWER  16
#endif

// Pin# of the I²C clock signal for the Ethernet PHY
#ifndef ETH_PHY_MDC
  #define ETH_PHY_MDC     23
#endif

// Pin# of the I²C IO signal for the Ethernet PHY
#ifndef ETH_PHY_MDIO
  #define ETH_PHY_MDIO    18
#endif

/*
  //typedef enum { ETH_CLOCK_GPIO0_IN, ETH_CLOCK_GPIO0_OUT, ETH_CLOCK_GPIO16_OUT, ETH_CLOCK_GPIO17_OUT } eth_clock_mode_t;
  ETH_CLOCK_GPIO0_IN   - default: external clock from crystal oscillator
  ETH_CLOCK_GPIO0_OUT  - 50MHz clock from internal APLL output on GPIO0 - possibly an inverter is needed for LAN8720
  ETH_CLOCK_GPIO16_OUT - 50MHz clock from internal APLL output on GPIO16 - possibly an inverter is needed for LAN8720
  ETH_CLOCK_GPIO17_OUT - 50MHz clock from internal APLL inverted output on GPIO17 - tested with LAN8720
*/
#ifndef ETH_CLK_MODE
  #define ETH_CLK_MODE    ETH_CLOCK_GPIO0_IN  //  ETH_CLOCK_GPIO17_OUT
#endif

#include <ETH.h>

#include <WiFi.h>
#include <WebServer.h> // Introduce corresponding libraries

#ifndef SHIELD_TYPE
  #define SHIELD_TYPE     "ETH_PHY_LAN8720" 
#endif

extern bool WT32_ETH01_eth_connected;

extern void WT32_ETH01_onEvent();

extern void WT32_ETH01_waitForConnect();

extern bool WT32_ETH01_isConnected();

extern void WT32_ETH01_event(WiFiEvent_t event);

#include "WebServer_WT32_ETH01_Impl.h"

#endif    // WEBSERVER_WT32_ETH01_H
