#include <iostream>
#include <getopt.h>

#include "utils/configs.hpp"
#include "drivers/tcp_server.hpp"
#include "drivers/ser_port.hpp"
#include "driver_manager.hpp"

int main(int argc, char* argv[]) {
    tcp2serial::configs cfg;
    bool empty_options = true;
    int opt;
    while ((opt = getopt(argc, argv, "hp:s:b:c:o:")) != -1) {
        empty_options=false;
        switch (opt) {
        case 'h':
            std::cout << "This can be considered as a TCP to serial adapter, wherein incoming TCP packets will be sent through the selected serial port." << '\n';
            std::cout << "Arguments: " << '\n';
            std::cout << "\t-p <arg>\t\t" << "arg is the port number for tcp server" << '\n';
            std::cout << "\t-s <arg>\t\t" << "arg is the serial port name, something like /dev/ttyx " <<'\n';
            std::cout << "\t-b <arg>\t\t" << "arg is the baud rate for serial port" <<'\n';
            std::cout << "\t-c <arg>\t\t" << "arg is the incoming request type which can be a simple command(1) or enable/disable stream output of serial port(2)"
                      <<'\n';
            std::cout << "\t-o <arg>\t\t" << "arg is add/remove of crlf to/from incoming request " <<'\n';
            return EXIT_SUCCESS;
            break;
        case 'p':
            cfg.tcp_port(atoi(optarg));
            break;
        case 's':
            cfg.ser_port_name(std::string(optarg));
            break;
        case 'b':
            cfg.ser_port_baud_rate(std::string(optarg));
            break;
        case 'c':
            cfg.incoming_req_type(std::string(optarg));
            break;
        case 'o':
            cfg.crlf(std::string(optarg)=="add");
            break;
        default: /* '?' */
            std::cerr << "ERROR!\nCall tcp2serial with -h option to see the help\n";
            exit(EXIT_FAILURE);
        }
    }
    if(empty_options) {
        std::cerr << "Tcp2serial executed according to the default config as follow: \n" << cfg << '\n';
        std::cerr << "To change this config, use the -h option for help." << '\n';
    }
    tcp2serial::driver_manager dm{cfg};
    dm.init();
    dm.run();
    return 0;
}

