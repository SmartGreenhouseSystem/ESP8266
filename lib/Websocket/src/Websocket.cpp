#include "Websocket.hpp"
#include <ArduinoWebsockets.h>
#include <ArduinoJson.h>
#include <iostream>

Websocket::Websocket(const std::string serverUrl, const std::string serverOrigin) : socketServerUrl(serverUrl) {
    client.addHeader("Origin", serverOrigin.c_str());

    client.onMessage([this](const websockets::WebsocketsMessage &message) {
        this->consumeMessage(message);
    });

    client.onEvent([this](const websockets::WebsocketsEvent &event, const String &data) {
        this->consumeEvent(event);
    });
};

bool Websocket::connect() {
    return client.connect(socketServerUrl.c_str());
}

void Websocket::disconnect() {
    client.close();
}

void Websocket::send(const std::string &message) {
    Serial.print("WS: Send: ");
    Serial.println(message.c_str());
    client.send(message.c_str());
}

void Websocket::subscribe(const std::string &channelName, const std::string &id, const std::string &name) {
    identifier = "{\\\"channel\\\":\\\"" + channelName + "\\\",\\\"mcid\\\":\\\"" + id + "\\\",\\\"name\\\":\\\"" + name + "\\\"}";
    std::string message = "{\"command\":\"subscribe\",\"identifier\":\"" + identifier + "\"}";
    send(message);
}

void Websocket::saveReading(const std::string &readingName, const float &value) {
    std::string message = 
        "{\"command\": \"message\", \"identifier\": \"" + identifier
        + "\",  \"data\": \"{\\\"action\\\":\\\"save\\\",\\\"name\\\":\\\"" + readingName
        + "\\\",\\\"value\\\":" + std::to_string(value) + ",\\\"recorded_at\\\":"
        + std::to_string(serverTime + (millis() - systemTime) / 1000) + "}\"}";
    send(message);
}

void Websocket::consumeMessage(const websockets::WebsocketsMessage &message) {
    Serial.print("WS: Receive raw data: ");
    Serial.println(message.data());

    // The exact value was predetermined via https://arduinojson.org/v6/assistant/
    
    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, message.data());

    if (error) {
        Serial.print(F("WS: JSON deserialization failed: "));
        Serial.println(error.f_str());
        return;
    }

    Serial.print("WS: Receive JSON type: ");

    const char* type = doc["type"];

    if (strcmp(type, "ping") == 0) {
        serverTime = doc["message"];
        systemTime = millis();
    }

    Serial.println(type);
}

void Websocket::consumeEvent(const websockets::WebsocketsEvent &event) {
    if(event == websockets::WebsocketsEvent::ConnectionOpened) {
        Serial.println("WS: Connnection Opened");
    } else if(event == websockets::WebsocketsEvent::ConnectionClosed) {
        Serial.println("WS: Connnection Closed");
    } else if(event == websockets::WebsocketsEvent::GotPing) {
        Serial.println("WS: Got a Ping!");
    } else if(event == websockets::WebsocketsEvent::GotPong) {
        Serial.println("WS: Got a Pong!");
    } else {
        Serial.println("WS: Something completely else...");
    }
}

void Websocket::poll() {
    client.poll();
}
