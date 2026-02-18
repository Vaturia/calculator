#include <iostream>
#include "operation.hpp"
#include "parser.hpp"
#include "compute.hpp"
#include "printer.hpp"
#include "logger.hpp"
#include "cache.hpp"
#include "db_conn.hpp"
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
    DBConnection m_db;
    Cache m_cache;
public:
    App(int argc, char **argv)
        :   m_argc{argc}, m_argv{argv},
            m_db("host=localhost port=5432 dbname=postgres user=postgres password=12345"),
            m_cache(m_db)
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

            m_logger.info("Search operation in cache");
            bool atCache = m_cache.check(m_operation);
            m_logger.info(atCache ? "Operation found in cache" : "Operation not found in cache");

            if(!(atCache))
            {
                m_logger.info("Start calculating...");
                m_compute.calculate(m_operation);
                m_logger.info("Calculate done!");
                m_logger.info("Add operation to cache and DB");
                m_cache.add(m_operation);
                m_logger.info("Operation added into cache and DB");
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