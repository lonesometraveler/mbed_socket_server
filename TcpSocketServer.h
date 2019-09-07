#ifndef __TCP_SOCKETSERVER_H__
#define __TCP_SOCKETSERVER_H__

#include "SocketServer.h"

class TcpSocketServer: public SocketServer {

public:

	TcpSocketServer(int port);

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