#include "logmsg.hpp"
#include "buffer.hpp"
#include "logger.hpp"
#include <string>
#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
/**
 * @brief Funkcja włączająca buforowanie
 *
 * Funkcja włącza/wyłącza buforowanie wiadomości przed wysłaniem. Aby wysłać
 * buforowane wiadomości należy użyc @see log::sendMsgs()
 *
 * @param state bool, true lub false, zależnie czy buforowanie ma być włączone
 * czy nie.
 */
void log::enableBuffering(bool state) {
    this->buffering = state;
}

/**
 * @brief Funkcja sprawdzająca stan połączenia
 *
 * Funkcja sprawdza czy klient jest połączony z serwerem logów
 *
 * @return bool, true lub false zależnie od tego czy klient jest połączony
 */
bool log::isConnected() {
    return this->connected;
}

/**
 * @brief Funkcja sprawdzająca buforowanie
 *
 * Funkcja sprawza czy włączone jest buforowanie wiadomości przed wysłaniem do
 * serwera.
 *
 * @return bool, true lub false zależnie od tego czy buforowanie jest włączone
 */
bool log::isBuffered() {
    return this->buffering;
}

/**
 * @brief Funkcja łącząca się z serwerem
 *
 * Funkcja łączy klienta ze zdalnym serwerem logoów.
 *
 * @param host, ciąg znaków, adres IP lub nazwa domenowa hosta, do którego
 * klient ma się podłączyć
 * @param p, numer portu na którym ma nastąpić połączenie
 *
 * @returns -1 w przypadku błędu, 0 jeśli udało się połączyć.
 */
int log::connectRemote(std::string host, int p) {
    struct addrinfo hints;
    struct addrinfo *servinfo;
    int status;
    std::string port;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    port = std::to_string(p);
    status = getaddrinfo(host.c_str(), port.c_str(), &hints, &servinfo);

    if(status)
        return -1;

    sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

    if(sockfd == -1)
        return -1;

    status = connect(this->sockfd, servinfo->ai_addr, servinfo->ai_addrlen);

    if(status == -1) {
        close(this->sockfd);
        return -1;
    }

    this->connected = true;
    return 0;
}
/**
 * @brief Funkcja odłączająca klienta od serwera
 */
void log::disconnect() {
    if(this->connected)
        close(this->sockfd);
}

int log::_sendMsg(logMsg ms) {
    std::string m;
    int status;

    m = ms.printLog() + "\n";
    status = send(this->sockfd, m.c_str(), m.length(), 0);

    return status;
}
/**
 * @brief Metoda dodająca wiadomość
 *
 * Metoda pozwala na dodawanie logowanych wiadomości. Jeśli włączone jest
 * buforowanie wiadomość dodawana jest do bufora. Jeśli nie, jest od razu
 * wysyłana
 *
 * @param ms wiadomość do logowania
 *
 * @returns 0 jeśli wszystko się udało, -1 w razie błędu
 */
int log::addMsg(logMsg ms) {
    if(this->buffering) {
        this->buf.addElem(ms);
        return 0;
    } else {
        return this->_sendMsg(ms);
    }
    return -1;
}

/**
 * @brief Metoda wysyłająca buforowane logi.
 *
 * Metoda wysyła do serwera wszystkie logi aktualnie przechowywane w buforze w
 * kolejności od pierwszego przyjętego do ostatniego.
 *
 * @returns -1 w razie błędu, 0 jeśli wszystko przebiegło poprawnie
 */
int log::sendMsgs() {
    logMsg tmp;
    int status;

    if(!this->buffering) 
        return -1;

    while(!this->buf.isEmpty()) {
        tmp = this->buf.getFirst();
        status = this->_sendMsg(tmp);
        if(status == -1)
            return status;
    }

    return 0;
}
