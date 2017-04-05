#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include "buffer.hpp"
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
 * @brief Metoda ustawiająca plik lokalnego gniazda
 *
 * Metoda ustawia ścieżkę do pliku, który ma być używany do obsługi lokalnych
 * połączeń do serwera.
 *
 * @param filename ciąg znaków, ścieżka do pliku
 */
void logServer::setLocalSocket(std::string filename){
    this->localSock = filename;
}

/**
 * @brief Metoda włączająca buforowanie
 *
 * Metoda pozwala włączać lub wyłączać buforowanie przychodzących wiadomości
 * przed ich zapisem do logów.
 *
 * @param state false - buforowanie wyłączone, true - buforowanie włączone
 * @return Aktualnie ustawiony stan buforowania
 */
bool logServer::enableBuffering(bool state) {
    this->buffering = state;
    return this->buffering;
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
 * @brief Metoda zwracająca stan buforowania
 *
 * Metoda zwraca informacje o tym czy włączone jest buforowanie przychodzących
 * wiadomości do logowania.
 *
 * @return true - buforowanie jest włączone, false - buforowanie jest wyłączone
 */
bool logServer::isBuffered(){
    return this->buffering;
}

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
    				if(c == '\n') {
    					logMsg log(msg);
    					if(this->buffering) {
    						this->buf.addElem(log);
    					} else {
    						this->_saveMsg(log);
    					}
    					msg.clear();
    				} else {
    					msg +=c;
    				}
    			} while(status != 0);
    		}
    		close(childfd);
    	}
    	close(this->remotefd);
    }
}

void logServer::stopRemoteListener() {
	for(pid_t p : this->listeners) {
        kill(p, SIGTERM);
    }
}
