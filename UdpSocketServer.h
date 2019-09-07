#ifndef __UDP_SOCKETSERVER_H__
#define __UDP_SOCKETSERVER_H__

#include "SocketServer.h"

class UdpSocketServer: public SocketServer {

public:

	UdpSocketServer(int port);

	/**
	 * @brief open a listening port and wait for a connection on a thread
	 * @return os status | osOK = 0, osErrorNoMemory = -5
	 */
	osStatus run(void);

private:
	/**
	 * @brief Thread loop.
	 *
	 */
	void loop(void);

};
#endif