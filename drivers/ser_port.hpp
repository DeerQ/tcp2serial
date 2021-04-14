#ifndef SER_PORT_HPP
#define SER_PORT_HPP

#include <termios.h>
#include <unordered_map>
#include <mutex>

#include "../apis/send.hpp"
#include "../utils/semaphore.hpp"

namespace tcp2serial {
class ser_port : public send {
        class baud_rate_table {
                std::unordered_map<std::string,speed_t> _table;
            public:
                void init() noexcept {
                    _table["0"] = 0;
                    _table["50"] =     0000001;
                    _table["75"] =     0000002;
                    _table["110"] =    0000003;
                    _table["134"] =    0000004;
                    _table["150"] =    0000005;
                    _table["200"] =    0000006;
                    _table["300"] =    0000007;
                    _table["600"] =    0000010;
                    _table["1200"] =   0000011;
                    _table["1800"] =   0000012;
                    _table["2400"] =   0000013;
                    _table["4800"] =   0000014;
                    _table["9600"] =   0000015;
                    _table["19200"] =  0000016;
                    _table["38400"] =  0000017;
                    _table["57600"] =  0010001;
                    _table["115200"] = 0010002;
                    _table["230400"] = 0010003;
                    _table["460800"] = 0010004;
                }
                speed_t lookup(const std::string& str) {
                    return _table.at(str);
                }
        };
        baud_rate_table _baud_rates;
        int _serial_port;
        //---------------------------
        std::string _bytes_to_send;
        tcp2serial::semaphore _smp;
        std::mutex _mx;

    public:
        ser_port() = default;
        ~ser_port();
        void append_to_send_stream(std::string bytes_to_send) override;
        void send_worker() override;
        void init(const std::string& port_name, const std::string& baud_rate);
        virtual std::string receive_data() override;
};
}

#endif
