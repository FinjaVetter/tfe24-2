#ifndef MY_VECTOR_HPP
#define MY_VECTOR_HPP

#include <cstddef>
#include <stdexcept>

class MyVector {
public:
    MyVector();
    MyVector(unsigned int size);
    MyVector(const MyVector& other); // Copy-Konstruktor
    MyVector& operator=(const MyVector& other); // Copy-Zuweisung
    ~MyVector();

    void push_back(int value);
    int& at(size_t index);
    const int& at(size_t index) const;

    int& operator[](size_t index) { return m_data[index]; }
    const int& operator[](size_t index) const { return m_data[index]; }

    unsigned int size() const noexcept;
    unsigned int capacity() const noexcept;
    void reserve(unsigned int new_cap);
    void resize(unsigned int new_size);
    void clear() noexcept;

private:
    void reallocate(unsigned int new_cap);

    int* m_data;
    unsigned int m_size;
    unsigned int m_capacity;
};
#endif /* MY_VECTOR_HPP */
