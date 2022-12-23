#include "lib_dbg.c"

int main()
{
	dbg_open();
	
	char* buf;
	dbg_read(buf);

    while (true)
    {
        if ((rv = poll(fds, 1, 100) > 0))
        {

            if (fds[0].revents & POLLIN)
            {
                recv(sockfd, buff, 200, 0);
                printf("From Server : %s", buff);
                bzero(buff, sizeof(buff));

            }
            else if (fds[0].revents & POLLOUT)
            {
                puts(buff);
                strcpy(buff, "HELLO WORLD");
                write(sockfd, buff, sizeof(buff));
                break;
            }
        }
    }

	dbg_close();
}
