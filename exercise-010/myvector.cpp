#include "myvector.hpp"
#include <fmt/format.h>
#include <algorithm>

// Default constructor initializes empty vector with no allocated data
MyVector::MyVector() : m_data(nullptr), m_size(0), m_capacity(0) {
    fmt::println("[MyVector] welcome to the CTOR!");
}

// Constructor with initial size, allocates memory for 'size' elements, zero-initialized
MyVector::MyVector(unsigned int size)
    : m_data(size ? new int[size]() : nullptr), m_size(size), m_capacity(size)
{
    fmt::println("[MyVector] welcome to the size CTOR!");
}

// Copy constructor performs deep copy of other's data
MyVector::MyVector(const MyVector& other)
    : m_data(other.m_capacity ? new int[other.m_capacity]() : nullptr),
      m_size(other.m_size), m_capacity(other.m_capacity)
{
    fmt::println("[MyVector] copy CTOR");
    std::copy(other.m_data, other.m_data + m_size, m_data);
}

// Copy assignment operator with self-assignment check, deep copies data
MyVector& MyVector::operator=(const MyVector& other) {
    if (this != &other) {
        delete[] m_data;  // release current storage
        m_capacity = other.m_capacity;
        m_size = other.m_size;
        m_data = other.m_capacity ? new int[other.m_capacity]() : nullptr;
        std::copy(other.m_data, other.m_data + m_size, m_data);
    }
    fmt::println("[MyVector] copy assignment");
    return *this;
}

// Destructor releases allocated memory
MyVector::~MyVector() {
    fmt::println("[MyVector] welcome to the DTOR!");
    delete[] m_data;
}

// Adds a new value at the end, reallocating if capacity is insufficient
void MyVector::push_back(int value) {
    if (m_size == m_capacity) {
        reserve(m_capacity ? m_capacity * 2 : 1); // double capacity or start at 1
    }
    m_data[m_size++] = value;
}

// Returns a reference to element at index with bounds checking
int& MyVector::at(size_t index) {
    if(index >= m_size) throw std::out_of_range("MyVector::at");
    return m_data[index];
}
const int& MyVector::at(size_t index) const {
    if(index >= m_size) throw std::out_of_range("MyVector::at");
    return m_data[index];
}

// Returns current size (number of stored elements)
unsigned int MyVector::size() const noexcept { return m_size; }

// Returns current capacity (allocated storage size)
unsigned int MyVector::capacity() const noexcept { return m_capacity; }

// Reserves memory for at least new_cap elements, reallocates if needed
void MyVector::reserve(unsigned int new_cap) {
    if (new_cap > m_capacity)
        reallocate(new_cap);
}

// Resizes the vector to new_size, default-initializes extended elements with 0
void MyVector::resize(unsigned int new_size) {
    if (new_size > m_capacity)
        reserve(new_size);
    if (new_size > m_size)
        std::fill(m_data + m_size, m_data + new_size, 0); // zero-fill new elements
    m_size = new_size;
}

// Clears all elements by setting size to zero (capacity is unchanged)
void MyVector::clear() noexcept {
    m_size = 0;
}

// Private helper reallocates storage to larger capacity and copies existing elements
void MyVector::reallocate(unsigned int new_cap) {
    int* new_data = new int[new_cap]();
    std::copy(m_data, m_data + m_size, new_data);
    delete[] m_data;
    m_data = new_data;
    m_capacity = new_cap;
}
