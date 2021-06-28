/*This class was designed to forward the incoming data to output.
 * This is done regardless of the types source or destination of data.
 * In this case, the source of data is a tcp server and the destination is serial port,
 * however, it can be easily switched with other sources such as a database or file,
 * and other form of destinations such as a web service or a file again.
*/
#ifndef DRIVER_MANAGER_HPP
#define DRIVER_MANAGER_HPP

#include <thread>
#include <vector>

#include "utils/configs.hpp"
#include "apis/receive.hpp"
#include "apis/send.hpp"

namespace tcp2serial {
class driver_manager {
        configs _cfg;
        // Pool of threads used for receiving data from the data source and sending to the predefined destination
        std::vector<std::thread> _worker_threads;

        std::shared_ptr<send> _send_api;
        std::shared_ptr<receive> _receive_api;
        void receive_to_send_worker(std::shared_ptr<send> send_api, std::shared_ptr<receive> receive_api);
    public:
        ~driver_manager() = default;
        driver_manager(const driver_manager& dm)=delete;
        driver_manager& operator=(const driver_manager& dm)=delete;
        driver_manager(configs cfg);
        void init();
        void run();
};
}
#endif // DRIVER_MANAGER_HPP
