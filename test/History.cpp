#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <limits>

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

    TEST(HistoryTest, HistoryGetLastOperationsHugeCount)
    {
        InMemoryHistory history;
        SimpleCalculator calculator(history);

        calculator.Add(1, 1);

        auto operations = history.GetLastOperations(std::numeric_limits<size_t>::max());
        EXPECT_EQ(operations.size(), 1);
    }

    TEST(HistoryTest, DISABLED_H1istoryCapacityLimit)
    {
        InMemoryHistory history;
        SimpleCalculator calculator(history);

        size_t limit = std::numeric_limits<size_t>::max();

        for (int i = 0; i < limit; ++i)
        {
            calculator.Add(i, i);
        }

        auto operations = history.GetLastOperations(limit);
        EXPECT_EQ(operations.size(), limit);
    }

    TEST(HistoryTest, DISABLED_HistoryThreadSafety)
    {
        InMemoryHistory history;
        SimpleCalculator calculator(history);

        EXPECT_TRUE(false) << "Thread safety not implemented";
    }
}