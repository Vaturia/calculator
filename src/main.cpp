#include "app.hpp"
int main(int argc, char *argv[])
{
    App app("tcp://0.0.0.0:50051");

    return app.run();
}
