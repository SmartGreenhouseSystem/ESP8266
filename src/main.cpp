#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Websocket.hpp>
#include <iostream>
#include "../.config.h"

Websocket websocket(SCADA_SERVER, SCADA_SERVER_ORIGIN);

void setup() {
	Serial.begin(115200);
	delay(100);

	Serial.print("WiFi: Connecting to ");
	Serial.print(WIFI_SSID);

	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
	WiFi.softAPdisconnect(true);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println("");
	Serial.print("WiFi: connected as IPv4: ");
	Serial.println(WiFi.localIP());

	websocket.connect();
	websocket.subscribe("MicrocontrollerChannel", "1");
}

void loop() {
	websocket.poll();
}