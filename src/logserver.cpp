#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <fstream>
#include <iostream>
#include "logmsg.hpp"
#include "logserver.hpp"

/**
 * @brief Metoda ustawiająca numer portu
 *
 * Metoda ustawia numer portu do nasłuchiwania zdalnych połączeń. Jeśli numer
 * portu jest z poza zakresu 0,65535 ustawiana jest wartość domyślna 10000.
 * 
 * @param p numer portu, liczba całkowita
 */
void logServer::setRemotePort(int p){
    if(p > 65535 || p < 0) {
        this->port = 10000;
    } else {
        this->port = p;
    }
}

/**
 * @brief Metoda ustawiająca adres serwera
 * 
 * Metoda ustawia adres, na którym serwer ma nasłuchiwać zdalnych połączeń
 * 
 * @param ip ciąg znaków, adres ip lub nazwa domenowa, na której serwer ma słuchać
 */
void logServer::setRemoteAddress(std::string ip) {
	this->remoteAddr = ip;
}



/**
 * @brief Metoda ustawiająca ścieżkę logów.
 *
 * Metoda pozwala ustawić ścieżkę w której zapisywane będą logowane wiadomości.
 *
 * @param path ścieżka, w której zapisywane mają być logi.
 */
void logServer::setLogPath(std::string path){
    this->path = path;
}


/**
 * @brief Metoda uruchamiająca serwer zbierający logi
 *
 * Metoda uruchamia serwer nasłuchujący na porcie i adresie ustawionych
 * wcześniej. Serwer zbiera logi i zapisuje je do katalogu podanego wcześniej.
 *
 * @returns zwraca 0 jeśli udało się uruchomić serwer, a -1 w razie błędu
 */
int logServer::startRemoteListener() {
	int childfd;
	struct addrinfo hints;
	struct addrinfo *servinfo;
	struct sockaddr_storage remoteinfo;
	int status;
	int yes = 1;
	std::string msg;
	pid_t pid;
	char c;
	
	memset(&hints, 0, sizeof hints);
	
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	
    std::string port = std::to_string(this->port);
	status = getaddrinfo(this->remoteAddr.c_str(), port.c_str(), &hints, &servinfo);

	if(status != 0) 
		return -1;
		
	if(servinfo == NULL)
		return -1;
		
	this->remotefd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
	
	if(this->remotefd == -1)
		return -1;
		
	if(setsockopt(this->remotefd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		return -1;
		
	if(bind(this->remotefd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
		close(this->remotefd);
		return -1;
	}
	
    status = listen(this->remotefd, 10);
	if(status == -1) 
		return -1;
    socklen_t addrlen = sizeof remoteinfo;
    pid = fork();
    if(pid > 0) 
        this->listeners.push_back(pid);
    if(pid == 0) {
    	while(1) {
    		childfd = accept(this->remotefd, (struct sockaddr*)&remoteinfo, &addrlen);
    		
    		if(childfd == -1)
    			continue;
    		pid = fork();
    		if(pid > 0)
    		    this->listeners.push_back(pid);
    
	    	if(pid == 0) {
    			close(this->remotefd);
    			do {
    				status = recv(childfd, (char*)&c, 1, 0);
                    msg += c;
    				if(msg.find("\n") != std::string::npos) {
                        msg = msg.substr(0, msg.size()-1);
    					logMsg log(msg);
                        if((log.getMsg()).compare("") == 0) {
                            msg.clear();
                            continue;
                        }
    					this->_saveMsg(log);
    					msg.clear();
                    }
    			} while(status != 0);
    		}
    		close(childfd);
    	}
    	close(this->remotefd);
    }

    return 0;
}

/*
 * @brief Metoda wyłączająca serwer zbierania logów.
 *
 * Metoda wyłącza serwer zbierania logów, wysyłając do wszystkich procesów
 * potomnych sygnał SIGTERM
 */
void logServer::stopRemoteListener() {
	for(pid_t p : this->listeners) {
        kill(p, SIGTERM);
    }
}

void logServer::_saveMsg(logMsg ms) {
    std::string fPath;
    switch(ms.getPriority()) {
        case 2:
            fPath = this->path + "/error.log";
            break;
        case 1:
            fPath = this->path + "/warning.log";
            break;
        case 0:
            fPath = this->path + "/info.log";
            break;
    }

    std::ofstream fHnd (fPath, std::ios::app);
    fHnd << ms.printLog() << std::endl;
    fHnd.close();
}


