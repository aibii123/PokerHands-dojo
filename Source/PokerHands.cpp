#include "PokerHands.hpp"
#include <map>
#include <algorithm>
#include <assert.h>
#include <iostream>
using namespace std;

map<char, int> g_map
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

const int INVALID_VALUE = 0xffff;

Card::Card(const string& p_cardVal)
{
    m_value = g_map[p_cardVal[0]];
    m_suit = p_cardVal[1];
}


int PokerHands::compare(vector<Card> p_cards1, vector<Card> p_cards2)
{
    CardsRank l_c1 = calcRank(p_cards1);
    CardsRank l_c2 = calcRank(p_cards2);

    if (l_c1 == l_c2)
    {
        if (CARDS_RANK_ONE_PAIR == l_c1  or CARDS_RANK_THREE_OF_A_KIND == l_c1)
        {
            auto l_val1 = getTheOnlyOneSameValueInOneHand(p_cards1);
            auto l_val2 = getTheOnlyOneSameValueInOneHand(p_cards2);
            if (l_val1 == l_val2)
            {
				eraseTheSameValuesInTwoHands(l_val1, p_cards1, p_cards2);
                return findTheMaxHand(p_cards1, p_cards2);
            }
            else
            {
                return l_val1 > l_val2 ? 1 : -1;
            }
        }
        else if (CARDS_RANK_TWO_PAIRS == l_c1)
        {
           vector<int> l_pairVals1;
           vector<int> l_pairVals2;
           getPairValsInTwoPairsHand(p_cards1, l_pairVals1);
           getPairValsInTwoPairsHand(p_cards2, l_pairVals2);
           if (l_pairVals1[0] != l_pairVals2[0])
           {
               return l_pairVals1[0] > l_pairVals2[0] ? 1 : -1;
           }
           else if ((l_pairVals1[1])== (l_pairVals2[1]))
           {
           	   eraseTheSameValuesInTwoHands(l_pairVals1[0], p_cards1, p_cards2);
           	   eraseTheSameValuesInTwoHands(l_pairVals1[1], p_cards1, p_cards2);
           	   return p_cards1.begin() -> m_value > p_cards2.begin() -> m_value ? 1 : -1;
           }
           return (l_pairVals1[1]) > (l_pairVals2[1]) ? 1 : -1;
        }
        else if (CARDS_RANK_FULLHOUSE_KIND == l_c1)
        {
           vector<int> l_pairVals1;
           vector<int> l_pairVals2;
           getThreeOfAKindVal(p_cards1, l_pairVals1);
           getThreeOfAKindVal(p_cards2, l_pairVals2);
           if (l_pairVals1[0] != l_pairVals2[0])
           {
               return l_pairVals1[0] > l_pairVals2[0] ? 1 : -1;
           }
           else
           {
               eraseTheSameValuesInTwoHands(l_pairVals1[0], p_cards1, p_cards2);
               return p_cards1.begin() -> m_value > p_cards2.begin() -> m_value ? 1 : -1;
           }
        }
        return findTheMaxHand(p_cards1, p_cards2);
    }

    return l_c1 > l_c2 ? 1 : -1;
}

CardsRank PokerHands::calcRank(vector<Card> p_cards)
{
    CardsRank l_cr = CARDS_RANK_HIGH_CARD;
    if(isFullHouseKind(p_cards))
    {
        l_cr = CARDS_RANK_FULLHOUSE_KIND;
    }
    else if(isFlushKind(p_cards))
    {
        l_cr = CARDS_RANK_FLUSH_KIND;
    }
    else if (isStraightKind(p_cards))
    {
        l_cr = CARDS_RANK_STRAIGHT_KIND;
    }
    else if (isThreeOfAKind(p_cards))
    {
        l_cr = CARDS_RANK_THREE_OF_A_KIND;
    }
    else if (isTwoPairs(p_cards))
    {
        l_cr = CARDS_RANK_TWO_PAIRS;
    }
    else if (isOnePair(p_cards))
    {
        l_cr = CARDS_RANK_ONE_PAIR;
    }

    return l_cr;
}

bool PokerHands::isOnePair(vector<Card> p_cards)
{
    for(auto l_iter = p_cards.begin(); l_iter != p_cards.end(); l_iter++)
    {
       if(2 == count_if(p_cards.begin(),p_cards.end(),
                        [&](Card p){return p.m_value == l_iter->m_value;}))
           return true;
    }
    return false;
}


