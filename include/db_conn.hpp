#pragma once

#include <libpq-fe.h>

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "operation.hpp"

struct PGconnDeleter
{
    void operator()(PGconn *conn) const
    {
        if (conn)
            PQfinish(conn);
    }
};
struct PGresultDeleter
{
    void operator()(PGresult *res) const
    {
        if (res)
            PQclear(res);
    }
};
using PGconnPtr = std::unique_ptr<PGconn, PGconnDeleter>;
using PGresultPtr = std::unique_ptr<PGresult, PGresultDeleter>;
class DBConnection
{
   private:
    PGconnPtr m_conn;

   public:
    explicit DBConnection(const std::string &conn_info) : m_conn(PQconnectdb(conn_info.c_str()))
    {
        if (PQstatus(m_conn.get()) != CONNECTION_OK)
        {
            std::string err = PQerrorMessage(m_conn.get());
            throw std::runtime_error("Connection failed: " + err);
        }
    }

    void exec(const std::string &sql)
    {
        PGresultPtr res(PQexec(m_conn.get(), sql.c_str()));
        if (PQresultStatus(res.get()) != PGRES_COMMAND_OK)
        {
            std::string err = PQerrorMessage(m_conn.get());
            throw std::runtime_error("Exec failed: " + err);
        }
    }
    std::vector<std::vector<std::string>> select(const std::string &sql)
    {
        PGresultPtr res(PQexec(m_conn.get(), sql.c_str()));
        if (PQresultStatus(res.get()) != PGRES_TUPLES_OK)
        {
            std::string err = PQerrorMessage(m_conn.get());
            throw std::runtime_error("Select failed: " + err);
        }

        size_t rows = static_cast<size_t>(PQntuples(res.get()));
        size_t cols = static_cast<size_t>(PQnfields(res.get()));
        std::vector<std::vector<std::string>> result;
        result.reserve(rows);

        for (size_t i = 0; i < rows; ++i)
        {
            std::vector<std::string> row;
            row.reserve(cols);
            for (size_t j = 0; j < cols; ++j)
            {
                row.emplace_back(PQgetvalue(res.get(), i, j));
            }
            result.push_back(std::move(row));
        }
        return result;
    }
};