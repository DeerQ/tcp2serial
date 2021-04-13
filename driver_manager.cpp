#include "driver_manager.hpp"
#include <iostream>

void tcp2serial::driver_manager::input_to_output_worker(send* send_api,
        receive* receive_api) {
    while(true) {
        send_api->append_to_send_stream(receive_api->receive_data());
    }
}

tcp2serial::driver_manager::driver_manager(tcp2serial::configs cfg)
    :_cfg{cfg},_ser_port{new ser_port},_tcp_server{new tcp_server } {
}

void tcp2serial::driver_manager::init() {
    if ( nullptr == _ser_port ) {
        throw std::runtime_error("ERROR, serial port pointer is empty");
    }
    else {
        _ser_port->init(_cfg.ser_port_name,_cfg.ser_port_baud_rate);
    }
    if ( nullptr == _tcp_server ) {
        throw std::runtime_error("ERROR, tcp_server pointer is empty");
    }
    else {
        _tcp_server->init(_cfg.tcp_port);
    }
}

void tcp2serial::driver_manager::run() {
    _ser_port_thread = std::thread(&tcp2serial::ser_port::serial_port_worker,_ser_port);
    auto send_api= static_cast<send*>(_ser_port);
    auto receive_api= static_cast<receive*>(_tcp_server);
    _tcp_thread1 = std::thread(&driver_manager::input_to_output_worker,this,send_api,receive_api);
    _tcp_thread2 = std::thread(&driver_manager::input_to_output_worker,this,send_api,receive_api);
    //    //--------------
    _tcp_thread1.join();
    _tcp_thread2.join();
    _ser_port_thread.join();
}
