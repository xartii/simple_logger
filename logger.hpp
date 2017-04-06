#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include "buffer.hpp"

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
