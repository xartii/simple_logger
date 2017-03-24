#include <string>
#include <openssl/sha.h>

enum priority { error = 2, warning = 1, info = 0 };

/**
 * @brief Klasa wiadomości logowanych
 *
 * Klasa przechowuje pojedyńczą wiadomość, która ma być logowana
 */
class logMsg {
    private:
        int priority; /**< Priorytet wiadomości */
        std::string prefix; /**< Prefiks wiadomości, dopisywany przed wiadomością */
        std::string msg; /**< Treść wiadomości */
        std::string checksum; /**< Suma kontrolna logowanej wiadomości*/
    public:
        void setPrefix(std::string p);
        void setPriority(enum priority pr);
        void setMsg(std::string msg);
        int getPriority();
        std::string getPrefix();
        std::string getMsg();
        std::string printLog();
        void calcChecksum();
};

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
    output.append("|");
    output.append(this->prefix);
    output.append("|");
    output.append(this->msg);
    output.append("||");
    output.append(this->checksum);
    output.append("|||");

    return output;
}
void logMsg::calcChecksum() {
    unsigned char temp[SHA_DIGEST_LENGTH];
    std::string ms;

    ms.append(std::to_string(this->priority));
    ms.append("|");
    ms.append(this->prefix);
    ms.append("|");
    ms.append("|");
    ms.append(this->msg);


    SHA1((const unsigned char*)(ms.c_str()), ms.size(), temp);

    for (int i = 0 ; i < SHA_DIGEST_LENGTH; i++) {
        sprintf((char*)this->checksum[i*2], "%02x", temp[i]);
    }
}
