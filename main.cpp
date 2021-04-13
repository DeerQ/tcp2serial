#include <iostream>
#include <getopt.h>

#include "utils/configs.hpp"
#include "drivers/tcp_server.hpp"
#include "drivers/ser_port.hpp"
#include "driver_manager.hpp"

int main(int argc, char* argv[]) {
    tcp2serial::configs cfg;
    int opt;
    while ((opt = getopt(argc, argv, "hp:s:b:c:o:")) != -1) {
        switch (opt) {
        case 'h':
            std::cout << "This can be considered as a TCP to serial adapter, wherein incoming TCP packets will be sent through the selected serial port." << '\n';
            return EXIT_SUCCESS;
            break;
        case 'p':
            cfg.tcp_port = atoi(optarg);
            break;
        case 's':
            cfg.ser_port_name = std::string(optarg);
            break;
        case 'b':
            cfg.ser_port_baud_rate = std::string(optarg);
            break;
        case 'c':
            cfg.incoming_req_type = std::string(optarg);
            break;
        case 'o':
            cfg.crlf = std::string(optarg);
            break;
        default: /* '?' */
            std::cerr << "ERROR!\nCall tcp2serial with -h option to see the help\n";
            exit(EXIT_FAILURE);
        }
    }
    tcp2serial::driver_manager dm{cfg};
    dm.init();
    dm.run();
    return 0;
}

