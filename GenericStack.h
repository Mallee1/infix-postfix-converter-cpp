#ifndef GENERICSTACK_H
#define GENERICSTACK_H

#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class GenericStack {
private:
    T* container;    // The basic container (a dynamic array) storing elements.
    int capacity;    // Current capacity of the container.
    int tos;         // Top-of-stack index (number of elements stored).

    // Resizes the container to newCapacity.
    // This method allocates a new array with size newCapacity,
    // copies the existing elements, frees the old array,
    // and updates the capacity.
    void resize(int newCapacity);

public:
    // No-argument constructor.
    // Initializes the stack with a default capacity (10).
    GenericStack();

    // Constructor with an initial capacity.
    // Initializes the stack with the specified capacity.
    GenericStack(int cap);

    // Copy constructor.
    // Creates a new GenericStack as an exact copy of 'other'.
    GenericStack(const GenericStack<T>& other);

    // Assignment operator.
    // Assigns the contents of 'other' to this GenericStack.
    GenericStack<T>& operator=(const GenericStack<T>& other);

    // Destructor.
    // Frees the dynamically allocated container.
    ~GenericStack();

    // Returns true if the stack is empty; false otherwise.
    bool empty() const;

    // Pushes element x onto the stack.
    void push(const T& x);

    // Removes the top element from the stack.
    void pop();

    // Returns a reference to the top element (modifiable).
    T& top();

    // Returns a const reference to the top element (read-only).
    const T& top() const;

    // Returns the number of elements in the stack.
    int size() const;

    // Prints the stack's content to ostream os.
    // If ofc is provided, elements are separated by that character.
    // Elements are printed in the order they would be removed (LIFO order).
    void print(std::ostream& os, char ofc = '\0') const;
};

// Non-member operator overloads:

// Overloads << to print a GenericStack by invoking its print() method.
template <typename T>
ostream& operator<<(ostream& os, const GenericStack<T>& a);

// Compares two GenericStack objects for equality (same elements, same order).
template <typename T>
bool operator==(const GenericStack<T>& a, const GenericStack<T>& b);

// Compares two GenericStack objects lexicographically (by repeatedly comparing top elements).
template <typename T>
bool operator<(GenericStack<T> a, GenericStack<T> b);

#include "GenericStack.cpp"
#endif
