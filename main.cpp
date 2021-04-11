#include <iostream>
#include "drivers/tcp_server.hpp"
int main() {
    tcp2serial::tcp_server server;
    server.init(8091);
    std::cerr << server.receive() << '\n';
    return 0;
}
