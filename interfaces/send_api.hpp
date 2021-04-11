#include <string>
namespace tcp2serial {
class send_api {
    public:
        virtual std::string send()=0;
};
}
