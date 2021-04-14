#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <mutex>

#include "../apis/receive.hpp"

namespace tcp2serial {
class tcp_server : public receive {
    private:
        int _sock_fd, _new_socket_fd;
        socklen_t _clilen;
        char _buffer[256];
        struct sockaddr_in _serv_addr, _cli_addr;
        std::mutex _mx;
    public:
        tcp_server() = default;
        ~tcp_server();
        std::string receive_data() override;
        virtual void send_data(std::string msg ) override;
        void init(int port) ;
        void accept_new_connection() override;

};
}

#endif
