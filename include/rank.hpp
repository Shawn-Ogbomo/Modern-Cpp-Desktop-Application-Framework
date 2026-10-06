#ifndef  RANK_HPP
#define  RANK_HPP

#include <array>

namespace Rank_Lib
{
    enum class Rank
    {
        queen,
        ace,
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
        ten,
        jack,
        king
    };

    inline std::array<Rank, 13> ranks{
    Rank::queen, Rank::ace, Rank::two, Rank::three, Rank::four, Rank::five, Rank::six,
          Rank::seven, Rank::eight, Rank::nine, Rank::ten, Rank::jack, Rank::king };
};

#endif // RANK_HPP