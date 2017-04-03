#include <string>
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
