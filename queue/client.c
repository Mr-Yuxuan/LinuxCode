#include"client.h"
int main()
{
	int msg_id=get_q_id();
	while(1)
	{
		char buf[SIZE];
		memset(buf,'\0',SIZE);
		printf("ENTER: ");
		gets(buf);
		send_msg(msg_id,buf,CLIENT);
        memset(buf,'\0',SIZE);
		recv_msg(msg_id,buf,SERVER);
		printf("SERVER: %s\n",buf);

	}
	return 0;
}
