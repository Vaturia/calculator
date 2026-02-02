#include <gtest/gtest.h>
#include "operation.hpp"
#include "printer.hpp"

TEST(PrinterTest, OutputResult){
    Operation op;
    Printer printer;

    op.m_operationMode = Operation::Mode::CALC;
    op.m_result = 100;

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    printer.printOutput(op);

    std::cout.rdbuf(old);

    EXPECT_TRUE(buffer.str().find("Result of operation: 100") != std::string::npos);
}
TEST(PrinterTest, OutputHelp){
    Operation op;
    Printer printer;

    op.m_operationMode =  Operation::Mode::HELP;

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    printer.printOutput(op);

    std::cout.rdbuf(old);

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("Usage:") != std::string::npos);
    EXPECT_TRUE(output.find("calculator file.json") != std::string::npos);

}
TEST(PrinterTest, OutputVersion){
    Operation op;
    Printer printer;

    op.m_operationMode = Operation::Mode::VERSION;

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    printer.printOutput(op);

    std::cout.rdbuf(old);

    std::string output = buffer.str();

    EXPECT_TRUE(output.find("Program name: Calculator") != std::string::npos);
    EXPECT_TRUE(output.find("Version: 2.0") != std::string::npos);
}