#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <sstream>
#include <string>

class bigint {
private:
    std::string value;
    
    void remove_leading_zeros();

public:
    // Constructors
    bigint() : value("0") {}
    bigint(unsigned long num);
    bigint(const bigint& other) : value(other.value) {}
    
    // Assignment operator
    bigint& operator=(const bigint& other) {
        if (this != &other)
            value = other.value;
        return *this;
    }

    // Arithmetic operators
    bigint  operator+(const bigint& other) const;
    bigint& operator+=(const bigint& other);

    // Digit shift operators (base 10)
    bigint  operator<<(size_t shift) const;
    bigint& operator<<=(size_t shift);
    bigint  operator>>(size_t shift) const;
    bigint& operator>>=(size_t shift);

    // Comparison operators
    bool operator<(const bigint& other) const;
    bool operator>(const bigint& other) const;
    bool operator<=(const bigint& other) const;
    bool operator>=(const bigint& other) const;
    bool operator==(const bigint& other) const;
    bool operator!=(const bigint& other) const;

    // Increment operators
    bigint& operator++();
    bigint  operator++(int);

    // Output operator (no leading zeros)
    friend std::ostream& operator<<(std::ostream& os, const bigint& num);
};

#endif // BIGINT_HPP
