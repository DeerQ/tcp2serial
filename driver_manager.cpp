#include "driver_manager.hpp"
#include "drivers/ser_port.hpp"
#include "drivers/tcp_server.hpp"
#include <iostream>
#include <algorithm>

tcp2serial::driver_manager::~driver_manager() {
    delete _send_api;
    delete _receive_api;
}

void tcp2serial::driver_manager::send_to_receive_worker(send* send_api,
        receive* receive_api) {
    while(_send_to_receive_thread) {
        auto msg = send_api->receive_data();
        if(msg.empty()) {
            continue;
        }
        receive_api->send_data(msg);
    }
}

tcp2serial::driver_manager::driver_manager(tcp2serial::configs cfg)
    :_cfg{cfg},_send_api{nullptr},_receive_api{nullptr} {
}

void tcp2serial::driver_manager::init() {
    _send_to_receive_thread = false;
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
    std::string input;
    _send_api_send_worker_thread = std::thread(&send::send_worker,_send_api);
    while (true) {
        _receive_api->accept_new_connection();
        _send_to_receive_thread=true;
        _send_api_receive_worker_thread = std::thread(&driver_manager::send_to_receive_worker,this,_send_api,_receive_api);
        while(true) {
            try {
                input = _receive_api->receive_data();
            }
            catch(...) {
                break;
            }
            if(input.empty()) {
                continue;
            }
            if( true == _cfg.crlf()) {
                input += "\r\n";
            }
            else {
                input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
                input.erase(std::remove(input.begin(), input.end(), '\r'), input.end());
            }
            _send_api->append_to_send_stream(input);
        }
        _send_to_receive_thread = false;
        _send_api_receive_worker_thread.join();
    }
    _send_api_send_worker_thread.join();
}
