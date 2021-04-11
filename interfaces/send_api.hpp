#include <string>
namespace tcp2serial {
class send_api {
    public:
        virtual void send(std::string)=0;
};
}
