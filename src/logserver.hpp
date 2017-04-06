#ifndef SERV_H
#define SERV_H
#include <string>
#include "buffer.hpp"
#include "logmsg.hpp"
/**
 * @brief Klasa serwera logującego
 *
 * Klasa obsługująca serwer logujący przychodzące wiadomości.
 */
class logServer {
    private:
        int port = 10000;
		int remotefd;
        std::string path;
		std::string remoteAddr;
		bool listening = true;
        buffer<logMsg> buf;
        std::vector<pid_t> listeners;
        void _saveMsg(logMsg ms);
    public:
        void setRemotePort(int p);
		void setRemoteAddress(std::string ip);
        int startRemoteListener();
        void stopRemoteListener();
        void setLogPath(std::string path);

};
#endif
