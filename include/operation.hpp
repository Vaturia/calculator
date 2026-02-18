#pragma once

#include <cstddef>   
#include <functional> 
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
    bool operator==(const Operation & other) const
    {
        return m_first == other.m_first 
            && m_second == other.m_second
            && m_operator == other.m_operator;
    }
};
namespace std {
     template<>
    struct hash<Operation>
    {
        size_t operator()(const Operation& op) const noexcept
        {
            size_t h = 0;

            // Комбинируем хеши только тех полей, которые используются в operator==
            h ^= hash<long>{}(op.m_first)    + 0x9e3779b9 + (h << 6) + (h >> 2);
            h ^= hash<long>{}(op.m_second)   + 0x9e3779b9 + (h << 6) + (h >> 2);
            h ^= hash<char>{}(op.m_operator) + 0x9e3779b9 + (h << 6) + (h >> 2);

            return h;
        }
    };
}