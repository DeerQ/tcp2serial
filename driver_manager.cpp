#include "driver_manager.hpp"
#include "drivers/ser_port.hpp"
#include "drivers/tcp_server.hpp"
#include <iostream>
#include <memory>

void tcp2serial::driver_manager::receive_to_send_worker(std::shared_ptr<send> send_api,
        std::shared_ptr<receive> receive_api) {
    while(true) {
        send_api->append_to_send_stream(receive_api->receive_data());
    }
}

tcp2serial::driver_manager::driver_manager(tcp2serial::configs cfg)
    :_cfg{cfg},_send_api{nullptr},_receive_api{nullptr} {
}

void tcp2serial::driver_manager::init() {
    if ( _send_api ) {
        throw std::runtime_error("ERROR, send handler is not empty");
    }
    else {
        auto port = std::make_shared<ser_port>();
        port->init(_cfg.ser_port_name(),_cfg.ser_port_baud_rate());
        _send_api = port;
    }
    if ( _receive_api ) {
        throw std::runtime_error("ERROR, receive handler is not empty");
    }
    else {
        auto server = std::make_shared<tcp_server>();
        server->init(_cfg.tcp_port());
        _receive_api = server;
    }
}

void tcp2serial::driver_manager::run() {
    _worker_threads.emplace_back(&send::send_worker,_send_api);
    for ( int i=0 ; i<3; i++) {
        _worker_threads.emplace_back(&driver_manager::receive_to_send_worker,this,_send_api,_receive_api);
    }
    //--------------
    for ( auto& th: _worker_threads) {
        th.join();
    }
}
