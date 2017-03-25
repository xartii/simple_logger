#include "logmsg.hpp" 
#include "functions.hpp"
#include <openssl/sha.h>
#include <ctime>

/**
 * @brief Metoda dodająca prefiks
 *
 * Metoda pozwala ustawić prefiks, który pojawi się przed logowaną wiadomością
 * @param p ciąg znaków, prefiks
 */
void logMsg::setPrefix(std::string p) {
    this->prefix = p;
}

/**
 * @brief Metoda ustawiająca priorytet
 *
 * Metoda pozwala ustawić priorytet logowanej wiadomości na jeden z wybranych.
 * @param pr priorytet, wartości: error, warning, info
 */
void logMsg::setPriority(enum priority pr) {
    this->priority = pr;
}

/**
 * @brief Metoda dodająca wiadomość
 *
 * Metoda pozwala ustawić treść logowanej wiadomości.
 * @param msg logowana wiadomość
 */
void logMsg::setMsg(std::string msg) {
    this->msg = msg;
}

/**
 * @brief Metoda zwracająca priorytet
 *
 * Metoda zwracająca wartość priorytetu logowanej wiadomości.
 * @return Jedna z trzech wartości priorytetu: error, warning, info
 */
int logMsg::getPriority() {
    return this->priority;
}

/**
 * @brief Metoda zwracająca prefiks
 *
 * Metoda zwraca prefiks logowanej wiadomości
 * @return Ciąg znaków, prefiks wiadomości
 */
std::string logMsg::getPrefix() {
    return this->prefix;
}

/**
 * @brief Metoda zwracająca wiadomość
 *
 * Metoda zwraca treść logowanej wiadomości
 * @return ciąg znaków, treść wiadomości
 */
std::string logMsg::getMsg() {
    return this->msg;
}

/**
 * @brief Metoda zamieniająca wiadomość w ciąg znaków
 *
 * Metoda zamienia cały obiekt w ciąg znaków możliwy do przesłania między
 * klientem a serwerem
 * @return ciąg znaków, wiadomość w formacie możliwym do przesłania
 */
std::string logMsg::printLog() {
    std::string output;
    output.append(this->date);
    output.append("|");
    output.append(std::to_string(this->priority));
    output.append("|");
    output.append(this->prefix);
    output.append("|");
    output.append(this->msg);
    output.append("|");
    output.append(this->checksum);

    return output;
}

/**
 * @brief Metoda obliczająca sumę kontrolną wiadomości.
 *
 * Metoda oblicza sumę kontrolną SHA1 wszystkich pól wiadomości, priorytetu,
 * prefiksu i jej treści. Wartość suma jest przypisywana do pola checksum
 * obiektu.
 */
void logMsg::calcChecksum() {
    unsigned char temp[SHA_DIGEST_LENGTH];
    std::string ms;

    ms.append(this->date);
    ms.append("|");
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

/**
 * @brief konstruktor tworzący obiekt wiadomość z ciągu znaków
 *
 * Konstruktor tworzy obiekt wiadomość z ciągu znaków stworzonego wcześniej
 * przez metodą printLog. Sprawdza poprawność sumy kontrolnej. Jeśli się nie
 * zgadza tworzona jest pusta wiadomość.
 * @param msg Ciąg znaków, na podstawie którego tworzony jest obiekt wiadomości.
 */
logMsg::logMsg(std::string msg) {
    std::vector<std::string> output;

    output = explode(msg, "|");
    this->date = output[0];
    this->priority = std::stoi(output[1]);
    this->prefix = output[2];
    this->msg = output[3];
    this->calcChecksum();
    if(this->checksum.compare(output[4]) != 0) {
        this->priority = 0;
        this->prefix = "";
        this->msg = "";
        this->checksum = "";
    }
}

/**
 * @brief Domyślny konstruktor
 *
 * Domyślny konstruktor tworzący pustą wiadomość
 */
logMsg::logMsg() {
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[128];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 128, "%R %D", timeinfo);
    this->date = buffer;
    this->priority = 0;
    this->prefix = "";
    this->msg = "";
    this->checksum = "";
}
