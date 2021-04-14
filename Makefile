CFLAGS=-pthread 
LDFLAGS=-lpthread
all: tcp2serial 

tcp2serial: main.o configs.o semaphore.o ser_port.o tcp_server.o driver_manager.o
	arm-linux-gnueabi-g++ --std=c++11 -static-libstdc++ main.o configs.o semaphore.o ser_port.o tcp_server.o driver_manager.o -o tcp2serial  $(LDFLAGS) 

main.o: main.cpp
	arm-linux-gnueabi-g++ -c --std=c++11 $(CFLAGS) main.cpp -o main.o 

semaphore.o: utils/semaphore.cpp 
	arm-linux-gnueabi-g++ -c --std=c++11 $(CFLAGS) utils/semaphore.cpp -o semaphore.o

configs.o: utils/configs.cpp 
	arm-linux-gnueabi-g++ -c --std=c++11 $(CFLAGS) utils/configs.cpp -o configs.o

ser_port.o: drivers/ser_port.cpp 
	arm-linux-gnueabi-g++ -c --std=c++11 $(CFLAGS) drivers/ser_port.cpp -o ser_port.o

tcp_server.o: drivers/tcp_server.cpp
	arm-linux-gnueabi-g++ -c --std=c++11 $(CFLAGS) drivers/tcp_server.cpp -o tcp_server.o

driver_manager.o: driver_manager.cpp
	arm-linux-gnueabi-g++ -c --std=c++11 $(CFLAGS) driver_manager.cpp -o driver_manager.o

clean:
	rm -f *.out *.o tcp2serial 
