#include <iostream>
#include "operation.hpp"
#include "parser.hpp"
#include "compute.hpp"
#include "printer.hpp"
#include "logger.hpp"
class App
{
private:
    int m_argc;
    char **m_argv;
    Operation m_operation;
    Parser m_parser;
    Compute m_compute;
    Printer m_printer;
    Logger m_logger;
public:
    App(int argc, char **argv)
        :m_argc{argc}, m_argv{argv}
    {
    }
    void run()  
    {
        m_logger.info("Start application");

        try
        {
            m_logger.info("Start parsing...");
            m_parser.parse(m_argc, m_argv, m_operation);
            m_logger.info("Parsing done!");
            if(m_operation.m_operator)
            {
                m_logger.info("Start calculating...");
                m_compute.calculate(m_operation);
                m_logger.info("Calculate done!");
            }
            m_logger.info("Choice printing...");
            m_printer.printOutput(m_operation);
            m_logger.info("Printing done!");
            m_logger.info("Stop application");
        }
        catch (const nlohmann::json::exception& e)
        {
            m_logger.error(e.what());
            m_logger.error("\nUse \n{\n\"mode\":\"help\"\n}\nin file for help\n");
        }
        catch(const std::exception& e)
        {
            m_logger.error(e.what());
            m_logger.error("\nUse \n{\n\"mode\":\"help\"\n}\nin file for help\n");
        }
    }
};