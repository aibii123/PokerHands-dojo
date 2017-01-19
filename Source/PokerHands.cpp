#include "PokerHands.hpp"
#include <map>
#include <algorithm>

map<char, int> g_map 
{
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 9},
    {'T', 10},
    {'J', 11},
    {'Q', 12},
    {'K', 13},
    {'A', 14}
};

Card::Card(const string& p_cardVal)
{
    m_value = g_map[p_cardVal[0]];
    m_suit = p_cardVal[1];
}

int compare(vector<Card> p_cards1, vector<Card> p_cards2)
{
    if(isOnePair(p_cards1) and (not isOnePair(p_cards2)))
    {
        return 1;
    }
    else if( (not isOnePair(p_cards1)) and isOnePair(p_cards2))
    {
        return -1;
    }
}

#if 1
bool isHighCard(vector<Card> cards)
{
    
}

bool isOnePair(vector<Card> p_cards)
{
    for(auto l_iter = p_cards.begin(); l_iter != p_cards.end(); l_iter++)
    {
       if(2 == count_if(p_cards.begin(),p_cards.end(),
                        [&](Card p){return p.m_value == l_iter->m_value;}))
           return true;
    }
    return false;
}
#endif

