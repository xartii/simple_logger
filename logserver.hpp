/**
 * @brief Klasa serwera logującego
 *
 * Klasa obsługująca serwer logujący przychodzące wiadomości.
 */
class logServer {
    private:
        int port = 10000;
        std::string path;
        std::string localSock;
        bool buffering;
        buffer<logMsg> buf;
    public:
        void setRemotePort(int p);
        void setLocalSocket(std::string filename);
        int startLocallistener();
        int startRemoteListener();
        int stopLocalListener();
        int stopRemoteListener();
        void setLogPath(std::string path);
        bool enableBuffering(bool state);
        bool isBuffered();
        int saveLogs();

};
