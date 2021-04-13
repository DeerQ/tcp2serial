#ifndef DRIVER_MANAGER_HPP
#define DRIVER_MANAGER_HPP

#include <thread>

#include "utils/configs.hpp"
#include "drivers/ser_port.hpp"
#include "drivers/tcp_server.hpp"

namespace tcp2serial {
class driver_manager {
        tcp2serial::configs _cfg;
        std::thread _ser_port_thread;
        std::thread _tcp_thread1;
        std::thread _tcp_thread2;

        ser_port* _ser_port;
        tcp_server* _tcp_server;
        void input_to_output_worker(send* send_api, receive* receive_api);
    public:
        driver_manager(tcp2serial::configs cfg);
        void init();
        void run();
};
}
#endif // DRIVER_MANAGER_HPP
