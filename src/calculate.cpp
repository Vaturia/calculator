#include "calculate.h"

#include <iostream>

#include "math_library.h"

int calculate(utils::Action &action)
{
    int status_div = 0;
    switch (action.operation)
    {
        case '+':
            return (math_operations::addition(action.first, action.second, action.result));
        case '-':
            return (math_operations::subtraction(action.first, action.second, action.result));
        case '*':
            return (math_operations::multiplication(action.first, action.second, action.result));
        case '/':
            status_div = math_operations::division(action.first, action.second, action.result);
            if ((status_div))
            {
                std::cerr << "Divizion on zero!\n";
                return -1;
            }
            return 0;
        case '^':
            return (math_operations::exponentiation(action.first, action.second, action.result));
        case '!':
            action.result = math_operations::factorial(action.first);
            return 0;
        default:
            std::cerr << "Unknown operation!\n";
            return -1;
    }
}