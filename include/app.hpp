#pragma once
#include <atomic>
#include <csignal>
#include <iostream>
#include <nlohmann/json.hpp>
#include <thread>
#include <zmq.hpp>

#include "cache.hpp"
#include "compute.hpp"
#include "db_conn.hpp"
#include "logger.hpp"
#include "parser.hpp"

class App
{
   private:
    std::string m_address;
    Logger m_logger;
    DBConnection m_db;
    Cache m_cache;
    Parser m_parser;
    Compute m_compute;
    std::atomic<bool> m_shutdown;

    void blockSignals()
    {
        sigset_t mask;
        sigemptyset(&mask);
        sigaddset(&mask, SIGTERM);
        sigaddset(&mask, SIGINT);
        pthread_sigmask(SIG_BLOCK, &mask, nullptr);
    }

    void signalThread()
    {
        sigset_t mask;
        sigemptyset(&mask);
        sigaddset(&mask, SIGTERM);
        sigaddset(&mask, SIGINT);

        m_logger.info("Signal handler started");

        int sig = 0;
        sigwait(&mask, &sig);

        m_logger.info("Signal " + std::to_string(sig) + " received, stopping...");
        m_shutdown = true;
    }
    std::string handleRequest(const std::string& requestStr)
    {
        try
        {
            Operation op;
            m_parser.parseFromString(requestStr, op);

            bool atCache = m_cache.check(op);
            m_logger.info(atCache ? "Found in cache" : "Not in cache, calculating...");

            if (!atCache)
            {
                m_cache.add(op);
                m_compute.calculate(op);
                m_cache.updateResult(op);
            }

            json response;
            response["result"] = op.m_result;
            response["from_cache"] = atCache;
            return response.dump();
        }
        catch (const std::exception& e)
        {
            m_logger.error(e.what());

            json error;
            error["error"] = e.what();
            return error.dump();
        }
    }
    void workerLoop()
    {
        zmq::context_t context(1);

        zmq::socket_t socket(context, zmq::socket_type::rep);
        socket.bind(m_address);
        m_logger.info("Listening on " + m_address);

        while (!m_shutdown)
        {
            zmq::message_t request;

            auto result = socket.recv(request, zmq::recv_flags::dontwait);

            if (!result)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                continue;
            }

            std::string requestStr(static_cast<char*>(request.data()), request.size());
            m_logger.info("Received: " + requestStr);

            std::string response = handleRequest(requestStr);
            m_logger.info("Sending: " + response);

            zmq::message_t reply(response.begin(), response.end());
            socket.send(reply, zmq::send_flags::none);
        }
    }

   public:
    App(const std::string& address)
        : m_address(address),
          m_db("host=localhost port=5432 dbname=postgres user=postgres password=12345"),
          m_cache(m_db),
          m_shutdown(false)
    {
    }
    int run()
    {
        blockSignals();

        std::thread sigThread(&App::signalThread, this);

        m_logger.info("Server starting on " + m_address);
        workerLoop();

        sigThread.join();
        m_logger.info("Server stopped");
        return 0;
    }
};