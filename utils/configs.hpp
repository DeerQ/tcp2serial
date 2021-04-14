#ifndef CONFIGS_HPP
#define CONFIGS_HPP
#include <string>
#include <ostream>

namespace tcp2serial {
class configs {
        friend std::ostream& operator<<(std::ostream& os, const tcp2serial::configs& cfg);
        int _tcp_port;
        std::string _ser_port_name;
        std::string _ser_port_baud_rate;
        std::string _incoming_req_type;
        bool _crlf;
    public:
        configs();
        int tcp_port();
        std::string ser_port_name();
        std::string ser_port_baud_rate();
        std::string incoming_req_type();
        bool crlf();
        void tcp_port(int f);
        void ser_port_name(std::string f);
        void ser_port_baud_rate(std::string f);
        void incoming_req_type(std::string f);
        void crlf(bool f);
};
std::ostream& operator<<(std::ostream& os, const tcp2serial::configs& cfg);
}

#endif // CONFIGS_HPP
