#pragma once

#include <string>
#include <vector>

using namespace std;

enum CardsRank
{
    CARDS_RANK_HIGH_CARD = 0,
    CARDS_RANK_ONE_PAIR,
    CARDS_RANK_TWO_PAIRS,
    CARDS_RANK_THREE_OF_A_KIND
};

class Card
{
public:
    Card(const string&);
    
    int m_value;
    char m_suit;   
};

class PokerHands
{
public:
     int compare(vector<Card>, vector<Card>);
private:
     bool isOnePair(vector<Card>);
     bool isTwoPairs(vector<Card>);
     bool isThreeOfAKind(vector<Card> p_cards);
     CardsRank calcRank(vector<Card>);
     int getTheOnlyOneSameValueInOneHand(vector<Card>);
     void getPairValsInTwoPairsHand(vector<Card> p_cards, vector<int>& p_pairVals);
     void eraseTheSameValuesInTwoHands(int p_val, vector<Card> & p_cards1, vector<Card> & p_cards2);
     int findTheMaxHand(vector<Card> p_cards1, vector<Card> p_cards2);
};
