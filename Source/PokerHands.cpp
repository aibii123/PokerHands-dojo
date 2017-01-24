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
            auto l_val1 = getTheSameValuesInOneHand(p_cards1);
            auto l_val2 = getTheSameValuesInOneHand(p_cards2);            
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
        return findHighestVal(p_cards1) > findHighestVal(p_cards2) ? 1 : -1;
    }
    
    return l_c1 > l_c2 ? 1 : -1;
}

CardsRank PokerHands::calcRank(vector<Card> p_cards)
{
    CardsRank l_cr = CARDS_RANK_HIGH_CARD;
    
    if (isThreeOfAKind(p_cards))
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


int PokerHands::findHighestVal(vector<Card> p_cards)
{
    auto l_maxCard = max_element(p_cards.begin(),p_cards.end(),
                       [](auto const p1, auto const p2){return p1.m_value < p2.m_value;});
    
    return l_maxCard->m_value; 
}


int PokerHands::getTheSameValuesInOneHand(vector<Card> p_cards)
{
    for(auto l_iter = p_cards.begin(); l_iter != p_cards.end(); l_iter++)
    {
       if(1 < count_if(p_cards.begin(),p_cards.end(),
                        [&](Card p){return p.m_value == l_iter->m_value;}))
           return l_iter->m_value;
    }
    return INVALID_VALUE;
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
	  
	  sort(p_cards1.begin(), p_cards1.end(), [](auto p1, auto p2) {return p2.m_value < p1.m_value;});
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