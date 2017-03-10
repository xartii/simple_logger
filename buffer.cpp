#include <string>
#include <vector>
/**
 * @brief Szablon klasy bufora.
 *
 * Szablon klasy bufora przechowującego logowane wiadomości.
 */
template <class T>
class buffer {
    private:
        std::vector<T> buf; /**< Wektor przechowujący elementy T w buforze.*/
    public:
        buffer(); 
        void addElem(T elem);
        void clearBuffer();
        T getFirst();
        T getLast();
        bool isEmpty();
};

/**
 * @brief Metoda dodająca element na koniec bufora.
 *
 * Metoda, która dodaje element na koniec bufora wiadomości
 * @param elem Element typu T, który ma być dodany do bufora
 */
template <class T>
void buffer<T>::addElem(T elem) {
    this->buf.push_back(elem);
}
/**
 * @brief Metoda sprawdzająca stan bufora.
 *
 * Metoda, która sprawdza czy bufor jest pusty czy też nie.
 * @return true gdy bufor jest pusty, false gdy nie
 */
template <class T>
bool buffer<T>::isEmpty() {
    return this->buf.empty;
}
/**
 * @brief Metoda zwracająca pierwszy element bufora.
 *
 * Metoda zwraca pierwszy element bufora, a także usuwa go z bufora.
 * @return Pierwszy element bufora.
 */
template <class T>
T buffer<T>::getFirst() {
    T tmp;
    typename std::vector<T>::iterator it;
    if(this->buf.empty())
        return NULL;
    it = this->buf.begin();
    tmp = *it;
    this->buf.erase(it);
    return tmp;
}

/**
 * @brief Metoda zwracająca ostatni element bufora
 *
 * Metoda zwraca ostatni element bufora, a także usuwa go z bufora.
 * @return Ostatni element bufora.
 */
template <class T>
T buffer<T>::getLast() {
    T tmp;
    typename std::vector<T>::iterator it;
    if(this->buf.empty())
        return NULL;
    it = this->buf.end();
    tmp = *it;
    this->buf.pop_back();
    return tmp;
}
/**
 * @brief Metoda czyszcząca bufor
 *
 * Metoda, która usuwa wszystkie elementy bufora od pierwszego do ostatniego.
 */
template <class T>
void buffer<T>::clearBuffer() {
    this->buf.erase(this->buf.begin(), this->buf.end());
}
