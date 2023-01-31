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

void Websocket::subscribe(const std::string &channelName, const std::string &id) {
    std::string message = "{\"command\":\"subscribe\",\"identifier\":\"{\\\"channel\\\":\\\"" + channelName + "\\\",\\\"mcid\\\":\\\"" + id + "\\\"}\"}";
    send(message);
}

void Websocket::consumeMessage(const websockets::WebsocketsMessage &message) {
    Serial.print("WS: Receive raw data: ");
    Serial.println(message.data());

    // The exact value was predetermined via https://arduinojson.org/v6/assistant/
    
    StaticJsonDocument<128> doc;
    DeserializationError error = deserializeJson(doc, message.data());

    if (error) {
        Serial.print(F("WS: JSON deserialization failed: "));
        Serial.println(error.f_str());
        return;
    }

    Serial.print("WS: Receive JSON type: ");

    const char* type = doc["type"];

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
