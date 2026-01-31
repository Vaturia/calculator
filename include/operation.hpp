#pragma once

class Parser;
class Compute;
class Printer;
class App;

class Operation
{
public:
    enum class Mode{
        CALC,
        HELP,
        VERSION,
        ERROR
    };
private:
    long m_first, m_second;
    char m_operator;
    long long m_result;
    Mode m_operationMode;

public:
    Operation()
        :m_first{0}, m_second{1}, m_operator{0}, m_result{0}, m_operationMode{Mode::ERROR}
    {
    }
    long getFirstNum() const { return m_first; };
    long getSecondNum() const { return m_second; };
    char getOperator() const { return m_operator; };
    long long getResult() const { return m_result; };
    Mode getMode() const { return m_operationMode; };
    void setFirstNum(long num) { m_first = num; };
    void setSecondNum(long num) { m_second = num; };
    void setOperator(char op) { m_operator = op; };
    void setResult (long long res) { m_result = res; };
    void setMode (Mode operMode) { m_operationMode = operMode; };
};