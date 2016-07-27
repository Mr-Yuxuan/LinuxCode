#include"server.h"
int main()
{
	int msg_id=create_q_id();
	while(1)
	{

		char buf[SIZE];
		memset(buf,'\0',SIZE);
	    recv_msg(msg_id,buf,CLIENT);
		printf("CLIENT: %s\n",buf);
		memset(buf,'\0',SIZE);
		printf("ENTER: ");
		gets(buf);
		send_msg(msg_id,buf,SERVER);
	}
	destory(msg_id);
	return 0;
}
