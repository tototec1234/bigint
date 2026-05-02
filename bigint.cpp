#include "bigint.hpp"
#include <algorithm>
#include <sstream>

// Constructor from unsigned long
bigint::bigint(unsigned long num) {
    std::ostringstream oss;
    oss << num;
    value = oss.str();
}

// Remove leading zeros
void bigint::remove_leading_zeros() {
    size_t start = value.find_first_not_of('0');
    if (start == std::string::npos) {
        value = "0";
    } else {
        value = value.substr(start);
    }
}

// Addition operator
bigint bigint::operator+(const bigint& other) const {
    std::string result;
    int carry = 0;
    
    int i = value.length() - 1;
    int j = other.value.length() - 1;
    
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += value[i--] - '0';
        if (j >= 0) sum += other.value[j--] - '0';
        
        result.push_back((sum % 10) + '0');
        carry = sum / 10;
    }
    
    std::reverse(result.begin(), result.end());
    bigint ret;
    ret.value = result;
    return ret;
}

// Left shift (multiply by 10^shift)
bigint bigint::operator<<(size_t shift) const {
    bigint ret;
    ret.value = value;
    ret.value.append(shift, '0');
    return ret;
}

// Right shift (divide by 10^shift)
bigint bigint::operator>>(size_t shift) const {
    if (shift >= value.length()) {
        return bigint(0);
    }
    bigint ret;
    ret.value = value.substr(0, value.length() - shift);
    return ret;
}

// Compound assignment operators
bigint& bigint::operator+=(const bigint& other) {
    *this = *this + other;
    return *this;
}

bigint& bigint::operator<<=(size_t shift) {
    value.append(shift, '0');
    return *this;
}

bigint& bigint::operator>>=(size_t shift) {
    if (shift >= value.length())
        value = "0";
    else
        value = value.substr(0, value.length() - shift);
    return *this;
}

// Comparison operators
bool bigint::operator<(const bigint& other) const {
    if (value.length() != other.value.length())
        return value.length() < other.value.length();
    return value < other.value;
}

bool bigint::operator>(const bigint& other) const { return other < *this; }
bool bigint::operator<=(const bigint& other) const { return !(other < *this); }
bool bigint::operator>=(const bigint& other) const { return !(*this < other); }
bool bigint::operator==(const bigint& other) const { return value == other.value; }
bool bigint::operator!=(const bigint& other) const { return !(*this == other); }

// Increment operators
bigint& bigint::operator++() {
    *this += bigint(1);
    return *this;
}

bigint bigint::operator++(int) {
    bigint temp = *this;
    ++(*this);
    return temp;
}

// Output operator
std::ostream& operator<<(std::ostream& os, const bigint& num) {
    os << num.value;
    return os;
}

/*
c++ -Werror -Wextra -Wall -std=c++98 *.cpp *.hpp
*/