# AsyncHTTPRequest_Generic

[![arduino-library-badge](https://www.ardu-badge.com/badge/AsyncHTTPRequest_Generic.svg?)](https://www.ardu-badge.com/AsyncHTTPRequest_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/AsyncHTTPRequest_Generic.svg)](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/AsyncHTTPRequest_Generic.svg)](http://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues)

---
---

## Table of Contents


* [Why do we need the new Async AsyncHTTPRequest_Generic library](#why-do-we-need-this-async-asynchttprequest_generic-library)
  * [Features](#features)
  * [Supports](#supports)
  * [Principles of operation](#principles-of-operation)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For STM32 boards to use LAN8720](#1-for-stm32-boards-to-use-lan8720)
  * [2. For STM32 boards to use Serial1](#2-for-stm32-boards-to-use-serial1)
* [Note for Platform IO using ESP32 LittleFS](#note-for-platform-io-using-esp32-littlefs) 
* [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)
* [Note for Platform IO using ESP32 LittleFS](#note-for-platform-io-using-esp32-littlefs)
* [HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)](#howto-use-analogread-with-esp32-running-wifi-andor-bluetooth-btble)
  * [1. ESP32 has 2 ADCs, named ADC1 and ADC2](#1--esp32-has-2-adcs-named-adc1-and-adc2)
  * [2. ESP32 ADCs functions](#2-esp32-adcs-functions)
  * [3. ESP32 WiFi uses ADC2 for WiFi functions](#3-esp32-wifi-uses-adc2-for-wifi-functions)
* [HOWTO use STM32F4 with LAN8720](#howto-use-stm32f4-with-lan8720)
  * [1. Wiring](#1-wiring)
  * [2. HOWTO program using STLink V-2 or V-3](#2-howto-program-using-stlink-v-2-or-v-3)
  * [3. HOWTO use Serial Port for Debugging](#3-howto-use-serial-port-for-debugging)
* [Examples](#examples)
  * [For ESP32 and ESP8266](#for-esp32-and-esp8266)
    * [1. AsyncHTTPRequest_ESP](examples/AsyncHTTPRequest_ESP)
    * [2. AsyncHTTPRequest_ESP_WiFiManager](examples/AsyncHTTPRequest_ESP_WiFiManager)
    * [3. AsyncHTTPMultiRequests_ESP](examples/AsyncHTTPMultiRequests_ESP)
  * [For STM32 using LAN8742A](#for-stm32-using-lan8742a)
    * [1. AsyncHTTPRequest_STM32](examples/AsyncHTTPRequest_STM32)
    * [2. AsyncCustomHeader_STM32](examples/AsyncCustomHeader_STM32)
    * [3. AsyncDweetGet_STM32](examples/AsyncDweetGet_STM32)
    * [4. AsyncDweetPost_STM32](examples/AsyncDweetPost_STM32)
    * [5. AsyncSimpleGET_STM32](examples/AsyncSimpleGET_STM32)
    * [6. AsyncWebClientRepeating_STM32](examples/AsyncWebClientRepeating_STM32)
  * [For STM32 using LAN8720](#for-stm32-using-lan8720)
    * [1. AsyncHTTPRequest_STM32_LAN8720](examples/STM32_LAN8720/AsyncHTTPRequest_STM32_LAN8720)
    * [2. AsyncCustomHeader_STM32_LAN8720](examples/STM32_LAN8720/AsyncCustomHeader_STM32_LAN8720)
    * [3. AsyncDweetGet_STM32_LAN8720](examples/STM32_LAN8720/AsyncDweetGet_STM32_LAN8720)
    * [4. AsyncDweetPost_STM32_LAN8720](examples/STM32_LAN8720/AsyncDweetPost_STM32_LAN8720)
    * [5. AsyncSimpleGET_STM32_LAN8720](examples/STM32_LAN8720/AsyncSimpleGET_STM32_LAN8720)
    * [6. AsyncWebClientRepeating_STM32_LAN8720](examples/STM32_LAN8720/AsyncWebClientRepeating_STM32_LAN8720)
  * [For WT32_ETH01](#for-wt32_eth01)
    * [1. AsyncHTTPRequest_WT32_ETH01](examples/WT32_ETH01/AsyncHTTPRequest_WT32_ETH01)
    * [2. AsyncHTTPMultiRequests_WT32_ETH01](examples/WT32_ETH01/AsyncHTTPMultiRequests_WT32_ETH01)
* [Example AsyncHTTPRequest_STM32](#example-asynchttprequest_stm32)
  * [1. File AsyncHTTPRequest_STM32.ino](#1-file-asynchttprequest_stm32ino)
  * [2. File defines.h](#2-file-definesh) 
* [Debug Terminal Output Samples](#debug-termimal-output-samples)
  * [1. AsyncHTTPRequest_STM32 running on STM32F7 Nucleo-144 NUCLEO_F767ZI using built-in LAN8742A ](#1-asynchttprequest_stm32-running-on-stm32f7-nucleo-144-nucleo_f767zi-using-built-in-lan8742a)
  * [2. AsyncHTTPRequest_ESP_WiFiManager running on ESP8266_NODEMCU](#2-asynchttprequest_esp_wifimanager-running-on-esp8266_nodemcu)
  * [3. AsyncHTTPRequest_ESP_WiFiManager running on ESP32_DEV](#3-asynchttprequest_esp_wifimanager-running-on-esp32_dev)
  * [4. AsyncHTTPRequest_ESP running on ESP8266_NODEMCU](#4-asynchttprequest_esp-running-on-esp8266_nodemcu)
  * [5. AsyncWebClientRepeating_STM32 running on STM32F7 Nucleo-144 NUCLEO_F767ZI using built-in LAN8742A](#5-asyncwebclientrepeating_stm32-running-on-stm32f7-nucleo-144-nucleo_f767zi-using-built-in-lan8742a)
  * [6. AsyncWebClientRepeating_STM32_LAN8720 running on STM32F4 BLACK_F407VE using LAN8720](#6-asyncwebclientrepeating_stm32_lan8720-running-on-stm32f4-black_f407ve-using-lan8720)
  * [7. AsyncHTTPMultiRequests_WT32_ETH01 on ESP32_DEV with ETH_PHY_LAN8720](#7-asynchttpmultirequests_wt32_eth01-on-esp32_dev-with-eth_phy_lan8720)
  * [8. AsyncHTTPRequest_WT32_ETH01 on ESP32_DEV with ETH_PHY_LAN8720](#8-asynchttprequest_wt32_eth01-on-esp32_dev-with-eth_phy_lan8720)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License and credits](#license-and-credits)
* [Copyright](#copyright)

---
---

## Why do we need this Async [AsyncHTTPRequest_Generic library](https://github.com/khoih-prog/AsyncHTTPRequest_Generic)

### Features

1. Asynchronous HTTP Request library for ESP8266, including ESP32-S2 (ESP32-S2 Saola, AI-Thinker ESP-12K, etc.) using built-in WiFi, WT32_ETH01 (ESP32 + LAN8720) and STM32 boards using LAN8720 or built-in LAN8742A Ethernet. 
2. Providing a subset of HTTP.
3. Relying on on **[`ESPAsyncTCP`](https://github.com/me-no-dev/ESPAsyncTCP) for ESP8266, [`AsyncTCP`](https://github.com/me-no-dev/AsyncTCP) for ESP32** using built-in WiFi
4. Relying on **[`STM32duino LwIP`](https://github.com/stm32duino/LwIP)/[`STM32duino STM32Ethernet`](https://github.com/stm32duino/STM32Ethernet)/[`STM32AsyncTCP`](https://github.com/philbowles/STM32AsyncTCP) for STM32 using LAN8720 or built-in LAN8742A Ethernet.**
5. Methods similar in format and usage to XmlHTTPrequest in Javascript.

### Supports

1. **GET, POST, PUT, PATCH, DELETE and HEAD**
2. Request and response headers
3. Chunked response
4. Single String response for short (<~5K) responses (heap permitting).
5. Optional onData callback.
6. Optional onReadyStatechange callback.

### Principles of operation

This library adds a simple HTTP layer on top of the ESPAsyncTCP/AsyncTCP/STM32 AsyncTCP library to **facilitate REST communication from a Client to a Server**. The paradigm is similar to the XMLHttpRequest in Javascript, employing the notion of a ready-state progression through the transaction request.

**Synchronization can be accomplished using callbacks on ready-state change, a callback on data receipt, or simply polling for ready-state change**. Data retrieval can be incremental as received, or bulk retrieved when the transaction completes provided there is enough heap to buffer the entire response.

The underlying buffering uses a new xbuf class. It handles both character and binary data. Class xbuf uses a chain of small (64 byte) segments that are allocated and added to the tail as data is added and deallocated from the head as data is read, achieving the same result as a dynamic circular buffer limited only by the size of heap. The xbuf implements indexOf and readUntil functions.

For short transactions, buffer space should not be an issue. In fact, it can be more economical than other methods that use larger fixed length buffers. Data is acked when retrieved by the caller, so there is some limited flow control to limit heap usage for larger transfers.

Request and response headers are handled in the typical fashion.

Chunked responses are recognized and handled transparently.

This library is based on, modified from:

1. [Bob Lemaire's asyncHTTPrequest Library](https://github.com/boblemaire/asyncHTTPrequest)

---

### Currently Supported Boards

#### 1. ESP32 including ESP32-S2 (ESP32-S2 Saola, AI-Thinker ESP-12K, etc.)

#### 2. ESP8266

#### 3. STM32F/L/H/G/WB/MP1 with built-in LAN8742A Ethernet.

1. Nucleo-144 (F429ZI, F746ZG, F756ZG, F767ZI)
2. Discovery STM32F746G-DISCOVERY
3. Any STM32 boards with enough flash/memory and already configured to run LAN8742A Ethernet.

#### 4. STM32 boards using Ethernet LAN8720

1. **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
2. **Discovery (DISCO_F746NG)**
3. **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**


#### 5. **WT32_ETH01** using ESP32-based boards and LAN8720 Ethernet

---
---

## Prerequisites

 1. [`Arduino IDE 1.8.16+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`ESP8266 Core 3.0.2+`](https://github.com/esp8266/Arduino) for ESP8266-based boards. [![Latest release](https://img.shields.io/github/release/esp8266/Arduino.svg)](https://github.com/esp8266/Arduino/releases/latest/)
 3. [`ESP32 Core 2.0.1+`](https://github.com/espressif/arduino-esp32) for ESP32-based boards. [Latest stable release ![Release Version](https://img.shields.io/github/release/espressif/arduino-esp32.svg?style=plastic)
 5. [`Arduino Core for STM32 2.1.0+`](https://github.com/stm32duino/Arduino_Core_STM32) for for STM32 using built-in Ethernet LAN8742A. [![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)
 6. [`ESPAsyncTCP v1.2.2+`](https://github.com/me-no-dev/ESPAsyncTCP) for ESP8266.
 7. [`AsyncTCP v1.1.1+`](https://github.com/me-no-dev/AsyncTCP) for ESP32.
 8. [`STM32Ethernet library v1.2.0+`](https://github.com/stm32duino/STM32Ethernet) for STM32 using built-in Ethernet LAN8742A on (Nucleo-144, Discovery). [![GitHub release](https://img.shields.io/github/release/stm32duino/STM32Ethernet.svg)](https://github.com/stm32duino/STM32Ethernet/releases/latest)
 9. [`LwIP library v2.1.2+`](https://github.com/stm32duino/LwIP) for STM32 using built-in Ethernet LAN8742A on (Nucleo-144, Discovery). [![GitHub release](https://img.shields.io/github/release/stm32duino/LwIP.svg)](https://github.com/stm32duino/LwIP/releases/latest)
10. [`STM32AsyncTCP library v1.0.1+`](https://github.com/khoih-prog/STM32AsyncTCP) for built-in Ethernet on (Nucleo-144, Discovery). To install manually for Arduino IDE.
11. [`ESPAsync_WiFiManager library v1.9.4+`](https://github.com/khoih-prog/ESPAsync_WiFiManager) for ESP32/ESP8266 using some examples. [![GitHub release](https://img.shields.io/github/release/khoih-prog/ESPAsync_WiFiManager.svg)](https://github.com/khoih-prog/ESPAsync_WiFiManager/releases)
12.  [`LittleFS_esp32 v1.0.6+`](https://github.com/lorol/LITTLEFS) for ESP32-based boards using LittleFS. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/LittleFS_esp32.svg?)](https://www.ardu-badge.com/LittleFS_esp32).
13. [`WebServer_WT32_ETH01 library v1.3.0+`](https://github.com/khoih-prog/WebServer_WT32_ETH01) if necessary to use WT32_ETH01 boards. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/WebServer_WT32_ETH01.svg?)](https://www.ardu-badge.com/WebServer_WT32_ETH01)

---

## Installation

### Use Arduino Library Manager
The best and easiest way is to use `Arduino Library Manager`. Search for `AsyncHTTPRequest_Generic`, then select / install the latest version. You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/AsyncHTTPRequest_Generic.svg?)](https://www.ardu-badge.com/AsyncHTTPRequest_Generic) for more detailed instructions.

### Manual Install

1. Navigate to [AsyncHTTPRequest_Generic](https://github.com/khoih-prog/AsyncHTTPRequest_Generic) page.
2. Download the latest release `AsyncHTTPRequest_Generic-master.zip`.
3. Extract the zip file to `AsyncHTTPRequest_Generic-master` directory 
4. Copy the whole `AsyncHTTPRequest_Generic-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**AsyncHTTPRequest_Generic** library](https://platformio.org/lib/show/11235/AsyncHTTPRequest_Generic) by using [Library Manager](https://platformio.org/lib/show/11235/AsyncHTTPRequest_Generic/installation). Search for AsyncHTTPRequest_Generic in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For STM32 boards to use LAN8720

To use LAN8720 on some STM32 boards 

- **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
- **Discovery (DISCO_F746NG)**
- **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**

you have to copy the files [stm32f4xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.1.0/system/STM32F4xx) and [stm32f7xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.1.0/system/STM32F7xx) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.1.0/system) to overwrite the old files.

Supposing the STM32 stm32 core version is 2.1.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.1.0/system/STM32F4xx/stm32f4xx_hal_conf_default.h` for STM32F4.
- `~/.arduino15/packages/STM32/hardware/stm32/2.1.0/system/STM32F7xx/stm32f7xx_hal_conf_default.h` for Nucleo-144 STM32F7.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F4xx/stm32f4xx_hal_conf_default.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F7xx/stm32f7xx_hal_conf_default.h


#### 2. For STM32 boards to use Serial1

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/2.1.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.1.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 2.1.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.1.0/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/2.1.0/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h`

---
---


### Note for Platform IO using ESP32 LittleFS

In Platform IO, to fix the error when using [`LittleFS_esp32 v1.0`](https://github.com/lorol/LITTLEFS) for ESP32-based boards with ESP32 core v1.0.4- (ESP-IDF v3.2-), uncomment the following line

from

```
//#define CONFIG_LITTLEFS_FOR_IDF_3_2   /* For old IDF - like in release 1.0.4 */
```

to

```
#define CONFIG_LITTLEFS_FOR_IDF_3_2   /* For old IDF - like in release 1.0.4 */
```

It's advisable to use the latest [`LittleFS_esp32 v1.0.5+`](https://github.com/lorol/LITTLEFS) to avoid the issue.

Thanks to [Roshan](https://github.com/solroshan) to report the issue in [Error esp_littlefs.c 'utime_p'](https://github.com/khoih-prog/ESPAsync_WiFiManager/issues/28) 

---
---

### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using xyz-Impl.h instead of standard xyz.cpp, possibly creates certain `Multiple Definitions` Linker error in certain use cases. Although it's simple to just modify several lines of code, either in the library or in the application, the library is adding a separate source directory, named src_cpp, besides the standard src directory.

To use the old standard cpp way, just 

1. **Rename the h-only src directory into src_h.**
2. **Then rename the cpp src_cpp directory into src.**
3. Close then reopen the application code in Arduino IDE, etc. to recompile from scratch.

---
---

### Note for Platform IO using ESP32 LittleFS

In Platform IO, to fix the error when using [`LittleFS_esp32 v1.0`](https://github.com/lorol/LITTLEFS) for ESP32-based boards with ESP32 core v1.0.4- (ESP-IDF v3.2-), uncomment the following line

from

```
//#define CONFIG_LITTLEFS_FOR_IDF_3_2   /* For old IDF - like in release 1.0.4 */
```

to

```
#define CONFIG_LITTLEFS_FOR_IDF_3_2   /* For old IDF - like in release 1.0.4 */
```

It's advisable to use the latest [`LittleFS_esp32 v1.0.5+`](https://github.com/lorol/LITTLEFS) to avoid the issue.

Thanks to [Roshan](https://github.com/solroshan) to report the issue in [Error esp_littlefs.c 'utime_p'](https://github.com/khoih-prog/ESPAsync_WiFiManager/issues/28) 

---
---

### HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)

Please have a look at [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to have more detailed description and solution of the issue.

#### 1.  ESP32 has 2 ADCs, named ADC1 and ADC2

#### 2. ESP32 ADCs functions

- ADC1 controls ADC function for pins **GPIO32-GPIO39**
- ADC2 controls ADC function for pins **GPIO0, 2, 4, 12-15, 25-27**

#### 3.. ESP32 WiFi uses ADC2 for WiFi functions

Look in file [**adc_common.c**](https://github.com/espressif/esp-idf/blob/master/components/driver/adc_common.c#L61)

> In ADC2, there're two locks used for different cases:
> 1. lock shared with app and Wi-Fi:
>    ESP32:
>         When Wi-Fi using the ADC2, we assume it will never stop, so app checks the lock and returns immediately if failed.
>    ESP32S2:
>         The controller's control over the ADC is determined by the arbiter. There is no need to control by lock.
> 
> 2. lock shared between tasks:
>    when several tasks sharing the ADC2, we want to guarantee
>    all the requests will be handled.
>    Since conversions are short (about 31us), app returns the lock very soon,
>    we use a spinlock to stand there waiting to do conversions one by one.
> 
> adc2_spinlock should be acquired first, then adc2_wifi_lock or rtc_spinlock.


- In order to use ADC2 for other functions, we have to **acquire complicated firmware locks and very difficult to do**
- So, it's not advisable to use ADC2 with WiFi/BlueTooth (BT/BLE).
- Use ADC1, and pins GPIO32-GPIO39
- If somehow it's a must to use those pins serviced by ADC2 (**GPIO0, 2, 4, 12, 13, 14, 15, 25, 26 and 27**), use the **fix mentioned at the end** of [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to work with ESP32 WiFi/BlueTooth (BT/BLE).

---
---

### HOWTO use STM32F4 with LAN8720

#### 1. Wiring

This is the Wiring for STM32F4 (BLACK_F407VE, etc.) using LAN8720


|LAN8720 PHY|<--->|STM32F4|
|:-:|:-:|:-:|
|TX1|<--->|PB_13|
|TX_EN|<--->|PB_11|
|TX0|<--->|PB_12|
|RX0|<--->|PC_4|
|RX1|<--->|PC_5|
|nINT/RETCLK|<--->|PA_1|
|CRS|<--->|PA_7|
|MDIO|<--->|PA_2|
|MDC|<--->|PC_1|
|GND|<--->|GND|
|VCC|<--->|+3.3V|

---

#### 2. HOWTO program using STLink V-2 or V-3

Connect as follows. To program, use **STM32CubeProgrammer** or Arduino IDE with 

- **U(S)ART Support: "Enabled (generic Serial)"**
- **Upload Method : "STM32CubeProgrammer (SWD)"**


|STLink|<--->|STM32F4|
|:-:|:-:|:-:|
|SWCLK|<--->|SWCLK|
|SWDIO|<--->|SWDIO|
|RST|<--->|NRST|
|GND|<--->|GND|
|5v|<--->|5V|


<p align="center">
    <img src="https://github.com/khoih-prog/AsyncHTTPRequest_Generic/blob/master/Images/STM32F407VET6.png">
</p>

---

#### 3. HOWTO use Serial Port for Debugging

Connect FDTI (USB to Serial) as follows:

|FDTI|<--->|STM32F4|
|:-:|:-:|:-:|
|RX|<--->|TX=PA_9|
|TX|<--->|RX=PA_10|
|GND|<--->|GND|


---
---

### Examples

#### For ESP32 and ESP8266

 1. [AsyncHTTPRequest_ESP](examples/AsyncHTTPRequest_ESP)
 2. [AsyncHTTPRequest_ESP_WiFiManager](examples/AsyncHTTPRequest_ESP_WiFiManager)
 3. [AsyncHTTPMultiRequests_ESP](examples/AsyncHTTPMultiRequests_ESP)

#### For STM32 using LAN8742A

 1. [AsyncHTTPRequest_STM32](examples/AsyncHTTPRequest_STM32)
 2. [AsyncCustomHeader_STM32](examples/AsyncCustomHeader_STM32)
 3. [AsyncDweetGet_STM32](examples/AsyncDweetGet_STM32)
 4. [AsyncDweetPost_STM32](examples/AsyncDweetPost_STM32)
 5. [AsyncSimpleGET_STM32](examples/AsyncSimpleGET_STM32)
 6. [AsyncWebClientRepeating_STM32](examples/AsyncWebClientRepeating_STM32)

#### For STM32 using LAN8720

 1. [AsyncHTTPRequest_STM32_LAN8720](examples/STM32_LAN8720/AsyncHTTPRequest_STM32_LAN8720)
 2. [AsyncCustomHeader_STM32_LAN8720](examples/STM32_LAN8720/AsyncCustomHeader_STM32_LAN8720)
 3. [AsyncDweetGet_STM32_LAN8720](examples/STM32_LAN8720/AsyncDweetGet_STM32_LAN8720)
 4. [AsyncDweetPost_STM32_LAN8720](examples/STM32_LAN8720/AsyncDweetPost_STM32_LAN8720)
 5. [AsyncSimpleGET_STM32_LAN8720](examples/STM32_LAN8720/AsyncSimpleGET_STM32_LAN8720)
 6. [AsyncWebClientRepeating_STM32_LAN8720](examples/STM32_LAN8720/AsyncWebClientRepeating_STM32_LAN8720)

#### For WT32_ETH01

 1. [AsyncHTTPRequest_WT32_ETH01](examples/WT32_ETH01/AsyncHTTPRequest_WT32_ETH01)
 2. [AsyncHTTPMultiRequests_WT32_ETH01](examples/WT32_ETH01/AsyncHTTPMultiRequests_ESP)
 
---

### Example [AsyncHTTPRequest_STM32](examples/AsyncHTTPRequest_STM32)

Please take a look at other examples, as well.

#### 1. File [AsyncHTTPRequest_STM32.ino](examples/AsyncHTTPRequest_STM32/AsyncHTTPRequest_STM32.ino)

```cpp
#include "defines.h"

// 600s = 10 minutes to not flooding, 60s in testing
#define HTTP_REQUEST_INTERVAL_MS     60000  //600000

#include <AsyncHTTPRequest_Generic.h>        // https://github.com/khoih-prog/AsyncHTTPRequest_Generic

#include <Ticker.h>                   // https://github.com/sstaub/Ticker

AsyncHTTPRequest request;

void sendRequest(void);

// Repeat forever, millis() resolution
Ticker sendHTTPRequest(sendRequest, HTTP_REQUEST_INTERVAL_MS, 0, MILLIS); 

void sendRequest(void)
{
  static bool requestOpenResult;
  
  if (request.readyState() == readyStateUnsent || request.readyState() == readyStateDone)
  {
    //requestOpenResult = request.open("GET", "http://worldtimeapi.org/api/timezone/Europe/London.txt");
    requestOpenResult = request.open("GET", "http://worldtimeapi.org/api/timezone/America/Toronto.txt");
    
    if (requestOpenResult)
    {
      // Only send() if open() returns true, or crash
      request.send();
    }
    else
    {
      Serial.println("Can't send bad request");
    }
  }
  else
  {
    Serial.println("Can't send request");
  }
}

void requestCB(void* optParm, AsyncHTTPRequest* request, int readyState) 
{
  (void) optParm;
  
  if (readyState == readyStateDone) 
  {
    Serial.println("\n**************************************");
    Serial.println(request->responseText());
    Serial.println("**************************************");
    
    request->setDebug(false);
  }
}

void setup(void) 
{
  Serial.begin(115200);
  while (!Serial);
  
  Serial.println("\nStart AsyncHTTPRequest_STM32 on " + String(BOARD_NAME));
  Serial.println(ASYNC_HTTP_REQUEST_GENERIC_VERSION);

  // start the ethernet connection and the server
  // Use random mac
  uint16_t index = millis() % NUMBER_OF_MAC;

  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  // Use DHCP dynamic IP and random mac
  Ethernet.begin(mac[index]);

  Serial.print(F("AsyncHTTPRequest @ IP : "));
  Serial.println(Ethernet.localIP());
  Serial.println();

  request.setDebug(false);
  
  request.onReadyStateChange(requestCB);
  sendHTTPRequest.start(); //start the ticker.

  // Send first request now
  //delay(60);
  sendRequest();
}

void loop(void) 
{
  sendHTTPRequest.update();
}
```

---

#### 2. File [defines.h](examples/AsyncHTTPRequest_STM32/defines.h)


```cpp
/*
   Currently support
   1) STM32 boards with built-in Ethernet (to use USE_BUILTIN_ETHERNET = true) such as :
      - Nucleo-144 (F429ZI, F767ZI)
      - Discovery (STM32F746G-DISCOVERY)
      - STM32 boards (STM32F/L/H/G/WB/MP1) with 32K+ Flash, with Built-in Ethernet, 
      - See How To Use Built-in Ethernet at (https://github.com/khoih-prog/EthernetWebServer_STM32/issues/1)
   2) STM32F/L/H/G/WB/MP1 boards (with 32+K Flash) running ENC28J60 shields (to use USE_BUILTIN_ETHERNET = false)
   3) STM32F/L/H/G/WB/MP1 boards (with 32+K Flash) running W5x00 shields
*/

#ifndef defines_h
#define defines_h

#if !( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
       defined(STM32L0) || defined(STM32L1) || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
       defined(STM32WB) || defined(STM32MP1) )
  #error This code is designed to run on STM32F/L/H/G/WB/MP1 platform! Please check your Tools->Board setting.
#endif

#define ASYNC_HTTP_DEBUG_PORT           Serial

// Use from 0 to 4. Higher number, more debugging messages and memory usage.
#define _ASYNC_HTTP_LOGLEVEL_           1


#if defined(STM32F0)
  #warning STM32F0 board selected
  #define BOARD_TYPE  "STM32F0"
#elif defined(STM32F1)
  #warning STM32F1 board selected
  #define BOARD_TYPE  "STM32F1"
#elif defined(STM32F2)
  #warning STM32F2 board selected
  #define BOARD_TYPE  "STM32F2"
#elif defined(STM32F3)
  #warning STM32F3 board selected
  #define BOARD_TYPE  "STM32F3"
#elif defined(STM32F4)
  #warning STM32F4 board selected
  #define BOARD_TYPE  "STM32F4"
#elif defined(STM32F7)
  #warning STM32F7 board selected
  #define BOARD_TYPE  "STM32F7"
#elif defined(STM32L0)
  #warning STM32L0 board selected
  #define BOARD_TYPE  "STM32L0"
#elif defined(STM32L1)
  #warning STM32L1 board selected
  #define BOARD_TYPE  "STM32L1"
#elif defined(STM32L4)
  #warning STM32L4 board selected
  #define BOARD_TYPE  "STM32L4"
#elif defined(STM32H7)
  #warning STM32H7 board selected
  #define BOARD_TYPE  "STM32H7"
#elif defined(STM32G0)
  #warning STM32G0 board selected
  #define BOARD_TYPE  "STM32G0"
#elif defined(STM32G4)
  #warning STM32G4 board selected
  #define BOARD_TYPE  "STM32G4"
#elif defined(STM32WB)
  #warning STM32WB board selected
  #define BOARD_TYPE  "STM32WB"
#elif defined(STM32MP1)
  #warning STM32MP1 board selected
  #define BOARD_TYPE  "STM32MP1"
#else
  #warning STM32 unknown board selected
  #define BOARD_TYPE  "STM32 Unknown"
#endif

#ifndef BOARD_NAME
  #define BOARD_NAME    BOARD_TYPE
#endif

#include <LwIP.h>
#include <STM32Ethernet.h>

//#include <AsyncUDP_STM32.h>

// Enter a MAC address and IP address for your controller below.
#define NUMBER_OF_MAC      20

byte mac[][NUMBER_OF_MAC] =
{
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x01 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x02 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x03 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x04 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x05 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x06 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x07 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x08 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x09 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0A },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0B },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0C },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0D },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0E },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0F },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x10 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x11 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x12 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x13 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x14 },
};

// Select the static IP address according to your local network
IPAddress ip(192, 168, 2, 232);

#endif    //defines_h
```

---
---

### Debug Terminal Ouput Samples

#### 1. [AsyncHTTPRequest_STM32](examples/AsyncHTTPRequest_STM32) running on STM32F7 Nucleo-144 NUCLEO_F767ZI using built-in LAN8742A 

```
Start AsyncHTTPRequest_STM32 on NUCLEO_F767ZI
AsyncHTTPRequest_Generic v1.4.0
AsyncHTTPRequest @ IP : 192.168.2.72

**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2020-09-13T18:22:59.555816-04:00
day_of_week: 0
day_of_year: 257
dst: true
dst_from: 2020-03-08T07:00:00+00:00
dst_offset: 3600
dst_until: 2020-11-01T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1600035779
utc_datetime: 2020-09-13T22:22:59.555816+00:00
utc_offset: -04:00
week_number: 37

**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2020-09-13T18:27:57.586325-04:00
day_of_week: 0
day_of_year: 257
dst: true
dst_from: 2020-03-08T07:00:00+00:00
dst_offset: 3600
dst_until: 2020-11-01T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1600036077
utc_datetime: 2020-09-13T22:27:57.586325+00:00
utc_offset: -04:00
week_number: 37
**************************************
```

---

#### 2. [AsyncHTTPRequest_ESP_WiFiManager](examples/AsyncHTTPRequest_ESP_WiFiManager) running on ESP8266_NODEMCU

```
Starting AsyncHTTPRequest_ESP_WiFiManager using LittleFS on ESP8266_NODEMCU
AsyncHTTPRequest_Generic v1.4.0
Stored: SSID = HueNet1, Pass = 12345678
Got stored Credentials. Timeout 120s
ConnectMultiWiFi in setup
After waiting 3.43 secs more in setup(), connection result is connected. Local IP: 192.168.2.186
H
**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2020-09-13T19:35:37.951609-04:00
day_of_week: 0
day_of_year: 257
dst: true
dst_from: 2020-03-08T07:00:00+00:00
dst_offset: 3600
dst_until: 2020-11-01T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1600040137
utc_datetime: 2020-09-13T23:35:37.951609+00:00
utc_offset: -04:00
week_number: 37
**************************************
HHHHHH

```

---

#### 3. [AsyncHTTPRequest_ESP_WiFiManager](examples/AsyncHTTPRequest_ESP_WiFiManager) running on ESP32_DEV

```
Starting AsyncHTTPRequest_ESP_WiFiManager using SPIFFS on ESP32_DEV
AsyncHTTPRequest_Generic v1.4.0
Stored: SSID = HueNet1, Pass = 12345678
Got stored Credentials. Timeout 120s
ConnectMultiWiFi in setup
After waiting 2.35 secs more in setup(), connection result is connected. Local IP: 192.168.2.232
H
**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2020-09-13T19:37:02.118166-04:00
day_of_week: 0
day_of_year: 257
dst: true
dst_from: 2020-03-08T07:00:00+00:00
dst_offset: 3600
dst_until: 2020-11-01T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1600040222
utc_datetime: 2020-09-13T23:37:02.118166+00:00
utc_offset: -04:00
week_number: 37
**************************************
HHHHHHHHH HHHHHHHHHH HHHHHHHHHH H
**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2020-09-13T19:42:01.507586-04:00
day_of_week: 0
day_of_year: 257
dst: true
dst_from: 2020-03-08T07:00:00+00:00
dst_offset: 3600
dst_until: 2020-11-01T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1600040521
utc_datetime: 2020-09-13T23:42:01.507586+00:00
utc_offset: -04:00
week_number: 37
**************************************
HHHHHHHHH HHHHHHHHHH HHHHHHHHHH 

```

---

#### 4. [AsyncHTTPRequest_ESP](examples/AsyncHTTPRequest_ESP) running on ESP8266_NODEMCU

```
Starting AsyncHTTPRequest_ESP using ESP8266_NODEMCU
AsyncHTTPRequest_Generic v1.4.0
Connecting to WiFi SSID: HueNet1
...........
HTTP WebServer is @ IP : 192.168.2.81

**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2020-09-13T19:56:28.295033-04:00
day_of_week: 0
day_of_year: 257
dst: true
dst_from: 2020-03-08T07:00:00+00:00
dst_offset: 3600
dst_until: 2020-11-01T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1600041388
utc_datetime: 2020-09-13T23:56:28.295033+00:00
utc_offset: -04:00
week_number: 37
**************************************
HHHHHHHHH HHHHHHHHHH HHHHHHHHHH H
```

---

#### 5. [AsyncWebClientRepeating_STM32](examples/AsyncWebClientRepeating_STM32) running on STM32F7 Nucleo-144 NUCLEO_F767ZI using built-in LAN8742A


```
Start AsyncWebClientRepeating_STM32 on NUCLEO_F767ZI
AsyncHTTPRequest_Generic v1.4.0
AsyncHTTPRequest @ IP : 192.168.2.72

**************************************

           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;;


```

---

#### 6. [AsyncWebClientRepeating_STM32_LAN8720](examples/STM32_LAN8720/AsyncWebClientRepeating_STM32_LAN8720) running on STM32F4 BLACK_F407VE using LAN8720


```
Start AsyncWebClientRepeating_STM32_LAN8720 on BLACK_F407VE
AsyncHTTPRequest_Generic v1.4.0
AsyncHTTPRequest @ IP : 192.168.2.150


**************************************

           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;;   

**************************************
```

---

#### 7. [AsyncHTTPMultiRequests_WT32_ETH01](examples/WT32_ETH01/AsyncHTTPMultiRequests_WT32_ETH01) on ESP32_DEV with ETH_PHY_LAN8720

```
Starting AsyncHTTPRequest_WT32_ETH01 on ESP32_DEV with ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.3.0
AsyncHTTPRequest_Generic v1.4.0
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.232, FULL_DUPLEX, 100Mbps
AsyncHTTPRequest @ IP : 192.168.2.232


***************Current***************
{"lat":-24.32,"lon":-46.9983,"timezone":"America/Sao_Paulo","timezone_offset":-10800,"current":{"dt":1625887856,"sunrise":1625910700,"sunset":1625949281,"temp":290.45,"feels_like":290.51,"pressure":1022,"humidity":87,"dew_point":288.27,"uvi":0,"clouds":97,"visibility":10000,"wind_speed":1.3,"wind_deg":3,"wind_gust":1.77,"weather":[{"id":804,"main":"Clouds","description":"overcast clouds","icon":"04n"}]}}
**************************************
HHHHHH
***************Minutely***************
{"lat":-24.32,"lon":-46.9983,"timezone":"America/Sao_Paulo","timezone_offset":-10800,"minutely":[{"dt":1625887920,"precipitation":0},{"dt":1625887980,"precipitation":0},{"dt":1625888040,"precipitation":0},{"dt":1625888100,"precipitation":0},{"dt":1625888160,"precipitation":0},{"dt":1625888220,"precipitation":0},{"dt":1625888280,"precipitation":0},{"dt":1625888340,"precipitation":0},{"dt":1625888400,"precipitation":0},{"dt":1625888460,"precipitation":0},{"dt":1625888520,"precipitation":0},{"dt":1625888580,"precipitation":0},{"dt":1625888640,"precipitation":0},{"dt":1625888700,"precipitation":0},{"dt":1625888760,"precipitation":0},{"dt":1625888820,"precipitation":0},{"dt":1625888880,"precipitation":0},{"dt":1625888940,"precipitation":0},{"dt":1625889000,"precipitation":0},{"dt":1625889060,"precipitation":0},{"dt":1625889120,"precipitation":0},{"dt":1625889180,"precipitation":0},{"dt":1625889240,"precipitation":0},{"dt":1625889300,"precipitation":0},{"dt":1625889360,"precipitation":0},{"dt":1625889420,"precipitation":0},{"dt":1625889480,"precipitation":0},{"dt":1625889540,"precipitation":0},{"dt":1625889600,"precipitation":0},{"dt":1625889660,"precipitation":0},{"dt":1625889720,"precipitation":0},{"dt":1625889780,"precipitation":0},{"dt":1625889840,"precipitation":0},{"dt":1625889900,"precipitation":0},{"dt":1625889960,"precipitation":0},{"dt":1625890020,"precipitation":0},{"dt":1625890080,"precipitation":0},{"dt":1625890140,"precipitation":0},{"dt":1625890200,"precipitation":0},{"dt":1625890260,"precipitation":0},{"dt":1625890320,"precipitation":0},{"dt":1625890380,"precipitation":0},{"dt":1625890440,"precipitation":0},{"dt":1625890500,"precipitation":0},{"dt":1625890560,"precipitation":0},{"dt":1625890620,"precipitation":0},{"dt":1625890680,"precipitation":0},{"dt":1625890740,"precipitation":0},{"dt":1625890800,"precipitation":0},{"dt":1625890860,"precipitation":0},{"dt":1625890920,"precipitation":0},{"dt":1625890980,"precipitation":0},{"dt":1625891040,"precipitation":0},{"dt":1625891100,"precipitation":0},{"dt":1625891160,"precipitation":0},{"dt":1625891220,"precipitation":0},{"dt":1625891280,"precipitation":0},{"dt":1625891340,"precipitation":0},{"dt":1625891400,"precipitation":0},{"dt":1625891460,"precipitation":0},{"dt":1625891520,"precipitation":0}]}
**************************************
HHHH HH
***************Daily***************
{"lat":-24.32,"lon":-46.9983,"timezone":"America/Sao_Paulo","timezone_offset":-10800,"daily":[{"dt":1625929200,"sunrise":1625910700,"sunset":1625949281,"moonrise":1625912640,"moonset":1625951340,"moon_phase":0.02,"temp":{"day":295.51,"min":288.03,"max":295.54,"night":289.23,"eve":290.52,"morn":288.14},"feels_like":{"day":295.42,"night":289.24,"eve":290.69,"morn":288.1},"pressure":1021,"humidity":62,"dew_point":287.26,"wind_speed":2.25,"wind_deg":151,"wind_gust":2.36,"weather":[{"id":800,"main":"Clear","description":"clear sky","icon":"01d"}],"clouds":0,"pop":0.01,"uvi":4.97},{"dt":1626015600,"sunrise":1625997092,"sunset":1626035705,"moonrise":1626001860,"moonset":1626041220,"moon_phase":0.05,"temp":{"day":295.33,"min":288.28,"max":295.45,"night":290.23,"eve":290.91,"morn":288.28},"feels_like":{"day":295.27,"night":290.5,"eve":291.22,"morn":288.07},"pressure":1021,"humidity":64,"dew_point":287.51,"wind_speed":2.46,"wind_deg":173,"wind_gust":2.85,"weather":[{"id":800,"main":"Clear","description":"clear sky","icon":"01d"}],"clouds":0,"pop":0,"uvi":5.01},{"dt":1626102000,"sunrise":1626083482,"sunset":1626122130,"moonrise":1626090900,"moonset":1626131100,"moon_phase":0.08,"temp":{"day":295.54,"min":289.16,"max":295.58,"night":290.41,"eve":291.33,"morn":289.32},"feels_like":{"day":295.61,"night":290.7,"eve":291.66,"morn":289.45},"pressure":1022,"humidity":68,"dew_point":288.68,"wind_speed":2.3,"wind_deg":115,"wind_gust":2.47,"weather":[{"id":800,"main":"Clear","description":"clear sky","icon":"01d"}],"clouds":0,"pop":0.01,"uvi":5.02},{"dt":1626188400,"sunrise":1626169871,"sunset":1626208556,"moonrise":1626179700,"moonset":1626220980,"moon_phase":0.12,"temp":{"day":297.47,"min":288.79,"max":297.47,"night":291.03,"eve":291.51,"morn":288.79},"feels_like":{"day":297.42,"night":291.09,"eve":291.75,"morn":288.73},"pressure":1020,"humidity":56,"dew_point":287.21,"wind_speed":2.26,"wind_deg":6,"wind_gust":2.64,"weather":[{"id":800,"main":"Clear","description":"clear sky","icon":"01d"}],"clouds":7,"pop":0,"uvi":5.16},{"dt":1626274800,"sunrise":1626256259,"sunset":1626294981,"moonrise":1626268380,"moonset":1626310860,"moon_phase":0.15,"temp":{"day":300.56,"min":291.14,"max":300.56,"night":292.56,"eve":293.32,"morn":291.14},"feels_like":{"day":300.44,"night":292.31,"eve":293.3,"morn":290.64},"pressure":1017,"humidity":42,"dew_point":285.41,"wind_speed":2.21,"wind_deg":9,"wind_gust":2.64,"weather":[{"id":804,"main":"Clouds","description":"overcast clouds","icon":"04d"}],"clouds":99,"pop":0,"uvi":1.57},{"dt":1626361200,"sunrise":1626342645,"sunset":1626381407,"moonrise":1626356940,"moonset":1626400740,"moon_phase":0.19,"temp":{"day":303.08,"min":291.35,"max":303.08,"night":294.83,"eve":295.82,"morn":291.35},"feels_like":{"day":302.65,"night":294.54,"eve":295.79,"morn":290.77},"pressure":1012,"humidity":39,"dew_point":286.19,"wind_speed":2.6,"wind_deg":343,"wind_gust":5.27,"weather":[{"id":802,"main":"Clouds","description":"scattered clouds","icon":"03d"}],"clouds":40,"pop":0,"uvi":2},{"dt":1626447600,"sunrise":1626429031,"sunset":1626467833,"moonrise":1626445440,"moonset":1626490680,"moon_phase":0.22,"temp":{"day":292.5,"min":289.95,"max":294.21,"night":289.95,"eve":290.68,"morn":291.26},"feels_like":{"day":292.84,"night":290.14,"eve":290.92,"morn":291.4},"pressure":1021,"humidity":90,"dew_point":290.28,"wind_speed":4.17,"wind_deg":265,"wind_gust":7.18,"weather":[{"id":500,"main":"Rain","description":"light rain","icon":"10d"}],"clouds":100,"pop":0.76,"rain":4.13,"uvi":2},{"dt":1626534000,"sunrise":1626515415,"sunset":1626554260,"moonrise":1626534060,"moonset":0,"moon_phase":0.25,"temp":{"day":288.1,"min":287.9,"max":289.38,"night":288.96,"eve":288.71,"morn":288.22},"feels_like":{"day":288.16,"night":289.05,"eve":288.78,"morn":288.24},"pressure":1025,"humidity":96,"dew_point":287.06,"wind_speed":3.79,"wind_deg":144,"wind_gust":6.59,"weather":[{"id":501,"main":"Rain","description":"moderate rain","icon":"10d"}],"clouds":100,"pop":1,"rain":32.28,"uvi":2}]}
**************************************
H
```

---

#### 8. [AsyncHTTPRequest_WT32_ETH01](examples/WT32_ETH01/AsyncHTTPRequest_WT32_ETH01) on ESP32_DEV with ETH_PHY_LAN8720

```
Starting AsyncHTTPRequest_WT32_ETH01 on ESP32_DEV with ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.3.0
AsyncHTTPRequest_Generic v1.4.0
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.232, FULL_DUPLEX, 100Mbps
AsyncHTTPRequest @ IP : 192.168.2.232

**************************************
abbreviation: EDT
client_ip: 45.72.193.56
datetime: 2021-07-09T23:16:50.506413-04:00
day_of_week: 5
day_of_year: 190
dst: true
dst_from: 2021-03-14T07:00:00+00:00
dst_offset: 3600
dst_until: 2021-11-07T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1625887010
utc_datetime: 2021-07-10T03:16:50.506413+00:00
utc_offset: -04:00
week_number: 27
**************************************
```


---
---

### Debug

Debug is enabled by default on Serial.

You can also change the debugging level from 0 to 4

```cpp
#define ASYNC_HTTP_DEBUG_PORT           Serial

// Use from 0 to 4. Higher number, more debugging messages and memory usage.
#define _ASYNC_HTTP_LOGLEVEL_           1
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the `ESP32 / ESP8266 / STM32` core for Arduino.

Sometimes, the library will only work if you update the `ESP32 / ESP8266 / STM32` core to the latest version because I am using newly added functions.

---

### Issues ###

Submit issues to: [AsyncHTTPRequest_Generic issues](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues)

---

## TO DO

 1. Fix bug. Add enhancement
 2. Add support to more Ethernet / WiFi shields
 3. Add support to more boards.
 4. Add many more examples.


## DONE

 1. Initially add support to STM32 using built-in LAN8742A Etnernet. Tested on **STM32F7 Nucleo-144 F767ZI**.
 2. Add more examples.
 3. Add debugging features.
 4. Add PUT, PATCH, DELETE and HEAD besides GET and POST.
 5. Add support to **Ethernet LAN8720** using [STM32Ethernet library](https://github.com/stm32duino/STM32Ethernet), for boards such as **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG), Discovery (DISCO_F746NG)** and **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**
 6. Add support to **WT32_ETH01** using ESP32-based boards and LAN8720 Ethernet

---
---

### Contributions and Thanks

This library is based on, modified, bug-fixed and improved from:

1. [Bob Lemaire's **asyncHTTPrequest Library**](https://github.com/boblemaire/asyncHTTPrequest) to use the better **asynchronous** features of these following Async TCP Libraries : ( [`ESPAsyncTCP`](https://github.com/me-no-dev/ESPAsyncTCP), [`AsyncTCP`](https://github.com/me-no-dev/AsyncTCP), and [`STM32AsyncTCP`](https://github.com/philbowles/STM32AsyncTCP) ).

2. Thanks to [Daniel Brunner](https://github.com/0xFEEDC0DE64) to report and make PR in [Fixed linker errors when included in multiple .cpp files](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/pull/1) leading to v1.0.1. See [**HOWTO Fix `Multiple Definitions` Linker Error**](https://github.com/khoih-prog/AsyncHTTPRequest_Generic#HOWTO-Fix-Multiple-Definitions-Linker-Error)

3. Thanks to [gleniat](https://github.com/gleniat) to make enhancement request in [Add support for sending PUT, PATCH, DELETE request](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/5) leading to v1.1.0.

4. Thanks to [BadDwarf](https://github.com/baddwarf) to report [**compatibility with ESPAsyncWebServer #11**](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/11) leading to the enhancement in v1.1.2.

5. Thanks to [spdi](https://github.com/spdi) to report [**'Connection' header expects 'disconnect' instead 'close' ? #13**](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/13) leading to new release v1.1.3 to fix bug.

6. Thanks to [andrewk123](https://github.com/andrewk123) to report [**Http GET polling causes crash when host disconnected #22**](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/22) leading to new release v1.4.0 to fix bug.


<table>
  <tr>
    <td align="center"><a href="https://github.com/boblemaire"><img src="https://github.com/boblemaire.png" width="100px;" alt="boblemaire"/><br /><sub><b>⭐️ Bob Lemaire</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/0xFEEDC0DE64"><img src="https://github.com/0xFEEDC0DE64.png" width="100px;" alt="0xFEEDC0DE64"/><br /><sub><b>Daniel Brunner</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/gleniat"><img src="https://github.com/gleniat.png" width="100px;" alt="gleniat"/><br /><sub><b>gleniat</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/baddwarf"><img src="https://github.com/baddwarf.png" width="100px;" alt="baddwarf"/><br /><sub><b>BadDwarf</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/spdi"><img src="https://github.com/spdi.png" width="100px;" alt="spdi"/><br /><sub><b>spdi</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/andrewk123"><img src="https://github.com/andrewk123.png" width="100px;" alt="andrewk123"/><br /><sub><b>andrewk123</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License and credits ###

- The library is licensed under [GPLv3](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/blob/master/LICENSE)

---

## Copyright

Copyright (C) <2018>  <Bob Lemaire, IoTaWatt, Inc.>

Copyright 2020- Khoi Hoang



