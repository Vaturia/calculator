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
    op.setFirstNum(5);
    op.setSecondNum(2);

    for(const auto& [op_value, result_op] : operations)
    {
        op.setOperator(op_value);
        compute.calculate(op);

        EXPECT_EQ(op.getResult(), result_op);
    }
}
TEST(CalculationTest, TestWithUnaryOp)
{
    Operation op;
    Compute compute;

    op.setFirstNum(5);
    op.setOperator('!');

    compute.calculate(op);

    EXPECT_EQ(op.getResult(), 120);
}
TEST(CalculationTest, ZeroThrowException)
{
    Operation op;
    Compute compute;

    op.setFirstNum(10);
    op.setSecondNum(0);
    op.setOperator('/');

    EXPECT_THROW(compute.calculate(op), std::runtime_error);
}