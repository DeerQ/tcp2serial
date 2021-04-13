#ifndef RECEIVE_HPP
#define RECEIVE_HPP

#include <string>
namespace tcp2serial {
class receive {
    public:
        virtual std::string receive_data()=0;
};
}

#endif
