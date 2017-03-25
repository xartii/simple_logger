#include "logmsg.hpp" 
#include "functions.hpp"
#include <openssl/sha.h>


/**
 * @brief Klasa wiadomości logowanych
 *
 * Klasa przechowuje pojedyńczą wiadomość, która ma być logowana
 */

void logMsg::setPrefix(std::string p) {
    this->prefix = p;
}

void logMsg::setPriority(enum priority pr) {
    this->priority = pr;
}

void logMsg::setMsg(std::string msg) {
    this->msg = msg;
}

int logMsg::getPriority() {
    return this->priority;
}

std::string logMsg::getPrefix() {
    return this->prefix;
}

std::string logMsg::getMsg() {
    return this->msg;
}

std::string logMsg::printLog() {
    std::string output;
    output.append(std::to_string(this->priority));
    output.append("|");
    output.append(this->prefix);
    output.append("|");
    output.append(this->msg);
    output.append("|");
    output.append(this->checksum);

    return output;
}
void logMsg::calcChecksum() {
    unsigned char temp[SHA_DIGEST_LENGTH];
    std::string ms;

    ms.append(std::to_string(this->priority));
    ms.append("|");
    ms.append(this->prefix);
    ms.append("|");
    ms.append(this->msg);


    SHA1((const unsigned char*)(ms.c_str()), ms.size(), temp);

    char buf[SHA_DIGEST_LENGTH*2];
    for (int i = 0 ; i < SHA_DIGEST_LENGTH; i++) {
        sprintf(&buf[i*2], "%02x", temp[i]);
    }
    this->checksum = buf;
}

logMsg::logMsg(std::string msg) {
    std::vector<std::string> output;

    output = explode(msg, "|");
    this->priority = std::stoi(output[0]);
    this->prefix = output[1];
    this->msg = output[2];
    this->checksum = output[3];
}

logMsg::logMsg() {
    this->priority = 0;
    this->prefix = "";
    this->msg = "";
    this->checksum = "";
}
