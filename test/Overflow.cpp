#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <climits>

#include "SimpleCalculator.h"
#include "InMemoryHistory.h"

using ::testing::StrictMock;

namespace calc::test
{

    class MockHistory : public IHistory
    {
    public:
        MOCK_METHOD(void, AddEntry, (const std::string &operation), (override));
        MOCK_METHOD(std::vector<std::string>, GetLastOperations, (size_t count), (const, override));
    };

    class OverflowTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            calculator = std::make_unique<SimpleCalculator>(mockHistory);
        }

        StrictMock<MockHistory> mockHistory;
        std::unique_ptr<SimpleCalculator> calculator;
    };

    TEST_F(OverflowTest, AdditionOverflow)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Add(INT_MAX, 1));
    }

    TEST_F(OverflowTest, AdditionUnderflow)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Add(INT_MIN, -1));
    }

    TEST_F(OverflowTest, AdditionMaxValues)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Add(INT_MAX, INT_MAX));
    }

    TEST_F(OverflowTest, AdditionMinValues)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Add(INT_MIN, INT_MIN));
    }

    TEST_F(OverflowTest, SubtractionOverflow)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Subtract(INT_MAX, -1));
    }

    TEST_F(OverflowTest, SubtractionUnderflow)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Subtract(INT_MIN, 1));
    }

    TEST_F(OverflowTest, SubtractionMaxFromMin)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Subtract(INT_MIN, INT_MAX));
    }

    TEST_F(OverflowTest, MultiplicationOverflow)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Multiply(INT_MAX, 2));
    }

    TEST_F(OverflowTest, MultiplicationUnderflow)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Multiply(INT_MIN, 2));
    }

    TEST_F(OverflowTest, MultiplicationMaxValues)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Multiply(INT_MAX, INT_MAX));
    }

    TEST_F(OverflowTest, MultiplicationMinValues)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Multiply(INT_MIN, INT_MIN));
    }

    TEST_F(OverflowTest, DivisionMinIntByMinusOne)
    {
        EXPECT_THROW(calculator->Divide(INT_MIN, -1), std::overflow_error);
    }

    TEST_F(OverflowTest, DivisionMaxInt)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Divide(INT_MAX, 2));
    }

    TEST_F(OverflowTest, DivisionMinInt)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Divide(INT_MIN, 2));
    }

}