#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <iostream>

class Terminate : public std::runtime_error {
public:
	using std::runtime_error::runtime_error;
};

class Invalid_card_count : public std::invalid_argument {
public:
	using std::invalid_argument::invalid_argument;
};

class Invalid_file : public std::invalid_argument {
public:
	using std::invalid_argument::invalid_argument;
};
#endif //EXCEPTIONS_HPP