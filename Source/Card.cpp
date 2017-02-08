#include "Card.hpp"

map<char, int> Card::m_map=
    {
        {'2', 2},
        {'3', 3},
        {'4', 4},
        {'5', 5},
        {'6', 6},
        {'7', 7},
        {'8', 8},
        {'9', 9},
        {'T', 10},
        {'J', 11},
        {'Q', 12},
        {'K', 13},
        {'A', 14}
    };

Card::Card(const string& p_cardVal)
{
    m_value = m_map[p_cardVal[0]];
    m_suit = p_cardVal[1];
}


