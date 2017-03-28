#include "buffer.hpp"
#include "logmsg.hpp"
#include <iostream>

int main(int argc, char **argv) {
    buffer<logMsg> buf;
    logMsg msg;

    if(buf.isEmpty())
        std::cout << "Bufor jest pusty" << std::endl;

    msg.setPrefix("test");
    msg.setPriority(error);
    msg.setMsg("testowy log");
    msg.calcChecksum();
    std::cout << msg.printLog() << std::endl;
    buf.addElem(msg);

    if(!buf.isEmpty())
        std::cout << "Bufor nie jest pusty" << std::endl;

    logMsg tmp;

    tmp = buf.getFirst();

    if(buf.isEmpty())
        std::cout << "Bufor jest pusty" << std::endl;

    std::cout << tmp.printLog() << std::endl;

    return 0;
}
