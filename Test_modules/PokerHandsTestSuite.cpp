#include "gtest/gtest.h"
#include "PokerHands.hpp"

class PokerHandsTestSuite : public ::testing::Test
{
public:
    vector<Card> m_hand1;
    vector<Card> m_hand2;
    PokerHands   m_pokerhands;
};

TEST_F(PokerHandsTestSuite, onePairShouldWinHighCard)
{
    m_hand1 = {string("5H"), string("6C"), string("7S"), string("8D"), string("TH")};
    m_hand2 = {string("5H"), string("5C"), string("7S"), string("8D"), string("TH")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, twoPairsShouldWinOnePair)
{
    m_hand1 = {string("5H"), string("5C"), string("7S"), string("7D"), string("TH")};
    m_hand2 = {string("5H"), string("5C"), string("7S"), string("8D"), string("TH")};

    ASSERT_EQ(1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(-1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, oneHighCardWithHighestValueShouldWinTheOtherHighCard)
{
    m_hand1 = {string("QH"), string("4C"), string("7S"), string("8D"), string("TH")};
    m_hand2 = {string("QH"), string("5C"), string("7S"), string("8D"), string("TH")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, onePairCardWithHighestValueShouldWinOnePairWithLessValue)
{
    m_hand1 = {string("5H"), string("5C"), string("7S"), string("8D"), string("TH")};
    m_hand2 = {string("QH"), string("7C"), string("7S"), string("8D"), string("TH")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, theHandWithHighestValueShouldWinInTwoHandsWithOneSamePair)
{
    m_hand1 = {string("5H"), string("5C"), string("7S"), string("8D"), string("TH")};
    m_hand2 = {string("QH"), string("5C"), string("5S"), string("8D"), string("TH")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, theHandWithSecondHigherValueShouldWinInTwoHandsWithOneSamePairAndSameHighestValue)
{
    m_hand1 = {string("5H"), string("5C"), string("7S"), string("8D"), string("QH")};
    m_hand2 = {string("QH"), string("5C"), string("5S"), string("8D"), string("TH")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, theOnePairHandWithHigherSmallestValueShouldWinInTwoHandsWithOneSamePairAndOtherValuesSameExceptSmallestValue)
{
    m_hand1 = {string("5H"), string("5C"), string("7S"), string("8D"), string("QH")};
    m_hand2 = {string("QH"), string("5C"), string("5S"), string("8D"), string("TH")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, TwoPairsHandWithHigherPairValShouldWinTheOtherTwoPairsHand)
{
    m_hand1 = {string("5H"), string("5C"), string("7S"), string("7D"), string("QH")};
    m_hand2 = {string("TH"), string("TC"), string("7S"), string("7D"), string("QH")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, TwoPairsHandWithHigherPairValShouldWinTheOtherTwoPairsHandWithOneSamePair)
{
    m_hand1 = {string("5H"), string("5C"), string("7S"), string("7D"), string("QH")};
    m_hand2 = {string("4H"), string("4C"), string("7S"), string("7D"), string("QH")};

    ASSERT_EQ(1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(-1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, TwoPairsHandWithHigherValShouldWinTheOtherTwoPairsHandWithSamePairs)
{
    m_hand1 = {string("5H"), string("5C"), string("7S"), string("7D"), string("QH")};
    m_hand2 = {string("5H"), string("5C"), string("7S"), string("7D"), string("1H")};

    ASSERT_EQ(1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(-1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, ThreeOfAkindHandShouldWinTwoPairHand)
{
    m_hand1 = {string("5H"), string("5C"), string("5S"), string("7D"), string("QH")};
    m_hand2 = {string("5H"), string("5C"), string("7S"), string("7D"), string("1H")};

    ASSERT_EQ(1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(-1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, ThreeOfAKindHandWithHighestValueShouldWinThreeOfAKindWithSmallerValue)
{
    m_hand1 = {string("5H"), string("5C"), string("5S"), string("8D"), string("QH")};
    m_hand2 = {string("6H"), string("6C"), string("6S"), string("8D"), string("TH")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, ThreeOfAKindHandWithHigherValueShouldWinSameThreeOfAKind)
{
    m_hand1 = {string("6H"), string("6C"), string("6S"), string("8D"), string("QH")};
    m_hand2 = {string("6H"), string("6C"), string("6S"), string("8D"), string("TH")};

    ASSERT_EQ(1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(-1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, ThreeOfAKindHandWithHigherValueShouldWinSameThreeOfAKindAndSameOneHigherValue)
{
    m_hand1 = {string("6H"), string("6C"), string("6S"), string("8D"), string("QH")};
    m_hand2 = {string("6H"), string("6C"), string("6S"), string("7D"), string("QH")};

    ASSERT_EQ(1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(-1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, StraightHandShouldWinThreeOfAKindHand)
{
    m_hand1 = {string("5H"), string("6C"), string("7S"), string("8D"), string("9H")};
    m_hand2 = {string("6H"), string("6C"), string("6S"), string("7D"), string("QH")};

    ASSERT_EQ(1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(-1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, StraightHandWithHigherValShouldWinTheOtherStraightHand)
{
    m_hand1 = {string("5H"), string("6C"), string("7S"), string("8D"), string("9H")};
    m_hand2 = {string("6H"), string("7C"), string("8S"), string("9D"), string("TH")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, FlushHandShouldWinStraightHand)
{
    m_hand1 = {string("5H"), string("6C"), string("7S"), string("8D"), string("9H")};
    m_hand2 = {string("6H"), string("6H"), string("6H"), string("7H"), string("QH")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, FlushHandWitheHigherValShouldWinTheOtherFlushHand)
{
    m_hand1 = {string("5C"), string("6C"), string("TC"), string("8C"), string("9C")};
    m_hand2 = {string("6H"), string("6H"), string("6H"), string("7H"), string("QH")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, FullHouseHandShouldWinFlushHand)
{
    m_hand1 = {string("5H"), string("5C"), string("5S"), string("8D"), string("8H")};
    m_hand2 = {string("6H"), string("6H"), string("6H"), string("7H"), string("QH")};

    ASSERT_EQ(1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(-1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, FullHouseHandWithHigherValShouldWinTheOtherFullHouseHand)
{
    m_hand1 = {string("5H"), string("5C"), string("5S"), string("8D"), string("8H")};
    m_hand2 = {string("6H"), string("6H"), string("6H"), string("4H"), string("4H")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, FourOfAKindHandShouldWinFullHouseHand)
{
    m_hand1 = {string("5H"), string("5C"), string("5S"), string("8D"), string("8H")};
    m_hand2 = {string("6H"), string("6H"), string("6H"), string("6H"), string("4C")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, FourOfAKindHandWithHigherPairValShouldWinTheOtherFourOfAKindHand)
{
    m_hand1 = {string("5H"), string("5C"), string("5S"), string("5D"), string("8D")};
    m_hand2 = {string("6H"), string("6H"), string("6H"), string("6H"), string("4C")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, FourOfAKindHandWithHigherHardValShouldWinTheOtherFourOfAKindHandWithTheSamePairVals)
{
    m_hand1 = {string("6H"), string("6C"), string("6S"), string("6D"), string("8D")};
    m_hand2 = {string("6H"), string("6H"), string("6H"), string("6H"), string("4C")};

    ASSERT_EQ(1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(-1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, StraightFlushHandShouldWinFourOfAKindHand)
{
    m_hand1 = {string("6H"), string("7H"), string("8H"), string("9H"), string("TH")};
    m_hand2 = {string("6H"), string("6H"), string("6H"), string("6H"), string("4C")};

    ASSERT_EQ(1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(-1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, StraightFlushHandWithHigherValShouldWinTheOtherStraightFlushHand)
{
    m_hand1 = {string("6H"), string("7H"), string("8H"), string("9H"), string("TH")};
    m_hand2 = {string("7H"), string("8H"), string("9H"), string("TH"), string("JH")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1, m_pokerhands.compare(m_hand2, m_hand1));
}

