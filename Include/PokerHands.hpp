#pragma once

#include "Card.hpp"
#include <vector>

using namespace std;

enum CardsRank
{
    CARDS_RANK_HIGH_CARD = 0,
    CARDS_RANK_ONE_PAIR,
    CARDS_RANK_TWO_PAIRS,
    CARDS_RANK_THREE_OF_A_KIND,
    CARDS_RANK_STRAIGHT_KIND,
    CARDS_RANK_FLUSH_KIND,
    CARDS_RANK_FULLHOUSE_KIND
};


class PokerHands
{
public:
     int compare(vector<Card>, vector<Card>);
private:
     bool isOnePair(vector<Card>);
     bool isTwoPairs(vector<Card>);
     bool isThreeOfAKind(vector<Card> p_cards);
     bool isFlushKind(vector<Card> p_cards);
     bool isStraightKind(vector<Card> p_cards);
     bool isFullHouseKind(vector<Card> p_cards);
     CardsRank calcRank(vector<Card>);
     void getPairVals(vector<Card> p_cards, vector<int>& p_pairVals);
     void eraseValuesInTwoHands(vector<int> p_erasedvals, vector<Card> & p_cards1, vector<Card> & p_cards2);
     int findTheMaxHand(vector<Card> p_cards1, vector<Card> p_cards2);
};
