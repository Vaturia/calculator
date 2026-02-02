#include <gtest/gtest.h>
#include "operation.hpp"
#include "compute.hpp"
#include <vector>
#include <utility>
TEST(CalculationTest, TestWithBinaryOp)
{
    Operation op;
    Compute compute;

    std::vector<std::pair<char,long long>> operations = {
        {'+', 7},
        {'-', 3},
        {'*', 10},
        {'/', 2},
        {'^', 25}
    };
    op.m_first = 5;
    op.m_second = 2;

    for(const auto& [op_value, result_op] : operations)
    {
        op.m_operator = op_value;
        compute.calculate(op);

        EXPECT_EQ(op.m_result, result_op);
    }
}
TEST(CalculationTest, TestWithUnaryOp)
{
    Operation op;
    Compute compute;

    op.m_first = 5;
    op.m_operator = '!';

    compute.calculate(op);

    EXPECT_EQ(op.m_result, 120);
}
TEST(CalculationTest, ZeroThrowException)
{
    Operation op;
    Compute compute;

    op.m_first = 10;
    op.m_second = 0;
    op.m_operator = '/';

    EXPECT_THROW(compute.calculate(op), std::runtime_error);
}