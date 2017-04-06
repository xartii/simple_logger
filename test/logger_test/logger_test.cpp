#include "logmsg.hpp"
#include "logger.hpp"
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <string>
#include <libconfig.h++>

using namespace libconfig;

int main(int argc, char **argv) {
    log logger;
    Config cfg;
    std::string addr;
    int port;
    int temp;
    std::string msg;

    try {
        cfg.readFile("client.cfg");
    } catch (const FileIOException &ex) {
        std::cout << "Błąd otwarcia pliku konfiguracyjnego\n";
        return -1;
    }
    try {
        cfg.lookupValue("address", addr);
        cfg.lookupValue("port", port);
    } catch(const SettingNotFoundException &ex) {
        std::cout << "Nie udało się odczytać ustawień z pliku konfiguracyjnego\n";
        return -1;
    }


    logger.connectRemote(addr, port);
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
    srand(time(NULL));

    logger.enableBuffering(true);
    for(int i = 0 ; i < 101; i++) {
        ms = logMsg();
        temp = rand()%100+1;
        ms.setPrefix("temp");
        if(temp > 80) {
            ms.setPriority(error);
        } else if (temp > 50) {
            ms.setPriority(warning);
        } else {
            ms.setPriority(info);
        }
        msg = "Pomiar temperatury: " + std::to_string(temp);
        ms.setMsg(msg);
        ms.calcChecksum();
        logger.addMsg(ms);
        sleep(1);
        if(i%10 == 0)
            logger.sendMsgs();
    }
    
    logger.disconnect();

    return 0;

}


