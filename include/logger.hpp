#include <spdlog/spdlog.h>

class Logger
{
   public:
    Logger()
    {
        spdlog::set_pattern("[%H:%M:%S] [%^%l%$] %v");
    }
    void info(const std::string &message)
    {
        spdlog::info(message);
    }
    void warn(const std::string &message)
    {
        spdlog::warn(message);
    }
    void error(const std::string &message)
    {
        spdlog::error(message);
    }
    void debug(const std::string &message)
    {
        spdlog::debug(message);
    }
};