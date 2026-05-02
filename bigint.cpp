#include "bigint.hpp"
#include <sstream>

// Constructors / Destructor
bigint::bigint() : _value("0") {}

bigint::bigint(unsigned long num) {
    std::ostringstream oss;
    oss << num;
    _value = oss.str();
}

bigint::bigint(const bigint& other) : _value(other._value) {}

bigint::~bigint() {}

// Assignment operator
bigint& bigint::operator=(const bigint& other) {
    if (this != &other)
        _value = other._value;
    return *this;
}

// Public accessor
std::string bigint::str() const {
    return _value;
}

// Remove leading zeros
void bigint::remove_leading_zeros() {
    size_t start = _value.find_first_not_of('0');
    if (start == std::string::npos)
        _value = "0";
    else
        _value = _value.substr(start);
}

// Addition operator
bigint bigint::operator+(const bigint& other) const {
    std::string result;
    int carry = 0;

    int i = _value.length() - 1;
    int j = other._value.length() - 1;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += _value[i--] - '0';
        if (j >= 0) sum += other._value[j--] - '0';
        result.push_back((sum % 10) + '0');
        carry = sum / 10;
    }

    // reverse manually (std::reverse from <algorithm> is forbidden)
    int left = 0;
    int right = (int)result.length() - 1;
    while (left < right) {
        char tmp = result[left];
        result[left++] = result[right];
        result[right--] = tmp;
    }

    bigint ret;
    ret._value = result;
    return ret;
}

// Left shift (multiply by 10^shift)
bigint bigint::operator<<(size_t shift) const {
    bigint ret;
    ret._value = _value;
    ret._value.append(shift, '0');
    return ret;
}

// Right shift (divide by 10^shift)
bigint bigint::operator>>(size_t shift) const {
    if (shift >= _value.length())
        return bigint(0UL);
    bigint ret;
    ret._value = _value.substr(0, _value.length() - shift);
    return ret;
}

// Compound assignment operators
bigint& bigint::operator+=(const bigint& other) {
    *this = *this + other;
    return *this;
}

bigint& bigint::operator<<=(size_t shift) {
    _value.append(shift, '0');
    return *this;
}

bigint& bigint::operator>>=(size_t shift) {
    if (shift >= _value.length())
        _value = "0";
    else
        _value = _value.substr(0, _value.length() - shift);
    return *this;
}

// Comparison operators
bool bigint::operator<(const bigint& other) const {
    if (_value.length() != other._value.length())
        return _value.length() < other._value.length();
    return _value < other._value;
}

bool bigint::operator>(const bigint& other) const  { return other < *this; }
bool bigint::operator<=(const bigint& other) const { return !(other < *this); }
bool bigint::operator>=(const bigint& other) const { return !(*this < other); }
bool bigint::operator==(const bigint& other) const { return _value == other._value; }
bool bigint::operator!=(const bigint& other) const { return !(*this == other); }

// Increment operators
bigint& bigint::operator++() {
    *this += bigint(1UL);
    return *this;
}

bigint bigint::operator++(int) {
    bigint temp = *this;
    ++(*this);
    return temp;
}

// Output operator (non-friend non-member)
std::ostream& operator<<(std::ostream& os, const bigint& num) {
    os << num.str();
    return os;
}

/*
c++ -Werror -Wextra -Wall -std=c++98 -pedantic-errors *.cpp *.hpp
*/
