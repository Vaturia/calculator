#include "print.h"

#include <iostream>

void printResult(long long result)
{
    std::cout << result << '\n';
}
void printHelp()
{
    std::cout << "Usage:\n"
              << "  calculator [options]\n"
              << "  calculator [value1] [binaryOperation] [value2]\n"
              << "  calculator [number for factorial] !\n";
    std::cout << "Options:\n"
              << "  -h or --help\t\t Display this information\n"
              << "  -v or --version \t Display calculator version information\n";
    std::cout << "Parameters:\n"
              << "  value1/value2\t\t Any numbers\n"
              << "  binaryOperation  \t Mathematical operation (+, -, *, /, or "
                 "^). * - must be escaped (\\*)\n"
              << "  number for factorial \t Positive integer number\n";
}
void printVersion()
{
    std::cout << "Program name: Calculator\nVersion: 1.0\n";
}