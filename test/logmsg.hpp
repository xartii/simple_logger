#include <string>

enum priority { error = 2, warning = 1, info = 0 };


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

