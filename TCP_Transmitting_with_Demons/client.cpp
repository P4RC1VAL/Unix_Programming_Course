#include "lib_dbg.c"

int main()
{
	dbg_open();
	
	char* buf;
	dbg_read(buf);

	printf("Client got msg [%s]", buf);

	dbg_close();
}
