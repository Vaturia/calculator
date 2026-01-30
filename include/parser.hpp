#pragma once
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
using json = nlohmann::json;
#include "operation.hpp"

class Parser 
{
private:
    Operation::Mode convertStrToMode(std::string mode)
    {
        if(mode == "help"){ return Operation::Mode::HELP;  }
        else if (mode == "version") { return Operation::Mode::VERSION; }
        else if (mode == "calculation") { return Operation::Mode::CALC; }
        else { return Operation::Mode::ERROR; };
    }
public:
    void parseFromJson(const json& data, Operation& operation)
    {        
        if(data.empty() || data.is_null())
        {
            throw "Json is empty!\n";
        }
        else if(data.size() == 1)
        {
            operation.setMode(convertStrToMode(data["mode"].get<std::string>()));
        }
        else if(data.size() == 3)
        {
            operation.setMode(convertStrToMode(data["mode"].get<std::string>()));
            operation.setFirstNum(data["first_num"].get<long>());
            operation.setOperator((data["operation"].get<std::string>())[0]);
        }
        else if(data.size() == 4)
        {
            operation.setFirstNum(data["first_num"].get<long>());
            operation.setSecondNum(data["second_num"].get<long>());
            operation.setOperator((data["operation"].get<std::string>())[0]);
            operation.setMode(convertStrToMode(data["mode"].get<std::string>()));
        }
        else
        {
            throw std::invalid_argument("Invalid count arguments!");
        }
    }
    void parse(int argc, char** argv, Operation& operation)
    {
        spdlog::info("Parsing...");
        std::ifstream f(argv[1]);
        json data = json::parse(f);
        parseFromJson(data, operation);
        spdlog::info("Parsing done!");
    }
};