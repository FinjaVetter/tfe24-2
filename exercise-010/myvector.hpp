#ifndef MY_VECTOR_HPP
#define MY_VECTOR_HPP

#include <cstddef>   // for size_t
#include <stdexcept> // for std::out_of_range

class MyVector {
public:
    // Default constructor: creates empty vector with zero size and capacity
    MyVector();

    // Constructor with initial size: allocates storage for 'size' elements
    MyVector(unsigned int size);

    // Copy constructor for deep copying another MyVector
    MyVector(const MyVector& other);

    // Copy assignment operator for deep copying with self-assignment check
    MyVector& operator=(const MyVector& other);

    // Destructor frees allocated memory
    ~MyVector();

    // Adds an element to the end of the vector, resizing if needed
    void push_back(int value);

    // Access element with bounds checking; throws std::out_of_range if invalid
    int& at(size_t index);
    const int& at(size_t index) const;

    // Access element without bounds checking (like operator[])
    int& operator[](size_t index) { return m_data[index]; }
    const int& operator[](size_t index) const { return m_data[index]; }

    // Returns current number of elements stored
    unsigned int size() const noexcept;

    // Returns current capacity (allocated storage size)
    unsigned int capacity() const noexcept;

    // Allocates storage to hold at least new_cap elements
    void reserve(unsigned int new_cap);

    // Changes the size to new_size, default-filling new elements if enlarged
    void resize(unsigned int new_size);

    // Clears the vector (size becomes zero, capacity unchanged)
    void clear() noexcept;

private:
    // Private helper: reallocate storage to new capacity and copy existing data
    void reallocate(unsigned int new_cap);

    int* m_data;              // pointer to dynamically allocated array
    unsigned int m_size;      // current number of elements
    unsigned int m_capacity;  // allocated capacity of array
};

#endif /* MY_VECTOR_HPP */
