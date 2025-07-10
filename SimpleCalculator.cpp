// (C) PROTEI protei.com

#include "SimpleCalculator.h"
#include "IHistory.h"

#include <sstream>
#include <limits>

namespace calc
{

    SimpleCalculator::SimpleCalculator(IHistory &history)
        : m_history(history)
    {
    }

    void SimpleCalculator::SetHistory(IHistory &history)
    {
        m_history = history;
    }

    int SimpleCalculator::Add(int a, int b)
    {
        int result = a + b;
        LogOperation(a, "+", b, result);
        return result;
    }

    int SimpleCalculator::Subtract(int a, int b)
    {
        int result = a - b;
        LogOperation(a, "-", b, result);
        return result;
    }

    int SimpleCalculator::Multiply(int a, int b)
    {
        int result = a * b;
        LogOperation(a, "*", b, result);
        return result;
    }

    int SimpleCalculator::Divide(int a, int b)
    {
        if (b == 0)
        {
            throw std::invalid_argument("Division by zero is not allowed");
        }

        if (a == std::numeric_limits<int>::min() && b == -1)
        {
            throw std::overflow_error("Division overflow: INT_MIN / -1 would cause integer overflow");
        }

        int result = a / b;
        LogOperation(a, "/", b, result);
        return result;
    }

    void SimpleCalculator::LogOperation(int a, const char *op, int b, int result)
    {
        std::ostringstream oss;
        oss << a << " " << op << " " << b << " = " << result;
        m_history.AddEntry(oss.str());
    }

} // namespace calc
