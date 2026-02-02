#include "operation.hpp"
#include <spdlog/spdlog.h>
class Printer
{
private:
    void printResult(long long result)
    {
        std::cout <<"Result of operation: "<< result << '\n';
    }
    void printHelp()
    {
        std::cout << "Usage:\n"
                  << "  calculator file.json\n";
        std::cout << "File format:\n"
                  << "  {\n   \"mode\": {string},\n   \"first_num\": {number}, \n"
                  << "   \"second_num\": {number},\n   \"operation\": {symbol}\n  }\n";
        std::cout << "Parameters:\n"
                  << "  string\t  Work mode (help, version, calculation)\n"
                  << "  number\t  Any numbers for calculating (second_num optinal where use \'!\' in operation)\n"
                  << "  symbol\t  Mathematical operation (+, -, *, /, or ^)\n";
        std::cout << "Example use:\n  test.json\n"
                  << "  {\n   \"mode\": \"calculation\"\n   \"first_num\": 5 \n"
                  << "   \"second_num\": 2\n   \"operation\": \"*\"\n  }\n"
                  << "Output:\n  10\n";
    }
    void printVersion()
    {
        std::cout << "Program name: Calculator\nVersion: 2.0\n";
    }
public:
    void printOutput(Operation &operation)
    {
        Operation::Mode mode = operation.m_operationMode;
        if(mode == Operation::Mode::CALC)
        {
            printResult(operation.m_result);
        }
        else if(mode == Operation::Mode::HELP)
        {
            printHelp();
        }
        else if(mode == Operation::Mode::VERSION)
        {
            printVersion();
        }
    }
};