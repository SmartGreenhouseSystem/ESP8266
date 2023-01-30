# Smart Green House System Client

A client for the Smart Green House System Rails server

## Information

This is made for the WeMos copy of the ESP8266 chip which acts as a NodeMCU 1 ESP-12E board.

## Setup

### System requirements

It is required that there is some form of python runtime installed on the running system for configuration explained later in the README.

### IDE

This application is mostly meant for be used with VScode with the [PlatformIO IDE extension](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide). Just installing that extension and opening this project via it should be sufficient.

### Variables

To keep the variables such as the Wifi name and password hidden, environment variables which are put as build flags are used. This is made possible via the `env-extra.py` script which appends the build flags into the `platformio.ini` file at build time. 

To set them up one needs to make the `.env` file in the root of the project.

#### `.env` file example

```
WIFI_SSID="My_wifi_name"
WIFI_PASSWORD="MySooperAweshomeP@ssword"
```