#include "configs.hpp"


tcp2serial::configs::configs()
    :_tcp_port{8092},
     _ser_port_name{"/dev/pts/3"},
     _ser_port_baud_rate{"9600"} {
}

int tcp2serial::configs::tcp_port() {
    return _tcp_port;
}
std::string tcp2serial::configs::ser_port_name() {
    return _ser_port_name;
}
std::string tcp2serial::configs::ser_port_baud_rate() {
    return _ser_port_baud_rate;
}
std::string tcp2serial::configs::incoming_req_type() {
    return _incoming_req_type;
}
bool tcp2serial::configs::crlf() {
    return _crlf;
}
void tcp2serial::configs::tcp_port(int f) {
    _tcp_port=f;
}
void tcp2serial::configs::ser_port_name(std::string f) {
    _ser_port_name = f;
}
void tcp2serial::configs::ser_port_baud_rate(std::string f) {
    _ser_port_baud_rate = f;
}
void tcp2serial::configs::incoming_req_type(std::string f) {
    _incoming_req_type = f;
}
void tcp2serial::configs::crlf(bool f) {
    _crlf = f;
}

std::ostream& tcp2serial::operator<<(std::ostream& os, const tcp2serial::configs& cfg) {
    os << "tcp port: "           << cfg._tcp_port << '\n'
       << "serial port name: "      << cfg._ser_port_name  << '\n'
       << "serial port baud rate: " << cfg._ser_port_baud_rate << '\n'
       << "incoming request type: "  << cfg._incoming_req_type << '\n'
       << "crlf: "               << cfg._crlf << std::endl;
    return os;
}
