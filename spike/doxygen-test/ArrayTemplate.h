#ifndef OPENENGINE_TEMPLATE_H
#define OPENENGINE_TEMPLATE_H

#include <iterator>

#include <cstring>

//! Template for a standard array.
//!
//! This is a generic array template that has a default size of
//! 10 elements.
//!
//! @tparam T The type contained in the array.
//! @tparam N The size of the array.
//!
//! @version 1.0.0
//! @pre Understand template types.
//! @bug There are *no* bugs!
//! @copyright GNU Public License
//! @date 1989-2018
//! @author jyates
//!
template<typename T, std::size_t N = 10>
class Array {
    //! The internal array structure.
    T m_array[N];

    //! The size of the array.
    const std::size_t m_count;

public:
    //! This is the internal iterator for this class.
    //!
    //! The iterator declared here allows one to use instances
    //! of this Array template in modern for loops and algorithms.
    //!
    class Iterator : public std::iterator<
            std::forward_iterator_tag,
            T,              //!< type
            std::ptrdiff_t, //!< diff type
            T*,             //!< pointer type
            T&              //!< reference type
    > {

        //! Points to the current element in the array.
        T* m_currentNode;

    public:
        //! Constructor that explicitly initializes the internal pointer.
        explicit Iterator();

        //! Constructor use to create the iterator from an external pointer.
        //!
        //! @param currentValue Typically a pointer to the beginning of the array.
        //!
        explicit Iterator(T* currentValue);

        //! Overload the dereference operator (required for iterators).
        //!
        //! @return Reference to the current element.
        //!
        T& operator*() const;

        //! Pre-increment operator overload.
        //!
        //! Increment to the next element without creating a copy.
        //!
        //! @return Reference to the current instance.
        //!
        Iterator& operator++();

        //! Post-increment operator overload.
        //!
        //! Create a copy of the iterator and then increment to the next
        //! element.
        //!
        //! @return Copy of a new instance.
        const Iterator operator++(int);

        //! Pre-decrement operator overload.
        //!
        //! Decrement to the previous element without creating a copy.
        //!
        //! @return Reference to the current instance.
        //!
        Iterator& operator--();

        //! Post-decrement operator overload.
        //!
        //! Create a copy of the iterator and then decrement to the next
        //! element.
        //!
        //! @return Copy of a new instance before incrementing.
        //!
        const Iterator operator--(int);

        //! Equality operator overload.
        //!
        //! @param right Operand to the right of the equality operator.
        //!
        //! @return True if instance is equal to operand.
        //!
        bool operator==(const Iterator& right);

        //! Inequality operator overload.
        //!
        //! @param right Operand to the righ tof the inequality operator.
        //!
        //! @return True if instance is _not_ equal to operand.
        //!
        bool operator!=(const Iterator& right);

    };

    //! Explicitly defined constructor for Array template.
    //!
    //! This constructor provides an initialization parameter but also includes
    //! a default if there is none provided.
    //!
    //! @param someType The first element of the Array.
    //!
    explicit Array(T someType = T());

    //! Subscript operator overload.
    //!
    //! Provides the widely used subscript operator for the Array class.
    //!
    //! @param index Index at which to find the element.
    //!
    //! @return Reference to the element at index.
    //!
    T& operator[](std::size_t index);

    //! Const qualified subscript operator overload.
    //!
    //! Provides the widely used subscript operator (but this time, const
    //! qualified) for the Array class.
    //!
    //! @param index Index at which to find the element.
    //!
    //! @return Const reference to the element at index.
    //!
    const T& operator[](std::size_t index) const;

    //! Provide a const qualified pointer to the array.
    //!
    //! @return The raw pointer to the beginning of the array.
    //!
    const T* raw() const;

    //! Return the const iterator pointing to the beginning of the array.
    //!
    //! @return Const qualified copy of the iterator pointing to array start.
    //!
    const Iterator begin() const;

    //! Return the iterator pointing to the beginning of the array.
    //!
    //! @return Copy of the iterator pointing to the array start.
    Iterator begin();

    //! Return the const iterator pointing to the end of the array.
    //!
    //! This will return the const qualified iterator pointing to end of the
    //! array, such that the position is equal to start + size.
    //!
    //! @return Const qualified copy of the iterator pointing to the end of the
    //!         array.
    //!
    const Iterator end() const;

    //! Return the iterator pointing to the end of the array.
    //!
    //! This will return the iterator pointing to the end of the array, such
    //! that the position is equal to start + size.
    //!
    //! @return Copy of the iterator pointing to the end of the array.
    //!
    Iterator end();

    //! Get the size of the array, declared at compile time.
    //!
    //! @return The size of the array.
    //!
    const std::size_t size() const;
};

template<typename T, size_t N>
Array<T, N>::Iterator::Iterator() :
    m_currentNode(nullptr) { }

template<typename T, size_t N>
Array<T, N>::Iterator::Iterator(T* currentValue) :
    m_currentNode(currentValue) { }

template<typename T, size_t N>
T& Array<T, N>::Iterator::operator*() const {
    return *m_currentNode;
}

template<typename T, size_t N>
typename Array<T, N>::Iterator& Array<T, N>::Iterator::operator++() {
    ++m_currentNode;
    return *this;
}

template<typename T, size_t N>
const typename Array<T, N>::Iterator Array<T, N>::Iterator::operator++(int) {
    Iterator temporaryIterator = *this;
    ++m_currentNode;
    return temporaryIterator;
}

template<typename T, size_t N>
typename Array<T, N>::Iterator& Array<T, N>::Iterator::operator--() {
    --m_currentNode;
    return *this;
}

template<typename T, size_t N>
const typename Array<T, N>::Iterator Array<T, N>::Iterator::operator--(int) {
    Iterator temporaryIterator = *this;
    ++m_currentNode;
    return *this;
}

template<typename T, size_t N>
bool Array<T, N>::Iterator::operator==(const Array::Iterator& right) {
    return *m_currentNode == *right.m_currentNode;
}

template<typename T, size_t N>
bool Array<T, N>::Iterator::operator!=(const Array::Iterator& right) {
    return !(*this == right);
}

template<typename T, std::size_t N>
Array<T, N>::Array(T someType) :
    m_array{ someType },
    m_count(N) { }

template<typename T, std::size_t N>
T& Array<T, N>::operator[](std::size_t index) {
    return m_array[index];
}

template<typename T, std::size_t N>
const T& Array<T, N>::operator[](std::size_t index) const {
    return m_array[index];
}

template<typename T, size_t N>
const T* Array<T, N>::raw() const {
    return m_array;
}

template<typename T, std::size_t N>
const typename Array<T, N>::Iterator Array<T, N>::begin() const {
    return Array<T, N>::Iterator(m_array);
}

template<typename T, std::size_t N>
typename Array<T, N>::Iterator Array<T, N>::begin() {
    return Array<T, N>::Iterator(m_array);
}

template<typename T, std::size_t N>
const typename Array<T, N>::Iterator Array<T, N>::end() const {
    return Array<T, N>::Iterator(m_array + m_count);
}

template<typename T, std::size_t N>
typename Array<T, N>::Iterator Array<T, N>::end() {
    return Array<T, N>::Iterator(m_array + m_count);
}

template<typename T, std::size_t N>
const std::size_t Array<T, N>::size() const {
    return m_count;
}

#endif //OPENENGINE_TEMPLATE_H
