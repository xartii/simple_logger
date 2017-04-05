/**
 * @brief Klasa serwera logującego
 *
 * Klasa obsługująca serwer logujący przychodzące wiadomości.
 */
class logServer {
    private:
        int port = 10000;
		int remotefd;
        std::string path;
        std::string localSock;
		std::string remoteAddr;
        bool buffering;
		bool listening = true;
        buffer<logMsg> buf;
        void _saveMsg(logMsg ms);
    public:
        void setRemotePort(int p);
		void setRemoteAddress(std::string ip);
        void setLocalSocket(std::string filename);
        int startLocallistener();
        int startRemoteListener();
        int stopLocalListener();
        void stopRemoteListener();
        void setLogPath(std::string path);
        bool enableBuffering(bool state);
        bool isBuffered();
        int saveLogs();

};
