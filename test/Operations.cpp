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

    class OperationsTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            calculator = std::make_unique<SimpleCalculator>(mockHistory);
        }

        StrictMock<MockHistory> mockHistory;
        std::unique_ptr<SimpleCalculator> calculator;
    };

    TEST_F(OperationsTest, DivisionByZero)
    {
        EXPECT_THROW(calculator->Divide(5, 0), std::invalid_argument);
    }

    TEST_F(OperationsTest, IntegerDivisionTruncation)
    {
        EXPECT_CALL(mockHistory, AddEntry("7 / 3 = 2")).Times(1);
        EXPECT_EQ(calculator->Divide(7, 3), 2);
    }

    TEST_F(OperationsTest, IntegerDivisionNegativeTruncation)
    {
        EXPECT_CALL(mockHistory, AddEntry("-7 / 3 = -2")).Times(1);
        EXPECT_EQ(calculator->Divide(-7, 3), -2);
    }

    TEST_F(OperationsTest, IntegerDivisionNegativeBothTruncation)
    {
        EXPECT_CALL(mockHistory, AddEntry("-7 / -3 = 2")).Times(1);
        EXPECT_EQ(calculator->Divide(-7, -3), 2);
    }

    TEST_F(OperationsTest, OperationsWithZero)
    {
        EXPECT_CALL(mockHistory, AddEntry("0 + 0 = 0")).Times(1);
        EXPECT_EQ(calculator->Add(0, 0), 0);
    }

    TEST_F(OperationsTest, MultiplyByZero)
    {
        EXPECT_CALL(mockHistory, AddEntry("100 * 0 = 0")).Times(1);
        EXPECT_EQ(calculator->Multiply(100, 0), 0);
    }

    TEST_F(OperationsTest, DivideByOne)
    {
        EXPECT_CALL(mockHistory, AddEntry("42 / 1 = 42")).Times(1);
        EXPECT_EQ(calculator->Divide(42, 1), 42);
    }

    TEST_F(OperationsTest, DivideZeroByNonZero)
    {
        EXPECT_CALL(mockHistory, AddEntry("0 / 5 = 0")).Times(1);
        EXPECT_EQ(calculator->Divide(0, 5), 0);
    }
}