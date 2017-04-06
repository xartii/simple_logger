#include "logserver.hpp"
#include <iostream>
#include <unistd.h>

int main(int argc, char** argv) {
    logServer serv;
    serv.setLogPath("./");
    serv.setRemoteAddress("127.0.0.1");
    serv.setRemotePort(10000);

    if(serv.startRemoteListener() == 0) {
        std::cout << "Serwer został uruchomiony\n";
    } else {
        std::cout << "Serwer nie został uruchomiony\n";
    }
    sleep(30);
    serv.stopRemoteListener();

    return 0;
}
