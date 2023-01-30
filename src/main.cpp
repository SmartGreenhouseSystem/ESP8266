#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Environment.h>

const char* ssid = ENV(WIFI_SSID);
const char* password = ENV(WIFI_PASSWORD);

void setup()
{
	Serial.begin(115200);
	delay(100);

	Serial.print("Connecting to ");
	Serial.println(ssid);

	WiFi.begin(ssid, password);
	WiFi.softAPdisconnect(true);

	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}

    Serial.println("");
    Serial.print("WiFi connected at: ");
    Serial.print(WiFi.localIP());

}

void loop() {
  // put your main code here, to run repeatedly:
}