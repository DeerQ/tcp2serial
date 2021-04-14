#ifndef SEND_HPP
#define SEND_HPP

#include <string>
namespace tcp2serial {
class send {
    public:
        virtual ~send() {}
        virtual void append_to_send_stream(std::string)=0;
        virtual void send_worker()=0;
        virtual std::string receive_data()=0;
};
}

#endif
