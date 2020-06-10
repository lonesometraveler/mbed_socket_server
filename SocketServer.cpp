#include "SocketServer.h"

static void defaultCallback(int count) {
    NDBG("rcvd %d bytes\r\n", count);
}

SocketServer::SocketServer(int port) {
    _port = port;
    _mycb = defaultCallback;
    net = NetworkInterface::get_default_instance();
    net->attach(callback(this, &SocketServer::statusCallback));
}

SocketServer::~SocketServer() {}

uint8_t* SocketServer::getDataPtr() {
    return &buffer[0];
}

nsapi_error_t SocketServer::netInit(const char* ip, const char* gateway, const char* mask) {

    nsapi_error_t error = net->set_network(ip, mask, gateway);
    if (error != NSAPI_ERROR_OK) {
        return error;
    }

    net->set_blocking(false);
    
    error = net->connect();
    if (error != NSAPI_ERROR_OK) {
        return error;
    }

    return NSAPI_ERROR_OK;
}

void SocketServer::attach(Callback<void(int)> function) {
    if (function) {
        _mycb = function;
    } else {
        _mycb = defaultCallback;
    }
}

void SocketServer::statusCallback(nsapi_event_t status, intptr_t param) {
    switch (param) {
    case NSAPI_STATUS_LOCAL_UP:
        NDBG("Local IP address set!\r\n");
        break;
    case NSAPI_STATUS_GLOBAL_UP:
        {
            SocketAddress a;
            net->get_ip_address(&a);
            NDBG("Global IP address set! [%s] \r\n", a.get_ip_address() ? a.get_ip_address() : "None");
        }
        break;
    case NSAPI_STATUS_DISCONNECTED:
        NDBG("No connection to network!\r\n");
        break;
    case NSAPI_STATUS_CONNECTING:
        NDBG("Connecting to network...\r\n");
        break;
    default:
        NDBG("Not supported");
        break;
    }
}