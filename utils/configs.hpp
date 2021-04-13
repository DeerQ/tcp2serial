#ifndef CONFIGS_HPP
#define CONFIGS_HPP
#include <string>

namespace tcp2serial {
struct configs {
    configs():tcp_port{8092},
        ser_port_name{"/dev/pts/2"},
        ser_port_baud_rate{"9600"} {}
    int tcp_port;
    std::string ser_port_name;
    std::string ser_port_baud_rate;
    std::string incoming_req_type;
    std::string crlf;
};
}

#endif // CONFIGS_HPP
