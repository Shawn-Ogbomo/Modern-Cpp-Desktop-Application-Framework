#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <iostream>

struct Invalid_card_count : public std::invalid_argument
{
    using std::invalid_argument::invalid_argument;
};

#endif // EXCEPTIONS_HPP