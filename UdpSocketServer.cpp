#include "UdpSocketServer.h"

static Thread thread(osPriorityNormal, 1024);

UdpSocketServer::UdpSocketServer(int port): SocketServer(port) {
    memset(buffer, 0, (sizeof buffer / sizeof buffer[0]));
}

osStatus UdpSocketServer::run() {
    osStatus result = thread.start(callback(this, &UdpSocketServer::loop));
    return result;
}

void UdpSocketServer::loop() {

    UDPSocket listener;
    bool running = true;

    listener.open(net);
    nsapi_error_t error = listener.bind(_port);
    if (error != NSAPI_ERROR_OK) {
        NDBG("error %d \r\n", error);
        running = false;
    } else {
        NDBG("Listening on port %d \r\n", _port);
    }

    while (running) {
        
        nsapi_size_or_error_t size = listener.recv(buffer, sizeof(buffer));

        if (size > 0) {
            buffer[size] = '\0';
            NDBG("size %d\r\n", size);
            _mycb.call(size); // callback
        }

        if (size < 0) {
            NDBG("error %d\r\n", size);
        }
    }

    listener.close();
}
