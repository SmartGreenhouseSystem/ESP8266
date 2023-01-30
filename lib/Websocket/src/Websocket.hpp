#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <iostream>
#include <ArduinoWebsockets.h>

class Websocket {
    private:
        std::string socketServerUrl;
        websockets::WebsocketsClient client;
        void consumeMessage(const websockets::WebsocketsMessage& message);
        void consumeEvent(const websockets::WebsocketsEvent& event);
    public:
        Websocket(const std::string serverUrl, const std::string serverOrigin);
        void connect();
        void subscribe(const std::string &channelName, const std::string &id);
        void disconnect();
        void onDisconnect(void (*callback));
        void poll();
};

#endif