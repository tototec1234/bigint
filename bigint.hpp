#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <sstream>
#include <string>

class bigint {
private:
    std::string _value;

    void            remove_leading_zeros();

public:
    bigint();
    bigint(unsigned long num);
    bigint(const bigint& other);
    ~bigint();

    bigint&         operator=(const bigint& other);

    std::string     str() const;

    bigint          operator+(const bigint& other) const;
    bigint&         operator+=(const bigint& other);

    bigint          operator<<(size_t shift) const;
    bigint&         operator<<=(size_t shift);
    bigint          operator>>(size_t shift) const;
    bigint&         operator>>=(size_t shift);

    bool            operator<(const bigint& other) const;
    bool            operator>(const bigint& other) const;
    bool            operator<=(const bigint& other) const;
    bool            operator>=(const bigint& other) const;
    bool            operator==(const bigint& other) const;
    bool            operator!=(const bigint& other) const;

    bigint&         operator++();
    bigint          operator++(int);
};

std::ostream&   operator<<(std::ostream& os, const bigint& num);

#endif // BIGINT_HPP
