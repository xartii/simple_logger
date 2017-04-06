#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include "buffer.hpp"
/**
 * @brief Klasa klienta logującego
 *
 * Klasa obsługująca łączenie z serwerem logów, a także wysyłanie wiadomości do
 * niego
 */
class log {
    private:
        bool buffering = false;
        std::string filename;
        int sockfd;
        bool connected = false;
        std::string hostname;
        buffer<logMsg> buf;
        int _sendMsg(logMsg ms);
    public:
        void enableBuffering(bool state);
        int connectLocal(std::string filename);
        int connectRemote(std::string host, int p);
        bool isConnected();
        void disconnect();
        int addMsg(logMsg ms);
        bool isBuffered();
        int sendMsgs();
};
#endif
