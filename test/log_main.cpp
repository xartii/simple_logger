#include "logmsg.hpp"
#include <iostream>

int main (int argc, char** argv) {
    logMsg msg;
    msg.setPrefix("test");
    msg.setPriority(error);
    msg.setMsg("testowy log");
    msg.calcChecksum();
    std::cout << msg.printLog();
    std::cout << std::endl;

    return 0;
}
