#pragma once
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
using json = nlohmann::json;
#include "operation.hpp"

class Parser
{
   private:
    Operation::Mode convertStrToMode(const std::string& mode)
    {
        if (mode == "help")
        {
            return Operation::Mode::HELP;
        }
        else if (mode == "version")
        {
            return Operation::Mode::VERSION;
        }
        else if (mode == "calculation")
        {
            return Operation::Mode::CALC;
        }
        else
        {
            return Operation::Mode::ERROR;
        };
    }

   public:
    void parseFromJson(const json& data, Operation& operation)
    {
        if (data.empty() || data.is_null())
        {
            throw std::invalid_argument("Json is empty!");
        }
        else if (data.size() == 1)
        {
            operation.m_operationMode = convertStrToMode(data["mode"].get<std::string>());
        }
        else if (data.size() == 3)
        {
            operation.m_operationMode = convertStrToMode(data["mode"].get<std::string>());
            operation.m_first = data["first_num"].get<long>();
            operation.m_operator = (data["operation"].get<std::string>())[0];
        }
        else if (data.size() == 4)
        {
            operation.m_first = data["first_num"].get<long>();
            operation.m_second = (data["second_num"].get<long>());
            operation.m_operator = (data["operation"].get<std::string>())[0];
            operation.m_operationMode = convertStrToMode(data["mode"].get<std::string>());
        }
        else
        {
            throw std::invalid_argument("Invalid count arguments!");
        }

        if (operation.m_operationMode == Operation::Mode::ERROR)
        {
            throw std::invalid_argument("Invalid mode type!");
        }
    }
    void parse(int argc, char** argv, Operation& operation)
    {
        std::string str_argv(argv[1]);
        json data = json::parse(str_argv);
        parseFromJson(data, operation);
    }
};