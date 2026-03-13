#include <gtest/gtest.h>
#include <zmq.hpp>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;


json sendRequest(const std::string& request)
{
    zmq::context_t context(1);
    zmq::socket_t socket(context, zmq::socket_type::req);
    socket.connect("tcp://localhost:50051");

    zmq::message_t message(request.begin(), request.end());
    socket.send(message, zmq::send_flags::none);

    zmq::message_t reply;
    socket.recv(reply);

    std::string responseStr(static_cast<char*>(reply.data()), reply.size());
    return json::parse(responseStr);
}


TEST(CalculatorTest, Addition)
{
    auto response = sendRequest(
        R"({"mode":"calculation","first_num":5,"second_num":2,"operation":"+"})"
    );
    EXPECT_EQ(response["result"].get<long long>(), 7);
}


TEST(CalculatorTest, Subtraction)
{
    auto response = sendRequest(
        R"({"mode":"calculation","first_num":10,"second_num":3,"operation":"-"})"
    );
    EXPECT_EQ(response["result"].get<long long>(), 7);
}


TEST(CalculatorTest, Multiplication)
{
    auto response = sendRequest(
        R"({"mode":"calculation","first_num":4,"second_num":3,"operation":"*"})"
    );
    EXPECT_EQ(response["result"].get<long long>(), 12);
}


TEST(CalculatorTest, Division)
{
    auto response = sendRequest(
        R"({"mode":"calculation","first_num":10,"second_num":2,"operation":"/"})"
    );
    EXPECT_EQ(response["result"].get<long long>(), 5);
}

TEST(CalculatorTest, DivisionByZero)
{
    auto response = sendRequest(
        R"({"mode":"calculation","first_num":10,"second_num":0,"operation":"/"})"
    );
    EXPECT_TRUE(response.contains("error"));
}


TEST(CalculatorTest, Power)
{
    auto response = sendRequest(
        R"({"mode":"calculation","first_num":2,"second_num":10,"operation":"^"})"
    );
    EXPECT_EQ(response["result"].get<long long>(), 1024);
}

// --- Факториал ---
TEST(CalculatorTest, Factorial)
{
    auto response = sendRequest(
        R"({"mode":"calculation","first_num":5,"operation":"!"})"
    );
    EXPECT_EQ(response["result"].get<long long>(), 120);
}


TEST(CalculatorTest, CacheHit)
{
    std::string request =
        R"({"mode":"calculation","first_num":99,"second_num":1,"operation":"+"})" ;


    auto first = sendRequest(request);
    EXPECT_EQ(first["result"].get<long long>(), 100);

    auto second = sendRequest(request);
    EXPECT_EQ(second["result"].get<long long>(), 100);
    EXPECT_TRUE(second["from_cache"].get<bool>());
}