#include "GenericStack.h"

// Resizes the container to newCapacity.
// Allocates a new array, copies existing elements, deletes the old array, and updates capacity.
template <typename T>
void GenericStack<T>::resize(int newCapacity) {
    T* newContainer = new T[newCapacity];   // Allocate a new array.
    for (int i = 0; i < tos; ++i)
        newContainer[i] = container[i];       // Copy elements from the old container.
    delete [] container;                      // Free the old array.
    container = newContainer;                 // Update container pointer.
    capacity = newCapacity;                   // Update capacity.
}

// No-argument constructor.
// Initializes the stack with a default capacity of 10 and sets the top-of-stack index to 0.
template <typename T>
GenericStack<T>::GenericStack() : capacity(10), tos(0) {
    container = new T[capacity];
}

// Constructor with initial capacity.
// Initializes the stack with the specified capacity (or 10 if the given capacity is <= 0).
template <typename T>
GenericStack<T>::GenericStack(int cap) : capacity(cap), tos(0) {
    if(cap <= 0)
        capacity = 10;
    container = new T[capacity];
}

// Copy constructor.
// Creates a new GenericStack that is an exact copy of 'other' by duplicating its container and tos.
template <typename T>
GenericStack<T>::GenericStack(const GenericStack<T>& other)
    : capacity(other.capacity), tos(other.tos)
{
    container = new T[capacity];
    for (int i = 0; i < tos; i++)
        container[i] = other.container[i];
}

// Assignment operator.
// First checks for self-assignment, then deletes the current container and copies the data from 'other'.
template <typename T>
GenericStack<T>& GenericStack<T>::operator=(const GenericStack<T>& other) {
    if (this != &other) {
        delete [] container;
        capacity = other.capacity;
        tos = other.tos;
        container = new T[capacity];
        for (int i = 0; i < tos; i++)
            container[i] = other.container[i];
    }
    return *this;
}

// Destructor.
// Frees the memory allocated for the container.
template <typename T>
GenericStack<T>::~GenericStack() {
    delete [] container;
}

// Returns true if the stack is empty (i.e., tos is 0).
template <typename T>
bool GenericStack<T>::empty() const {
    return (tos == 0);
}

// Pushes the element x onto the stack.
// If the container is full, it calls resize() to expand the capacity.
template <typename T>
void GenericStack<T>::push(const T& x) {
    if (tos >= capacity)
        resize(2 * capacity + 1);
    container[tos++] = x;
}

// Removes the top element from the stack by simply decrementing tos.
// Throws a runtime error if the stack is empty.
template <typename T>
void GenericStack<T>::pop() {
    if (empty())
        throw std::runtime_error("Stack is empty");
    tos--;
}

// Returns a reference to the top element (the last element pushed).
// Throws a runtime error if the stack is empty.
template <typename T>
T& GenericStack<T>::top() {
    if (empty())
        throw std::runtime_error("Stack is empty");
    return container[tos - 1];
}

// Returns a const reference to the top element (read-only version).
template <typename T>
const T& GenericStack<T>::top() const {
    if (empty())
        throw std::runtime_error("Stack is empty");
    return container[tos - 1];
}

// Returns the number of elements in the stack.
template <typename T>
int GenericStack<T>::size() const {
    return tos;
}

// Prints the stack's elements to the provided ostream.
// Elements are printed in reverse order (the order in which they would be popped).
template <typename T>
void GenericStack<T>::print(ostream& os, char ofc) const {
    for (int i = tos - 1; i >= 0; i--) {
        os << container[i];
        if (ofc != '\0' && i > 0)
            os << ofc;
    }
}

// Non-member operator<< overload.
// Uses the print() method to output the stack's contents.
template <typename T>
ostream& operator<<(ostream& os, const GenericStack<T>& a) {
    a.print(os);
    return os;
}

// Non-member operator== overload.
// Compares two stacks for equality by making copies and repeatedly comparing top elements.
template <typename T>
bool operator==(const GenericStack<T>& a, const GenericStack<T>& b) {
    if (a.size() != b.size())
        return false;
    GenericStack<T> copyA(a);
    GenericStack<T> copyB(b);
    while (!copyA.empty() && !copyB.empty()) {
        if (copyA.top() != copyB.top())
            return false;
        copyA.pop();
        copyB.pop();
    }
    return true;
}

// Non-member operator< overload.
// Returns true if, by repeatedly popping, each element from stack a is less than the corresponding element from b.
template <typename T>
bool operator<(GenericStack<T> a, GenericStack<T> b) {
    while (!a.empty() && !b.empty()) {
        if (!(a.top() < b.top()))
            return false;
        a.pop();
        b.pop();
    }
    return a.empty();
}
