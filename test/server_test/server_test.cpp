#include "logserver.hpp"
#include <iostream>
#include <string>
#include <unistd.h>
#include <libconfig.h++>

using namespace libconfig;

int main(int argc, char** argv) {
    logServer serv;
    Config cfg;
    std::string addr;
    int port;
    std::string path;

    try {
        cfg.readFile("server.cfg");
    }catch (const FileIOException &ex) {
        std::cout << "Błąd odczytu pliku konfiguracyjnego\n";
        return -1;
    }

    try {
        cfg.lookupValue("address", addr);
        cfg.lookupValue("port", port);
        cfg.lookupValue("path", path);
    }catch (const SettingNotFoundException &ex) {
        std::cout << "Niepoprawny plik konfiguracyjny\n";
        return -1;
    }

    serv.setLogPath(path);
    serv.setRemoteAddress(addr);
    serv.setRemotePort(port);

    if(serv.startRemoteListener() == 0) {
        std::cout << "Serwer został uruchomiony\n";
    } else {
        std::cout << "Serwer nie został uruchomiony\n";
    }
    sleep(180);
    serv.stopRemoteListener();

    return 0;
}
