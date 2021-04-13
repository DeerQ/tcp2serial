#ifndef SEND_HPP
#define SEND_HPP

#include <string>
namespace tcp2serial {
class send {
    public:
        virtual void append_to_send_stream(std::string)=0;
};
}

#endif
