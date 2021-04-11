#include <stdexcept>

#include "tcp_server.hpp"

std::string tcp2serial::tcp_server::receive() {
    _new_socket_fd= accept(_sock_fd,
                           (struct sockaddr*) &_cli_addr,
                           &_clilen);
    if ( _new_socket_fd < 0) {
        throw std::runtime_error("ERROR on accept");
    }
    bzero(_buffer,256);
    int n = read(_new_socket_fd,_buffer,255);
    if (n < 0) {
        throw std::runtime_error("ERROR reading from socket");
    }
    std::string response = "I got your message";
    n = write(_new_socket_fd,response.data(),response.size());
    if (n < 0) {
        throw std::runtime_error("ERROR writing to socket");
    }
    close(_new_socket_fd);
    return std::string(_buffer);
}

void tcp2serial::tcp_server::init(int port) throw() {
    _sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_sock_fd < 0) {
        throw std::runtime_error("ERROR opening socket");
    }
    bzero((char*) &_serv_addr, sizeof(_serv_addr));
    _serv_addr.sin_family = AF_INET;
    _serv_addr.sin_addr.s_addr = INADDR_ANY;
    _serv_addr.sin_port = htons(port);
    if (bind(_sock_fd, (struct sockaddr*) &_serv_addr,
             sizeof(_serv_addr)) < 0) {
        throw std::runtime_error("ERROR binding socket");
    }
    listen(_sock_fd,5);
    //------------------------------------------------------
    _clilen = sizeof(_cli_addr);
}
