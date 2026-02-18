#pragma once

#include <libpq-fe.h>
#include <memory>
#include <vector>
#include <string>
#include <cstddef>
#include "operation.hpp"
#include <stdexcept>

class DBConnection
{
private:
    PGconn* m_conn = nullptr;

public:
    explicit DBConnection(const std::string &conn_info)
        : m_conn(PQconnectdb(conn_info.c_str()))
    {
        if(PQstatus(m_conn) != CONNECTION_OK)
        {
            std::string err = PQerrorMessage(m_conn);
            PQfinish(m_conn);
            throw std::runtime_error("Connection failed: " + err);
        }
    }

    void exec(const std::string &sql)
    {
        PGresult* res = PQexec(m_conn, sql.c_str());
        if(PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            std::string err = PQerrorMessage(m_conn);
            PQclear(res);
            throw std::runtime_error("Exec failed: " + err);
        }
        PQclear(res);
    }
    std::vector<std::vector<std::string>> select(const std::string &sql)
    {
        PGresult* res = PQexec(m_conn, sql.c_str());
        if(PQresultStatus(res) != PGRES_TUPLES_OK)
        {
            std::string err = PQerrorMessage(m_conn);
            PQclear(res);
            throw std::runtime_error("Select failed: " + err);
        }

        size_t rows = static_cast<size_t>(PQntuples(res));
        size_t cols = static_cast<size_t>(PQnfields(res));
        std::vector<std::vector<std::string>> result;
        result.reserve(rows);      
        
        for(size_t i = 0; i < rows; ++i)
        {
            std::vector<std::string> row;
            row.reserve(cols);
            for(size_t j = 0; j < cols; ++j)
            {
                row.emplace_back(PQgetvalue(res, i, j));
            }
            result.push_back(std::move(row));
        }

        PQclear(res);
        return result;
    }

    ~DBConnection()
    {
        if(m_conn)
        {
            PQfinish(m_conn);
            m_conn = nullptr;
        }
    }
};