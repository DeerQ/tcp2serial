#include "../interfaces/send_api.hpp"
namespace tcp2serial {
class ser_port : public send_api {
    public:
        std::string send() override;
};
}
