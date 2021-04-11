#include <string>
namespace tcp2serial {
class receive_api {
    public:
        virtual std::string receive()=0;
};
}
