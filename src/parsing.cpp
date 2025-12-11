#include "../include/parsing.h"

#include <getopt.h>
#include <stdlib.h>

#include <iostream>
utils::TypeReturn parsing(int argc, char *argv[], utils::Action &action)
{
    int opt;
    int option_index = 0;
    const struct option long_options[] = {{"help", no_argument, 0, 'h'},
                                          {"version", no_argument, 0, 'v'}};

    if (argc == 2)
    {
        opt = getopt_long(argc, argv, "hv", long_options, &option_index);
        switch (opt)
        {
            case 'h':
                return utils::TypeReturn::HELP;
            case 'v':
                return utils::TypeReturn::VERSION;
            default:
                std::cerr << "Unknown arguments\n";
                return utils::TypeReturn::ERROR;
        }
    }
    else if (argc == 3)
    {
        action.first = atoi(argv[1]);
        if (action.first == 0)
        {
            std::cerr << "Incorrect arguments\n";
            return utils::TypeReturn::ERROR;
        }
        action.operation = argv[2][0];
        return utils::TypeReturn::READY_CALCULATE;
    }
    else if (argc == 4)
    {
        action.first = atoi(argv[1]);
        action.operation = argv[2][0];
        action.second = atoi(argv[3]);

        if ((action.first == 0) || (action.second == 0))
        {
            std::cerr << "Incorrect arguments\n";
            return utils::TypeReturn::ERROR;
        }
        return utils::TypeReturn::READY_CALCULATE;
    }
    else
    {
        std::cerr << "Incorrect count arguments\n";
        return utils::TypeReturn::ERROR;
    }
}