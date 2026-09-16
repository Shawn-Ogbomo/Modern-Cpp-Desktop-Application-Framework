#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <iostream>

class Invalid_card_count : public std::invalid_argument
{
public:
    using std::invalid_argument::invalid_argument;
};

#endif // EXCEPTIONS_HPP