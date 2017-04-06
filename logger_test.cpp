#include "logmsg.hpp"
#include "logger.hpp"
#include <ctime>
#include <unistd.h>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
    log logger;

    logger.connectRemote("127.0.0.1", 10000);
    if(logger.isConnected()) {
        std::cout << "Połączono z serwerem\n";
    } else {
        std::cout << "Nie udało się nawiązać połączenia z serwerem.\n";
        return -1;
    }

    logMsg ms;
    ms.setPrefix("test");
    ms.setPriority(error);
    ms.setMsg("Log testowy");
    ms.calcChecksum();

    logger.addMsg(ms);
    logger.enableBuffering(true);
    logger.addMsg(ms);
    logger.addMsg(ms);
    sleep(3);
    logger.sendMsgs();



    logger.disconnect();

    return 0;

}


