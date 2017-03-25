#include "logmsg.hpp"
#include <iostream>

int main (int argc, char** argv) {
    logMsg msg;
    std::string output;

    msg.setPrefix("test");
    msg.setPriority(error);
    msg.setMsg("testowy log");
    msg.calcChecksum();
    std::cout << "Before creating: " << std::endl;
    output = msg.printLog();
    std::cout << output;
    std::cout << std::endl;

    logMsg ms(output);

    std::cout << "After creating: " << std::endl;
    std::cout << ms.printLog();
    std::cout << std::endl;

    return 0;
}
