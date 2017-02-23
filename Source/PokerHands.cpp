#include "PokerHands.hpp"
#include <algorithm>
#include <assert.h>
#include <iostream>
using namespace std;

const int INVALID_VALUE = 0xffff;

int PokerHands::compare(vector<Card> p_cards1, vector<Card> p_cards2)
{
    CardsRank l_c1 = calcRank(p_cards1);
    CardsRank l_c2 = calcRank(p_cards2);

    if (l_c1 == l_c2)
    {
        vector<int> l_pairVals1;
        vector<int> l_pairVals2;
        if (CARDS_RANK_ONE_PAIR == l_c1  or
            CARDS_RANK_THREE_OF_A_KIND == l_c1 or
            CARDS_RANK_TWO_PAIRS == l_c1 or
            CARDS_RANK_FULLHOUSE_KIND == l_c1 or CARDS_RANK_FOUR_OF_A_KIND == l_c1)
        {
            getSameVals(p_cards1, l_pairVals1);
            getSameVals(p_cards2, l_pairVals2);
//        if (true == l_hasSameVals)
//        {
            if (l_pairVals1[0] != l_pairVals2[0])
            {
                return l_pairVals1[0] > l_pairVals2[0] ? 1 : -1;
            }
            else if((CARDS_RANK_ONE_PAIR == l_c1  or CARDS_RANK_THREE_OF_A_KIND == l_c1 or CARDS_RANK_FOUR_OF_A_KIND == l_c1)
                     and l_pairVals1[0] == l_pairVals2[0])
            {
                eraseValuesInTwoHands(l_pairVals1, p_cards1, p_cards2);
            }
            else if(CARDS_RANK_TWO_PAIRS == l_c1 and l_pairVals1== l_pairVals2)
            {
                eraseValuesInTwoHands(l_pairVals1, p_cards1, p_cards2);
                return p_cards1.begin() -> m_value > p_cards2.begin() -> m_value ? 1 : -1;
            }
            else
            {
               return l_pairVals1[1] > l_pairVals2[1] ? 1 : -1;
            }
        }
        return findTheMaxHand(p_cards1, p_cards2);
    }

    return l_c1 > l_c2 ? 1 : -1;
}

CardsRank PokerHands::calcRank(vector<Card> p_cards)
{
    CardsRank l_cr = CARDS_RANK_HIGH_CARD;
    if(isStraightFlushKind(p_cards))
    {
        l_cr = CARDS_RANK_STRAIGHT_FLUSH_KIND;
    }
    else if (isFourOfAKind(p_cards))
    {
        l_cr = CARDS_RANK_FOUR_OF_A_KIND;
    }
    else if (isFullHouseKind(p_cards))
    {
        l_cr = CARDS_RANK_FULLHOUSE_KIND;
    }
    else if (isFlushKind(p_cards))
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
//    for(auto l_iter = p_cards.begin(); l_iter != p_cards.end(); l_iter++)
//    {
//       if(1 < count_if(p_cards.begin(),p_cards.end(),
//                        [&](Card p){return p.m_value == l_iter->m_value;}))
//       {
//           return false;
//       }
//    }
    auto l_result = adjacent_find(p_cards.begin(),p_cards.end(),[](auto p1, auto p2) {return p2.m_value != (p1.m_value - 1);});
    return l_result == p_cards.end();
//    if (4 ==  (p_cards.begin() -> m_value - (p_cards.rbegin())->m_value))
//    {
//        return true;
//    }
//    return false;
}


bool PokerHands::isFlushKind(vector<Card> p_cards)
{
    sort(p_cards.begin(), p_cards.end(), [](auto p1, auto p2) {return p2.m_value < p1.m_value;});
//    for(auto l_iter = p_cards.begin(); l_iter != p_cards.end(); l_iter++)
//    {
//       if(5 == count_if(p_cards.begin(),p_cards.end(),
//                        [&](Card p){return p.m_suit == l_iter->m_suit;}))
//       {
//           return true;
//       }
//    }
    auto l_result = adjacent_find(p_cards.begin(),p_cards.end(),[](auto p1, auto p2) {return p2.m_suit != p1.m_suit;});
    return l_result == p_cards.end();

//    return false;
}


bool PokerHands::isFourOfAKind(vector<Card> p_cards)
{
    for(auto l_iter = p_cards.begin(); l_iter != next( p_cards.begin(),2) ; l_iter++)
    {
       if(4 == count_if(p_cards.begin(),p_cards.end(),
                        [&](Card p){return p.m_value == l_iter->m_value;}))
           return true;
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


bool PokerHands::isStraightFlushKind(vector<Card> p_cards)
{
    if (isStraightKind(p_cards) and isFlushKind(p_cards))
    {
        return true;
    }
    return false;
}


void PokerHands::getSameVals(vector<Card> p_cards, vector<int>& p_pairVals)
{
    sort(p_cards.begin(), p_cards.end(),
        [](auto const p1, auto const p2){return p2.m_value < p1.m_value;});// in descending order

    for(auto l_iter = p_cards.begin(); l_iter != p_cards.end(); l_iter++)
    {
        int l_numVals = count_if(p_cards.begin(),p_cards.end(),
                        [&](Card p){return p.m_value == l_iter->m_value;});
        if(l_numVals > 1)
        {
            if(l_numVals == 3)//mark may wrong
            {
                p_pairVals.insert(p_pairVals.begin(),l_iter->m_value);
            }
            else
            {
                p_pairVals.push_back(l_iter->m_value);//Appends the given element value to the end of the container,in descending order
            }

            l_iter+=(l_numVals-1);
        }
    }
//    if (p_pairVals.size() != 0)
//    {
//        return true;
//    }
//    return false;

}

void PokerHands::eraseValuesInTwoHands(vector<int> p_erasedvals, vector<Card> & p_cards1, vector<Card> & p_cards2)
{
    for (int l_val : p_erasedvals)
    {
        p_cards1.erase(remove_if(p_cards1.begin(), p_cards1.end(),
            [=](auto p){return p.m_value == l_val;}), p_cards1.end());
        p_cards2.erase(remove_if(p_cards2.begin(), p_cards2.end(),
            [=](auto p){return p.m_value == l_val;}), p_cards2.end());
    }
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


