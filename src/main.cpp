#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Websocket.hpp>
#include <SoftwareSerial.h>
#include <iostream>
#include <sstream>
#include "../.config.h"

#define ARDUINO_RX D2
#define ARDUINO_TX D3

Websocket websocket(SCADA_SERVER, SCADA_SERVER_ORIGIN);

SoftwareSerial ArduinoSerial(ARDUINO_RX, ARDUINO_TX);

void setup() {
	pinMode(ARDUINO_RX, INPUT);
	pinMode(ARDUINO_TX, OUTPUT);

	Serial.begin(115200);
	ArduinoSerial.begin(9600);
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
	websocket.subscribe("MicrocontrollerChannel", CONTROLLER_ID, CONTROLLER_NAME);
}

void loop() {
	websocket.poll();

	if(ArduinoSerial.available() > 0) {
		std::string reading = ArduinoSerial.readString().c_str(); 

		std::vector<std::string> strings;
		std::string buffer;
		std::istringstream stream(reading);   

		while (std::getline(stream, buffer, '|')) {
			strings.push_back(buffer);
			Serial.println(buffer.c_str());
		}
		
		// websocket.saveReading(strings[0], std::stof(strings[1].c_str()));
	}
}