#include "../include/run.h"

#include <iostream>

#include "../include/calculate.h"
#include "../include/parsing.h"
#include "../include/print.h"
#include "../include/utils.hpp"
int run(int argc, char *argv[])
{
    utils::Action action;
    utils::TypeReturn status = parsing(argc, argv, action);
    switch (status)
    {
        case utils::TypeReturn::ERROR:
            std::cerr << "Use -h or --help to get help!\n";
            return -1;
        case utils::TypeReturn::HELP:
            printHelp();
            return 0;
        case utils::TypeReturn::VERSION:
            printVersion();
            return 0;
        case utils::TypeReturn::READY_CALCULATE:
            break;
    }
    int status_calc = calculate(action);
    if (!(status_calc == 0))
    {
        std::cerr << "Calculating error...\n";
        return -1;
    }
    printResult(action.result);
    return 0;
}