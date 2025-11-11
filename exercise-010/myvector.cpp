#include "myvector.hpp"
#include <fmt/format.h>
#include <algorithm>

// Default-Konstruktor
MyVector::MyVector() : m_data(nullptr), m_size(0), m_capacity(0) {
    fmt::println("[MyVector] welcome to the CTOR!");
}

// Size-Konstruktor
MyVector::MyVector(unsigned int size)
    : m_data(size ? new int[size]() : nullptr), m_size(size), m_capacity(size)
{
    fmt::println("[MyVector] welcome to the size CTOR!");
}

// Copy-Konstruktor
MyVector::MyVector(const MyVector& other)
    : m_data(other.m_capacity ? new int[other.m_capacity]() : nullptr),
      m_size(other.m_size), m_capacity(other.m_capacity)
{
    fmt::println("[MyVector] copy CTOR");
    std::copy(other.m_data, other.m_data + m_size, m_data);
}

// Copy-Assignment
MyVector& MyVector::operator=(const MyVector& other) {
    if (this != &other) {
        delete[] m_data;
        m_capacity = other.m_capacity;
        m_size = other.m_size;
        m_data = other.m_capacity ? new int[other.m_capacity]() : nullptr;
        std::copy(other.m_data, other.m_data + m_size, m_data);
    }
    fmt::println("[MyVector] copy assignment");
    return *this;
}

// Destruktor
MyVector::~MyVector() {
    fmt::println("[MyVector] welcome to the DTOR!");
    delete[] m_data;
}

// push_back: adds value at end, resizes if needed
void MyVector::push_back(int value) {
    if (m_size == m_capacity) {
        reserve(m_capacity ? m_capacity * 2 : 1);
    }
    m_data[m_size++] = value;
}

// at: mit Bereichsprüfung
int& MyVector::at(size_t index) {
    if(index >= m_size) throw std::out_of_range("MyVector::at");
    return m_data[index];
}
const int& MyVector::at(size_t index) const {
    if(index >= m_size) throw std::out_of_range("MyVector::at");
    return m_data[index];
}

// size
unsigned int MyVector::size() const noexcept { return m_size; }

// capacity
unsigned int MyVector::capacity() const noexcept { return m_capacity; }

// reserve
void MyVector::reserve(unsigned int new_cap) {
    if (new_cap > m_capacity)
        reallocate(new_cap);
}

// resize
void MyVector::resize(unsigned int new_size) {
    if (new_size > m_capacity)
        reserve(new_size);
    if (new_size > m_size)
        std::fill(m_data + m_size, m_data + new_size, 0);
    m_size = new_size;
}

// clear
void MyVector::clear() noexcept {
    m_size = 0;
}

// reallociert auf größere Kapazität
void MyVector::reallocate(unsigned int new_cap) {
    int* new_data = new int[new_cap]();
    std::copy(m_data, m_data + m_size, new_data);
    delete[] m_data;
    m_data = new_data;
    m_capacity = new_cap;
}
