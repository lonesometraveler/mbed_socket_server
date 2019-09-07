#ifndef __SOCKETSERVER_H__
#define __SOCKETSERVER_H__

#include "mbed.h"

/**
 * @brief macro function for debug
 *
 */
#define NET_DEBUG 1
#ifdef NET_DEBUG 
#define NDBG(fmt, ...)                             \
    do {                                           \
        printf("[NDBG] %s %s, line:%d\r\n",        \
               __func__, __FILE__, __LINE__);      \
        printf(fmt, ##__VA_ARGS__);                \
    } while (0)
#else 
#define NDBG(...) 
#endif
 
class SocketServer {

public:

	SocketServer(int port);

	virtual ~SocketServer();

	/**
	 * @brief network settings.
	 *
	 */
	typedef struct network_setting_s {
		int timeout = 1000;	// Timeout in milliseconds
		int backlog = 1;	// Number of pending connections that can be queued simultaneously, defaults to 1
	} network_setting_s;

	network_setting_s setting;

	/**
	 * @brief buffer pointer
	 * @return pointer to buffer
	 *
	 */
	uint8_t* getDataPtr();

	/**
	 * @brief Network interface init.
	 * @return error | NSAPI_ERROR_OK = 0, negative numbers for errors
	 * https://github.com/ARMmbed/mbed-os/blob/master/features/netsocket/nsapi_types.h
	 */
	nsapi_error_t netInit(const char* ip, const char* gateway, const char* mask);

	/**
	 * @brief attach callback.
	 * @param function   This function will be called when _mycb.call() is called.
	 *
	 */
	void attach(Callback<void(int)> function);
	
protected:
	NetworkInterface* net;
	uint8_t buffer[768]; // TODO: define the size with config. https://os.mbed.com/docs/mbed-os/v5.13/reference/configuration.html
	Callback<void(int)> _mycb;
	int _port;

private:
	/**
	 * @brief Network interface status change callback.
	 *
	 */
	void statusCallback(nsapi_event_t status, intptr_t param);
};
#endif