bool PokerHands::isTwoPairs(vector<Card> p_cards)
{
    sort(p_cards.begin(), p_cards.end(),
         [](auto const p1, auto const p2){return p1.m_value < p2.m_value;});

    int count = 0;
    for(auto l_iter = p_cards.begin(); l_iter != p_cards.end(); l_iter++)
    {
        if(2 == count_if(p_cards.begin(),p_cards.end(),
                        [&](Card p){return p.m_value == l_iter->m_value;}))
        {
            count++;
            l_iter++;
        }
    }

    if (2 == count)
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool PokerHands::isThreeOfAKind(vector<Card> p_cards)
{
    for(auto l_iter = p_cards.begin(); l_iter != p_cards.end(); l_iter++)
    {
       if(3 == count_if(p_cards.begin(),p_cards.end(),
                        [&](Card p){return p.m_value == l_iter->m_value;}))
           return true;
    }
    return false;
}


bool PokerHands::isStraightKind(vector<Card> p_cards)
{
    sort(p_cards.begin(), p_cards.end(), [](auto p1, auto p2) {return p2.m_value < p1.m_value;});
    for(auto l_iter = p_cards.begin(); l_iter != p_cards.end(); l_iter++)
    {
       if(1 < count_if(p_cards.begin(),p_cards.end(),
                        [&](Card p){return p.m_value == l_iter->m_value;}))
       {
           return false;
       }
    }
    if (4 ==  (p_cards.begin() -> m_value - (p_cards.rbegin())-> m_value))
    {
        return true;
    }
    return false;
}


bool PokerHands::isFlushKind(vector<Card> p_cards)
{
    sort(p_cards.begin(), p_cards.end(), [](auto p1, auto p2) {return p2.m_value < p1.m_value;});
    for(auto l_iter = p_cards.begin(); l_iter != p_cards.end(); l_iter++)
    {
       if(5 == count_if(p_cards.begin(),p_cards.end(),
                        [&](Card p){return p.m_suit == l_iter->m_suit;}))
       {
           return true;
       }
    }
    return false;
}


bool PokerHands::isFullHouseKind(vector<Card> p_cards)
{
    sort(p_cards.begin(), p_cards.end(), [](auto p1, auto p2) {return p2.m_value < p1.m_value;});
    bool l_isThreeOfAKind = false;
    bool l_isTwoPair = false;
    for(auto l_iter = p_cards.begin(); l_iter != p_cards.end(); l_iter++)
    {
       if(3 == count_if(p_cards.begin(),p_cards.end(),
                        [&](Card p){return p.m_value == l_iter->m_value;}))
       {
           l_iter+=2;
           l_isThreeOfAKind = true;

       }
       if(2 == count_if(p_cards.begin(),p_cards.end(),
                        [&](Card p){return p.m_value == l_iter->m_value;}))
       {
           l_isTwoPair = true;
           l_iter ++;
       }
    }
    if (l_isTwoPair == true and l_isThreeOfAKind == true)
    {
        return true;
    }

    return false;
}


int PokerHands::getTheOnlyOneSameValueInOneHand(vector<Card> p_cards)
{
    for(auto l_iter = p_cards.begin(); l_iter != p_cards.end(); l_iter++)
    {
       if(1 < count_if(p_cards.begin(),p_cards.end(),
                        [&](Card p){return p.m_value == l_iter->m_value;}))
           return l_iter->m_value;
    }
    return INVALID_VALUE;
}


void PokerHands::getPairValsInTwoPairsHand(vector<Card> p_cards, vector<int>& p_pairVals)
{
   sort(p_cards.begin(), p_cards.end(),
         [](auto const p1, auto const p2){return p2.m_value < p1.m_value;});// in descending order

    for(auto l_iter = p_cards.begin(); l_iter != p_cards.end(); l_iter++)
    {
        if(2 == count_if(p_cards.begin(),p_cards.end(),
                        [&](Card p){return p.m_value == l_iter->m_value;}))
        {
            p_pairVals.push_back(l_iter->m_value);//Appends the given element value to the end of the container,in descending order
            l_iter++;
        }
    }
}

void PokerHands::getThreeOfAKindVal(vector<Card> p_cards, vector<int>& p_pairVals)
{
   sort(p_cards.begin(), p_cards.end(),
         [](auto const p1, auto const p2){return p2.m_value < p1.m_value;});// in descending order

    for(auto l_iter = p_cards.begin(); l_iter != p_cards.end(); l_iter++)
    {
        if(3 == count_if(p_cards.begin(),p_cards.end(),
                        [&](Card p){return p.m_value == l_iter->m_value;}))
        {
            p_pairVals.push_back(l_iter->m_value);//Appends the given element value to the end of the container,in descending order
            l_iter+=2;
        }
    }
}


void PokerHands::getPairValsInFullHouseHand(vector<Card> p_cards, vector<int>& p_pairVals)
{
   sort(p_cards.begin(), p_cards.end(),
         [](auto const p1, auto const p2){return p2.m_value < p1.m_value;});// in descending order

    for(auto l_iter = p_cards.begin(); l_iter != p_cards.end(); l_iter++)
    {
        if(2 == count_if(p_cards.begin(),p_cards.end(),
                        [&](Card p){return p.m_value == l_iter->m_value;}))
        {
            p_pairVals[1] = l_iter->m_value;//Appends the given element value to the end of the container,in descending order
            l_iter++;
        }
        if(3 == count_if(p_cards.begin(),p_cards.end(),
                        [&](Card p){return p.m_value == l_iter->m_value;}))
        {
            p_pairVals[0] = l_iter->m_value;//Appends the given element value to the end of the container,in descending order
            l_iter+=2;
        }
    }
}


void PokerHands::eraseTheSameValuesInTwoHands(int p_val, vector<Card> & p_cards1, vector<Card> & p_cards2)
{
    p_cards1.erase(remove_if(p_cards1.begin(), p_cards1.end(),
        [=](auto p){return p.m_value == p_val;}), p_cards1.end());
    p_cards2.erase(remove_if(p_cards2.begin(), p_cards2.end(),
        [=](auto p){return p.m_value == p_val;}), p_cards2.end());
}


int PokerHands::findTheMaxHand(vector<Card> p_cards1, vector<Card> p_cards2)
{
	  int l_length = p_cards1.size();

	  sort(p_cards1.begin(), p_cards1.end(), [](auto p1, auto p2) {return p2.m_value < p1.m_value;});// in descending order
	  sort(p_cards2.begin(), p_cards2.end(), [](auto p1, auto p2) {return p2.m_value < p1.m_value;});

	  for (int i = 0; i < l_length; i++)
	  {
	      if(p_cards1[i].m_value != p_cards2[i].m_value)
	      {
	          return p_cards1[i].m_value > p_cards2[i].m_value ? 1 : -1;
	      }
	  }

    return INVALID_VALUE;

}