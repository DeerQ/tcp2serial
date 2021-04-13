#include "driver_manager.hpp"
#include "drivers/ser_port.hpp"
#include "drivers/tcp_server.hpp"
#include <iostream>

tcp2serial::driver_manager::~driver_manager() {
    delete _send_api;
    delete _receive_api;
}

void tcp2serial::driver_manager::receive_to_send_worker(send* send_api,
        receive* receive_api) {
    while(true) {
        send_api->append_to_send_stream(receive_api->receive_data());
    }
}

tcp2serial::driver_manager::driver_manager(tcp2serial::configs cfg)
    :_cfg{cfg},_send_api{nullptr},_receive_api{nullptr} {
}

void tcp2serial::driver_manager::init() {
    if ( nullptr != _send_api ) {
        throw std::runtime_error("ERROR, send api pointer is not empty");
    }
    else {
        auto send_api = new ser_port;
        send_api->init(_cfg.ser_port_name(),_cfg.ser_port_baud_rate());
        _send_api = static_cast<send*>(send_api);
    }
    if ( nullptr != _receive_api ) {
        throw std::runtime_error("ERROR, receive api pointer is not empty");
    }
    else {
        auto receive_api = new tcp_server;
        receive_api->init(_cfg.tcp_port());
        _receive_api = static_cast<receive*>(receive_api);
    }
}

void tcp2serial::driver_manager::run() {
    _worker_threads.emplace_back(&send::send_worker,_send_api);
    for ( int i=0 ; i<2; i++) {
        _worker_threads.emplace_back(&driver_manager::receive_to_send_worker,this,_send_api,_receive_api);
    }
    //--------------
    for ( auto& th: _worker_threads) {
        th.join();
    }
}
