#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "SimpleCalculator.h"
#include "InMemoryHistory.h"

using ::testing::_;
using ::testing::InSequence;
using ::testing::Return;
using ::testing::StrictMock;

namespace calc::test
{

    class MockHistory : public IHistory
    {
    public:
        MOCK_METHOD(void, AddEntry, (const std::string &operation), (override));
        MOCK_METHOD(std::vector<std::string>, GetLastOperations, (size_t count), (const, override));
    };

    class MockCalculator : public ICalculator
    {
    public:
        MOCK_METHOD(int, Add, (int a, int b), (override));
        MOCK_METHOD(int, Subtract, (int a, int b), (override));
        MOCK_METHOD(int, Multiply, (int a, int b), (override));
        MOCK_METHOD(int, Divide, (int a, int b), (override));
        MOCK_METHOD(void, SetHistory, (IHistory & history), (override));
    };

    class CalculatorWithMockHistoryTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            calculator = std::make_unique<SimpleCalculator>(mockHistory);
        }

        StrictMock<MockHistory> mockHistory;
        std::unique_ptr<SimpleCalculator> calculator;
    };

    class MockCalculatorWithRealHistoryTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            realHistory = std::make_unique<InMemoryHistory>();
        }

        StrictMock<MockCalculator> mockCalculator;
        std::unique_ptr<InMemoryHistory> realHistory;
    };

    TEST_F(CalculatorWithMockHistoryTest, AddOperationLogsToHistory)
    {
        EXPECT_CALL(mockHistory, AddEntry("2 + 3 = 5")).Times(1);
        int result = calculator->Add(2, 3);
        EXPECT_EQ(result, 5);
    }

    TEST_F(CalculatorWithMockHistoryTest, SubtractOperationLogsToHistory)
    {
        EXPECT_CALL(mockHistory, AddEntry("10 - 3 = 7")).Times(1);
        int result = calculator->Subtract(10, 3);
        EXPECT_EQ(result, 7);
    }

    TEST_F(CalculatorWithMockHistoryTest, MultiplyOperationLogsToHistory)
    {
        EXPECT_CALL(mockHistory, AddEntry("4 * 5 = 20")).Times(1);
        int result = calculator->Multiply(4, 5);
        EXPECT_EQ(result, 20);
    }

    TEST_F(CalculatorWithMockHistoryTest, DivideOperationLogsToHistory)
    {
        EXPECT_CALL(mockHistory, AddEntry("15 / 3 = 5")).Times(1);
        int result = calculator->Divide(15, 3);
        EXPECT_EQ(result, 5);
    }

    TEST_F(CalculatorWithMockHistoryTest, MultipleOperationsLogInOrder)
    {
        InSequence seq;
        EXPECT_CALL(mockHistory, AddEntry("2 + 3 = 5"));
        EXPECT_CALL(mockHistory, AddEntry("10 - 4 = 6"));
        EXPECT_CALL(mockHistory, AddEntry("5 * 2 = 10"));
        calculator->Add(2, 3);
        calculator->Subtract(10, 4);
        calculator->Multiply(5, 2);
    }

    TEST_F(CalculatorWithMockHistoryTest, NegativeNumbersAreLoggedCorrectly)
    {
        EXPECT_CALL(mockHistory, AddEntry("-5 + 3 = -2")).Times(1);
        int result = calculator->Add(-5, 3);
        EXPECT_EQ(result, -2);
    }

    TEST_F(CalculatorWithMockHistoryTest, ZeroValuesAreLoggedCorrectly)
    {
        EXPECT_CALL(mockHistory, AddEntry("0 * 100 = 0")).Times(1);
        int result = calculator->Multiply(0, 100);
        EXPECT_EQ(result, 0);
    }

    TEST_F(MockCalculatorWithRealHistoryTest, SetHistoryCallsCorrectMethod)
    {
        EXPECT_CALL(mockCalculator, SetHistory(testing::Ref(*realHistory))).Times(1);
        mockCalculator.SetHistory(*realHistory);
    }

    TEST_F(MockCalculatorWithRealHistoryTest, MockCalculatorBasicFunctionality)
    {
        EXPECT_CALL(mockCalculator, Add(5, 3)).WillOnce(Return(8));
        EXPECT_EQ(mockCalculator.Add(5, 3), 8);
    }

    TEST(CalculatorIntegrationTest, RealCalculatorWithRealHistory)
    {
        InMemoryHistory history;
        SimpleCalculator calculator(history);
        calculator.Add(2, 3);
        calculator.Subtract(10, 5);
        auto operations = history.GetLastOperations(2);
        EXPECT_EQ(operations.size(), 2);
        EXPECT_EQ(operations[0], "2 + 3 = 5");
        EXPECT_EQ(operations[1], "10 - 5 = 5");
    }

}