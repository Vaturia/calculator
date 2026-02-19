#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "db_conn.hpp"
#include "operation.hpp"
class Cache
{
   private:
    std::unordered_map<Operation, long long, OperationHash> m_cache;
    DBConnection& m_db;
    void load()
    {
        m_cache.clear();
        auto rows = m_db.select("SELECT first, second, operator, result FROM operations");

        for (const auto& row : rows)
        {
            Operation op;
            op.m_first = std::stol(row[0]);
            op.m_second = std::stol(row[1]);
            op.m_operator = row[2][0];
            long long result = std::stoll(row[3]);
            m_cache[op] = result;
        }
    }

   public:
    explicit Cache(DBConnection& db) : m_db(db)
    {
        load();
    }
    bool check(Operation& op)
    {
        if(op.m_operator == '+' || op.m_operator == '*')
            if (op.m_first < op.m_second)
                std::swap(op.m_first, op.m_second);
        auto it = m_cache.find(op);
        if (it != m_cache.end())
        {
            op.m_result = it->second;
            return true;
        }
        return false;
    }
    void add(Operation& op)
    {
        m_cache[op] = op.m_result;
        std::string sql = "INSERT INTO operations (first, second, operator, result) VALUES (" +
                          std::to_string(op.m_first) + ", " + std::to_string(op.m_second) + ", '" +
                          op.m_operator + "', " + std::to_string(op.m_result) + ")";

        m_db.exec(sql);
    }
    void updateResult(Operation& op)
    {
        m_cache[op] = op.m_result;
        std::string sql = "UPDATE operations SET result = " + std::to_string(op.m_result) + 
                          " WHERE first = " + std::to_string(op.m_first) +
                          " AND second = " + std::to_string(op.m_second) +
                          " AND operator = '" + op.m_operator + "'";
        m_db.exec(sql);
    }
};