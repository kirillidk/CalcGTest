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

    class BoundaryValueTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            calculator = std::make_unique<SimpleCalculator>(mockHistory);
        }

        StrictMock<MockHistory> mockHistory;
        std::unique_ptr<SimpleCalculator> calculator;
    };

    TEST_F(BoundaryValueTest, AdditionOverflow)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Add(INT_MAX, 1));
    }

    TEST_F(BoundaryValueTest, AdditionUnderflow)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Add(INT_MIN, -1));
    }

    TEST_F(BoundaryValueTest, AdditionMaxValues)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Add(INT_MAX, INT_MAX));
    }

    TEST_F(BoundaryValueTest, AdditionMinValues)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Add(INT_MIN, INT_MIN));
    }

    TEST_F(BoundaryValueTest, SubtractionOverflow)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Subtract(INT_MAX, -1));
    }

    TEST_F(BoundaryValueTest, SubtractionUnderflow)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Subtract(INT_MIN, 1));
    }

    TEST_F(BoundaryValueTest, SubtractionMaxFromMin)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Subtract(INT_MIN, INT_MAX));
    }

    TEST_F(BoundaryValueTest, MultiplicationOverflow)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Multiply(INT_MAX, 2));
    }

    TEST_F(BoundaryValueTest, MultiplicationUnderflow)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Multiply(INT_MIN, 2));
    }

    TEST_F(BoundaryValueTest, MultiplicationMaxValues)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Multiply(INT_MAX, INT_MAX));
    }

    TEST_F(BoundaryValueTest, MultiplicationMinValues)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Multiply(INT_MIN, INT_MIN));
    }

    TEST_F(BoundaryValueTest, DivisionByZero)
    {
        EXPECT_THROW(calculator->Divide(5, 0), std::invalid_argument);
    }

    TEST_F(BoundaryValueTest, DivisionMinIntByMinusOne)
    {
        EXPECT_THROW(calculator->Divide(INT_MIN, -1), std::overflow_error);
    }

    TEST_F(BoundaryValueTest, DivisionMaxInt)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Divide(INT_MAX, 2));
    }

    TEST_F(BoundaryValueTest, DivisionMinInt)
    {
        EXPECT_CALL(mockHistory, AddEntry(testing::_)).Times(1);
        EXPECT_NO_THROW(calculator->Divide(INT_MIN, 2));
    }

}