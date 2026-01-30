#include <iostream>
#include "operation.hpp"
#include "parser.hpp"
#include "compute.hpp"
#include "printer.hpp"
class App
{
private:
    int m_argc;
    char **m_argv;
public:
    App(int argc, char **argv)
        :m_argc{argc}, m_argv{argv}
    {
    }
    void run()  
    {
        spdlog::info("Start application");
        Operation operation;
        Parser parser;
        Compute comp;
        Printer printer;
        try
        {
            parser.parse(m_argc, m_argv, operation);
            if(operation.getOperator())
            {
                comp.calculate(operation);
            }
            printer.printOutput(operation);
            spdlog::info("Stop application");
        }
        catch (const nlohmann::json::exception& e)
        {
            std::cerr << "Error: " << e.what(); 
            std::cerr << "\nUse \n{\n\"mode\":\"help\"\n}\nin file for help\n";
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << '\n';
            std::cerr << "Use \n{\n\"mode\":\"help\"\n}\nin file for help\n";
        }
    }
};