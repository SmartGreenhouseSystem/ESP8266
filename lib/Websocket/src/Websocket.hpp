#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <iostream>
#include <ArduinoWebsockets.h>

class Websocket {
    private:
        std::string socketServerUrl, identifier;
        websockets::WebsocketsClient client;
        /**
         * Event handler for any incoming messages.
         * @param message a struct containing the information about the message.
         * @see websockets::WebsocketsEvent
        */
        void consumeMessage(const websockets::WebsocketsMessage& message);
        /**
         * Event handler for any event types like a disconnect, etc.
         * @param event an Enum for the event type.
         * @see websockets::WebsocketsEvent
        */
        void consumeEvent(const websockets::WebsocketsEvent& event);
    public:
        /**
         * Only initializer for the websocket connection. It only creates the object and does not start the connection.
         * @param serverUrl the absolute URL of the websocket server. It expectes the `ws://` or `wss://` extension on the beginning.
         * @param serverOrigin the information which will be sent with the `Origin` header during the connection.
         * @return the instance of the object
        */
        Websocket(const std::string serverUrl, const std::string serverOrigin);
        /**
         * Connect to the websocket. It does not connect to the channel, just to the server.
         * @return a boolean to determine whether the socket is connected or not.
        */
        bool connect();
        /**
         * Connect to the websocket channel. It is expected that the socket is already connected.
         * @param channelName the name of the channel which the socket should connect to. Example: `MicrocontrollerChannel`.
         * @param id the mcid of the device connecting.
         * @return a boolean to see whether it is connected or not.
        */
        void subscribe(const std::string &channelName, const std::string &id);
        /**
         * Disconnect from the socket connection.
        */
        void disconnect();
        /**
         * Poll the connection.
        */
        void poll();
        /**
         * Send a message to the socket connection. This is a wrapper which sends the message directly but also
         * shows in the serial console what was sent for debugging.
         * @param message the message being sent to the server.
        */
        void send(const std::string &message);
};

#endif