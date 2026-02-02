#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "operation.hpp"
#include "parser.hpp"
#include <string>
#include <vector>
#include <utility>
using json = nlohmann::json;

TEST(ParserTest, EmptyJsonThrowsException){
    Parser parser;
    Operation op;
    json empty_json = json::parse("{}");

    EXPECT_THROW(parser.parseFromJson(empty_json, op), std::invalid_argument);
}

TEST(ParseTest, SingleFieldModes){
    Parser parser;

    std::vector<std::pair<std::string, Operation::Mode>> modes = {
        {"help", Operation::Mode::HELP},
        {"version", Operation::Mode::VERSION}
    };
    for(const auto& [mode_str, expected_mode] : modes)
    {
        json data;
        data["mode"] = mode_str;

        Operation op;
        parser.parseFromJson(data, op);

        EXPECT_EQ(op.m_operationMode, expected_mode)
            << "Для mode='" << mode_str
            << "' ожидался " << static_cast<int>(expected_mode)
            <<", получен " << static_cast<int>(op.m_operationMode);
    }
}
TEST(ParseTest, ThreeFilesMode)
{
    Parser parser;
    Operation op;
    json data;


    data["mode"] = "calculation";
    data["first_num"] = 5;
    data["operation"] = "!";

    parser.parseFromJson(data, op);

    EXPECT_EQ(op.m_operationMode, Operation::Mode::CALC);
    EXPECT_EQ(op.m_operator, '!');
    EXPECT_EQ(op.m_first, 5);
}
TEST(ParseTest, FourFieldsMode)
{
    Parser parser;
    Operation op;
    json data;


    data["mode"] = "calculation";
    data["first_num"] = 5;
    data["second_num"] = 2;
    data["operation"] = "+";

    parser.parseFromJson(data, op);

    EXPECT_EQ(op.m_operationMode, Operation::Mode::CALC);
    EXPECT_EQ(op.m_operator, '+');
    EXPECT_EQ(op.m_first, 5);
    EXPECT_EQ(op.m_second, 2);
}
