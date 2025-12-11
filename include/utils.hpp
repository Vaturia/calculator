#ifndef ACTION_H
#define ACTION_H
#pragma once
namespace utils
{
    struct Action
    {
        long first;
        long second;
        char operation;
        long long result;
    };
    enum TypeReturn
    {
        ERROR = -1,
        READY_CALCULATE,
        HELP,
        VERSION
    };
};  // namespace utils
#endif