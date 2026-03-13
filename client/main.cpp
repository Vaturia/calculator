#include <zmq.hpp>
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: client '{\"mode\":\"calculation\","
                     "\"first_num\":5,\"second_num\":2,\"operation\":\"+\"}'\n";
        return 1;
    }

    zmq::context_t context(1);

    zmq::socket_t socket(context, zmq::socket_type::req);
    socket.connect("tcp://localhost:50051");

    std::string request = argv[1];
    zmq::message_t message(request.begin(), request.end());
    socket.send(message, zmq::send_flags::none);

    zmq::message_t reply;
    socket.recv(reply);

    std::string response(static_cast<char*>(reply.data()), reply.size());
    std::cout << "Response: " << response << "\n";

    return 0;
}