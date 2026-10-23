#ifndef  RANDOM_NUMBER_GEN_HPP
#define  RANDOM_NUMBER_GEN_HPP

#include <random>

struct Random_Number_Gen
{
public:
    Random_Number_Gen(int min = 0, int max = 51) : dst{min,max}
    {
        std::generate(std::begin(seed_data), std::end(seed_data),
            std::ref(rd));

        std::seed_seq seq(std::begin(seed_data), std::end(seed_data));

        g = std::mt19937{ seq };
    }

    std::random_device rd;
    std::mt19937 g{ };
    std::uniform_int_distribution<> dst{};
    std::array<int, std::mt19937::state_size> seed_data{};
};
#endif // RANDOM_NUMBER_GEN_HPP