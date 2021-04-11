#include <stdio.h>
#include <string.h>

#include <fcntl.h>
#include <errno.h>

#include <unistd.h>

#include <iostream>
#include <stdexcept>

#include "ser_port.hpp"

tcp2serial::ser_port::~ser_port() {
    close(_serial_port);
}

void tcp2serial::ser_port::send(std::string msg) {
    write(_serial_port, msg.c_str(), msg.size());
}

void tcp2serial::ser_port::init(const std::string& port_name, const std::string& baud_rate) throw() {
    _baud_rates.init();
    _serial_port = open(port_name.c_str(), O_RDWR);
    struct termios tty;
    if(tcgetattr(_serial_port, &tty) != 0) {
        throw std::runtime_error("ERROR "+std::to_string(errno)+" from tcgetattr: " +strerror(errno));
    }
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;
    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO;
    tty.c_lflag &= ~ECHOE;
    tty.c_lflag &= ~ECHONL;
    tty.c_lflag &= ~ISIG;
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);
    tty.c_oflag &= ~OPOST;
    tty.c_oflag &= ~ONLCR;
    tty.c_cc[VTIME] = 10;
    tty.c_cc[VMIN] = 0;
    speed_t speed= _baud_rates.lookup(baud_rate);
    cfsetispeed(&tty, speed);
    cfsetospeed(&tty, speed);
    if (tcsetattr(_serial_port, TCSANOW, &tty) != 0) {
        throw std::runtime_error("ERROR "+std::to_string(errno)+" from tcsetattr: " +strerror(errno));
    }
}
