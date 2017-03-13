#include <string>

enum priority { error = 2, warning = 1, info = 0 };


class logMsg {
    private:
        int priority;
        std::string prefix;
        std::string msg;
        std::string checksum;
    public:
        void setPrefix(std::string p);
        void setPriority(enum priority pr);
        void setMsg(std::string msg);
        enum priority getPriority();
        std::string getPrefix();
        std::string getMsg();
        std::string printLog();
        void calcChecksum();
};

