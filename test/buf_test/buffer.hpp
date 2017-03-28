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
        void addElem(T elem);
        void clearBuffer();
        T getFirst();
        T getLast();
        bool isEmpty();
};

#include "buffer.cpp"
