#include "gtest/gtest.h"
#include "SequenceProcessor.hpp"
#include <stdexcept>

using namespace std;

TEST(SequenceProcessorTestSuite, anUnsortedSequenceShouldBeSorted)
{
    vector<int> l_seq = { 1, 8, 7, 99, 94, 76, 22, 42 };
    vector<int> l_seqExpect = { 7, 8, 22, 42, 76, 94, 99, 1 };
    SequenceProcessor::process(l_seq);
    ASSERT_EQ(l_seq, l_seqExpect);
}

TEST(SequenceProcessorTestSuite, duplicatedNumbersShouldBeRemoved)
{
    vector<int> l_seq = { 1, 8, 1, 99, 94, 8, 42, 42 };
    vector<int> l_seqExpect = { 8, 42, 94, 99, 1 };
    SequenceProcessor::process(l_seq);
    ASSERT_EQ(l_seq, l_seqExpect);
}

TEST(SequenceProcessorTestSuite, allNumbersCannotBeDevidedBy5ShouldBePlacedBack)
{
    vector<int> l_seq = { 5, 8, 0, 100, 95, 8, 45, 45 };
    vector<int> l_seqExpect = { 5, 45, 95, 100, 8, 0 };
    SequenceProcessor::process(l_seq);
    ASSERT_EQ(l_seq, l_seqExpect);
}

TEST(SequenceProcessorTestSuite, 2LastNumbersDivededBy5ShouldbeExchangedWithNext2Numbers)
{
    vector<int> l_seq = { 5, 8, 0, 100, 95, 15, 42, 42 };
    vector<int> l_seqExpect = { 5, 15, 42, 8, 100, 95, 0};
    SequenceProcessor::process(l_seq);
    ASSERT_EQ(l_seq, l_seqExpect);
}

TEST(SequenceProcessorTestSuite, allNumbersBeforeThe1stNumberBiggerThan1stNumberShouldBePutBack)
{
    vector<int> l_seq = { 5, 8, 0, 100, 95, 15, 42, 42 };
    vector<int> l_seqExpect = { 5, 15, 42, 8, 100, 95, 0};
    SequenceProcessor::process(l_seq);
    ASSERT_EQ(l_seq, l_seqExpect);
}

TEST(SequenceProcessorTestSuite, invalidSeqSizeShouldThrowException)
{
    vector<int> l_seq = { 5, 8, 0, 100, 95, 15, 42 };

    EXPECT_THROW(SequenceProcessor::process(l_seq), length_error);
}

TEST(SequenceProcessorTestSuite, numberOutOfRangeShouldThrowException)
{
    vector<int> l_seq = { 5, 8, 0, 2345, 95, 4567, -90, 100 };

    EXPECT_THROW(SequenceProcessor::process(l_seq), out_of_range);
}

