#pragma once
struct Operation
{
    enum class Mode{
        CALC,
        HELP,
        VERSION,
        ERROR
    };

    long m_first, m_second;
    char m_operator;
    long long m_result;
    Mode m_operationMode;
    Operation()
        :m_first{0}, m_second{1}, m_operator{0}, m_result{0}, m_operationMode{Mode::ERROR}
    {
    }
};