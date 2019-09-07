# mbed Socket Server

Socket Server (TCP and UDP) library for mbed projects.

### Prerequisites

mbed OS 5


### Installing

Add this library to a mbed project.

```
mbed add https://github.com/lonesometraveler/mbed_socket_server.git
```


## Usage

1. Create an instance of ```TcpSocketServer``` or ```UdpSocketServer```. 
2. Initialize network interface with ```netInit(const char* ip, const char* gateway, const char* mask);```
3. If there is no error, let the server ```run()```.

```SocketServer``` has a buffer to store incoming data, which you can access via pointer. ```getDataPtr()``` returns a pointer address. Use this to access the data.

You can attach a callback to ```SocketServer```. If you don't attach any, a default callback function will be called when the server instance receives data.

### Example

Here is a ```TcpSocketServer``` example. When the server receives data, a callback function is called.

```c++
#include "mbed.h"
#include "TcpSocketServer.h"

EventQueue *queue = mbed_event_queue();

const int SocketServer_PORT = 10002;
TcpSocketServer server(SocketServer_PORT);
uint8_t* data;

void onSocketRcvd(int length) {
    printf("%s\r\n", data);
}

int main() {
    
    int err = server.netInit("192.168.1.162", "192.168.1.1", "255.255.255.0");
    if (err == NSAPI_ERROR_OK) {
    	data = server.getDataPtr();	// Access SocketServer's data buffer via pointer
        server.attach(&onSocketRcvd);	// Attach a callback. It will be called when SocketServer receives data.
		server.run();
    }

    queue->dispatch_forever();
}
```

```UdpSocketServer``` works exactly the same way. Create an instance and let it run just like ```TcpSocketServer```.

```c++
#include "UdpSocketServer.h"

UdpSocketServer server(SocketServer_PORT);
```

