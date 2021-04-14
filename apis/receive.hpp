#ifndef RECEIVE_HPP
#define RECEIVE_HPP

#include <string>
namespace tcp2serial {
class receive {
    public:
        virtual ~receive() {}
        virtual std::string receive_data()=0;
        virtual void send_data( std::string msg ) =0;
        virtual void accept_new_connection() = 0;
};
}

#endif
