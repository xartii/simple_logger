#include "logmsg.hpp"
#include "buffer.hpp"
#include "logger.hpp"
#include <string>
#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

void log::enableBuffering(bool state) {
    this->buffering = state;
}

bool log::isConnected() {
    return this->connected;
}

bool log::isBuffered() {
    return this->buffering;
}

int log::connectRemote(std::string host, int p) {
    struct addrinfo hints;
    struct addrinfo *servinfo;
    int status;
    std::string port;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    port = std::to_string(p);
    status = getaddrinfo(host.c_str(), port.c_str(), &hints, &servinfo);

    if(status)
        return -1;

    sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

    if(sockfd == -1)
        return -1;

    status = connect(this->sockfd, servinfo->ai_addr, servinfo->ai_addrlen);

    if(status == -1) {
        close(this->sockfd);
        return -1;
    }

    this->connected = true;
    return 0;
}

void log::disconnect() {
    if(this->connected)
        close(this->sockfd);
}

int log::_sendMsg(logMsg ms) {
    std::string m;
    int status;

    m = ms.printLog() + "\n";
    status = send(this->sockfd, m.c_str(), m.length(), 0);

    return status;
}

int log::addMsg(logMsg ms) {
    if(this->buffering) {
        this->buf.addElem(ms);
        return 0;
    } else {
        return this->_sendMsg(ms);
    }
    return -1;
}

int log::sendMsgs() {
    logMsg tmp;
    int status;

    if(!this->buffering) 
        return -1;

    while(!this->buf.isEmpty()) {
        tmp = this->buf.getFirst();
        status = this->_sendMsg(tmp);
        if(status == -1)
            return status;
    }

    return 0;
}
