#include <Arduino.h>
#include <ESP8266WiFi.h>

#define XSTR(x) #x
#define STR(x) XSTR(x)

void setup()
{
	Serial.begin(115200);
	delay(100);

	Serial.print("Connecting to ");
	Serial.println(STR(WIFI_SSID));

	WiFi.begin(STR(WIFI_SSID), STR(WIFI_PASSWORD));
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