#include "TcpSocketServer.h"

static Thread thread(osPriorityNormal, 1024);

TcpSocketServer::TcpSocketServer(int port): SocketServer(port) {
    memset(buffer, 0, (sizeof buffer / sizeof buffer[0]));
}

osStatus TcpSocketServer::run() {
    osStatus result = thread.start(callback(this, &TcpSocketServer::loop));
    return result;
}

void TcpSocketServer::loop() {

    TCPSocket listener;
    TCPSocket* client;

    listener.open(net);
    nsapi_error_t error = listener.bind(_port);
    if (error != NSAPI_ERROR_OK) {
        NDBG("error %d \r\n", error);
    }

    error = listener.listen(this->setting.backlog);
    if (error != NSAPI_ERROR_OK) {
        NDBG("error %d \r\n", error);
    }

    client = listener.accept(NULL);
    client->set_timeout(this->setting.timeout);
    
    while (true) {
        
        nsapi_size_or_error_t size = client->recv(buffer, sizeof(buffer));

        if (size > 0) {
            buffer[size] = '\0';
            _mycb.call(size); // callback
        }

        if (size == 0) {
            client->close();

            client = listener.accept(NULL);
            client->set_timeout(this->setting.timeout);
        } 
    }
}