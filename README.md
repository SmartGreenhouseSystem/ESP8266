# Smart Green House System Client

A client for the Smart Green House System Rails server

## Information

This is made for the WeMos copy of the ESP8266 chip which acts as a NodeMCU 1 ESP-12E board.

## Setup

### IDE

This application is mostly meant for be used with VScode with the [PlatformIO IDE extension](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide). Just installing that extension and opening this project via it should be sufficient.

### Variables

To keep the variables such as the Wifi name and password hidden, a hidden `.config.h` file in the root of the project is used to define constant variables.

#### `.config.h` file example

```c
#define WIFI_SSID           "My wifi ssid"
#define WIFI_PASSWORD       "MyWifiP@ssword"
#define SCADA_SERVER        "ws://192.168.1.130:3000/cable"
#define SCADA_SERVER_ORIGIN "http://localhost:3000"
#define CONTROLLER_ID       "main_room"
#define CONTROLLER_NAME     "A non unique display name"
```