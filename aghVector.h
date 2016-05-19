/**
 * @file aghVector.h
 * @author Łukasz Mielczarek, Łukasz Szcześniak
 * @date 05|05|2016
 * @version 0.1
 * @brief Contains declaration and definitions of aghVector template class.
*/

// --------------------------------------------------------------------------------

#ifndef DATA_CONTAINER_AGHVECTOR_H
#define DATA_CONTAINER_AGHVECTOR_H

#include "aghContainer.h"
#include <iostream>

using namespace std;

/**
 * Class template to provide operation on vectors.
*/
template<typename T>
class aghVector :
        public aghContainer<T> {
public:
    /**
     * Default constructor.
     */
    aghVector();

    /**
     * Copy constructor
     * @param another vector
     */
    aghVector(const aghContainer<T> &);

    /**
     * Destructor.
     */
    ~aghVector();

    /**
     * Insert an element at specified position.
     * @param position number
     * @param new element
     */
    bool insert(const int, const T &);

    /**
     * Get element at specified position.
     * @param position number
     */
    T &at(const int) const;

    /**
     * Get size of the container.
     * @return int size
     */
    int size(void) const;

    /**
     * Remove element at specified position.
     * @param position number
     * @return bool
     */
    bool remove(const int);

    /**
     * Remove all elements from the container.
     */
    void clear(void);

    /**
     * Make copy of another containe
     *
     * @param another container
     */
    void copy(const aghContainer<T> &source);

    /**
     * Assignment operator
     *
     * @param another vector
     * @return reference to the object
     */
    aghContainer<T> &operator=(const aghContainer<T> &);


private:
    T *vector; //< Pointer to table that holds vector.
    unsigned int elements; //< Number of elements in vector.

    /**
     * Frees memory allocated for vector.
     */
    void destroyVector();
};

// --------------------------------------------------------------------------------
// End of aghVector declaration.
// --------------------------------------------------------------------------------

template<typename T>
aghVector<T>::aghVector() : vector(nullptr), elements(0) {
}

// --------------------------------------------------------------------------------

template<typename T>
aghVector<T>::aghVector(const aghContainer<T> &another) : vector(nullptr) {
    this->copy(another);
}

// --------------------------------------------------------------------------------

template<typename T>
aghVector<T>::~aghVector() {
    this->clear();
}

// --------------------------------------------------------------------------------

template<typename T>
bool aghVector<T>::insert(const int index, const T &newValue) {
    if (index > elements || index < 0)
        return false;
    T *tmp = new T[elements + 1];
    if (!tmp)
        throw aghException(1, "No memory that could be allocated", __FILE__, __LINE__);
    for (int i = 0; i < elements; ++i)
        tmp[(i < index ? i : i + 1)] = this->vector[i];
    tmp[index] = newValue;
    this->destroyVector();
    this->vector = tmp;
    ++elements;
    return true;
}

// --------------------------------------------------------------------------------

template<typename T>
T &aghVector<T>::at(const int pos) const {
    if (pos < 0 || pos >= this->elements)
        throw aghException(1, "Wrong index demanded", __FILE__, __LINE__);
    return this->vector[pos];
}

// --------------------------------------------------------------------------------

template<typename T>
int aghVector<T>::size() const {
    return this->elements;
}

// --------------------------------------------------------------------------------

template<typename T>
bool aghVector<T>::remove(const int index) {
    if (index < 0 || index >= this->elements)
        return false;
    T *tmp = new T[elements - 1];
    for (int i = 0; i < elements - 1; i++)
        tmp[i] = this->vector[(i < index ? i : i + 1)];
    delete[] this->vector;
    this->vector = tmp;
    this->elements--;
    return true;
}

// --------------------------------------------------------------------------------

template<typename T>
void aghVector<T>::clear() {
    this->destroyVector();
    this->elements = 0;
}

// --------------------------------------------------------------------------------

template<typename T>
aghContainer<T> &aghVector<T>::operator=(const aghContainer<T> &another) {
    this->copy(another);
    return *this;
}

// --------------------------------------------------------------------------------

template<typename T>
void aghVector<T>::copy(const aghContainer<T> &source) {
    if (this != &source) {
        this->destroyVector();
        this->elements = source.size();
        this->vector = new T[this->elements];
        for (int i = 0; i < this->elements; ++i)
            this->vector[i] = source.at(i);
    }
    return;
}

// --------------------------------------------------------------------------------

template<typename T>
void aghVector<T>::destroyVector() {
    if (this->vector)
        delete[] this->vector;
    this->vector = nullptr;
}

// --------------------------------------------------------------------------------

#endif
