#include "Websocket.hpp"
#include <ArduinoWebsockets.h>
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

void Websocket::connect() {
    client.connect(socketServerUrl.c_str());
}

void Websocket::subscribe(const std::string &channelName, const std::string &id) {
    std::string message = "{\"command\":\"subscribe\",\"identifier\":\"{\\\"channel\\\":\\\"" + channelName + "\\\",\\\"mcid\\\":\\\"" + id + "\\\"}\"}";
    client.send(message.c_str());
}

void Websocket::consumeMessage(const websockets::WebsocketsMessage &message) {
    Serial.print("WS: Receive: ");
    Serial.println(message.data());
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