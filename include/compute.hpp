#include <stdexcept>
#include "operation.hpp"
#include "math_library.h"

class Compute
{
public:
    void calculate(Operation &operation)
    {

        char op = operation.m_operator;
        long first = operation.m_first;
        long second = operation.m_second;
        long long result;

        int status_div = 0;

        switch (op)
        {
            case '+':
                math_operations::addition(first, second, result);
                break;
            case '-':
                math_operations::subtraction(first, second, result);
                break;
            case '*':
                math_operations::multiplication(first, second, result);
                break;
            case '/':
                status_div = math_operations::division(first, second, result);
                if ((status_div))
                {
                    throw std::runtime_error("Divizion on zero!");
                }
                break;
            case '^':
                math_operations::exponentiation(first, second, result);
                break;
            case '!':
                result = math_operations::factorial(first);
                break;
            default:
                result = 0;
                break;
        }
        operation.m_result = result;
    }
};