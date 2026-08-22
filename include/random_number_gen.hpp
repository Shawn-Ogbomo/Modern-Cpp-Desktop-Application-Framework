#ifndef  RANDOM_NUMBER_GEN_HPP
#define  RANDOM_NUMBER_GEN_HPP

#include <random>

struct Random_Number_Gen
{
public:
	Random_Number_Gen() = default;
	static inline std::random_device rd;
	static inline std::mt19937 g{ rd() };
};

#endif // RANDOM_NUMBER_GEN_HPP