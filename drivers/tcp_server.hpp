#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../interfaces/receive_api.hpp"
namespace tcp2serial {
class tcp_server : public receive_api {
        int _sock_fd, _new_socket_fd;
        socklen_t _clilen;
        char _buffer[256];
        struct sockaddr_in _serv_addr, _cli_addr;
    public:
        tcp_server() = default;
        ~tcp_server();
        std::string receive() override;
        void init(int port) throw() ;
};
}
