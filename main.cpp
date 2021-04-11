#include <iostream>
#include "drivers/tcp_server.hpp"
#include "drivers/ser_port.hpp"
int main() {
    tcp2serial::ser_port sp;
    sp.init("/dev/pts/3","9600");
    sp.send("qwertyuiop[asdfghjkl;");
    return 0;
}

