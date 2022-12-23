#include "lib_dbg.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

struct pollfd fds[2];

void poller(int socketIn, std::string srcIP, int port)
{
	// Initialize the fds to 0
	memset(fds, 0, sizeof(fds));

	// Wait in ms before poll times out. -1 for infinite
	int timeout = 15000;

	fds[0].fd = socketIn;

	while (true)
	{
		fds[0].events = POLLIN;
		fds[1].fd = socketOut;
		fds[1].events = POLLIN;

		if (inWritePending)
		{
			fds[1].events = POLLOUT;
			fds[0].events = 0;
		}

		if (outWritePending)
		{
			fds[0].events = POLLOUT;
			if (!inWritePending)
			{
				fds[1].events = 0;
			}
		}
	}
}

int dbg_open()
{
	if (poll(fds, 2, timeout) > 0)
	{
		if (fds[0].revents & (POLLNVAL | POLLERR | POLLHUP))
		{
			clientdisconnected();
			break;
		}

		if (fds[1].revents & (POLLNVAL | POLLERR | POLLHUP))
		{
			serverdisconnected();
			break;
		}
	}
}


void dbg_write(const char* msg)
{
	if (fds[0].revents & POLLIN)
	{
		clientread();
		break;
	}

	if (fds[1].fd != 0 && fds[1].revents & POLLOUT)
	{
		serverwrite();
	}
}

void dbg_read(char* msg)
{
	if(fds[1].fd!=0 && fds[1].revents & POLLIN)
	{
		serverread();
	}

	if(fds[0].revents & POLLOUT)
	{
		clientwrite();
		break;
	}
}

void dbg_close()
{
	closeconn();
}
