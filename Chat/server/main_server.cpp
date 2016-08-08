#include"server.h"
static void usage(const char *proc)
{
	std::cout<<"Usage: "<<proc<<"[ip] [port]"<<std::endl;
}
void *recv_product(void *arg)
{
	//std::cout << __func__ << __LINE__ <<std::endl;
	Server *_serp=(Server*)arg;
	bool done=false;
	std::string _msg;
	while(!done)
	{
		_serp->_recv(_msg);
    }
	return NULL;

}
void *send_comsum(void *arg)
{
	Server *_serp=(Server*)arg;
	bool done=false;
	
	while(!done)
	{
		_serp->broadcast();
    }
	return NULL;

}
int main(int argc,char *argv[])
	
{
	//daemon(0,0);
	if(argc<3)
		std::cout<<"error:worng parameter"<<std::endl;
	std::string ip=argv[1];
	int port=atoi(argv[2]);

	Server ser(ip,port);
	ser._init();
	
	pthread_t th1,th2;
	pthread_create(&th1,NULL,recv_product,(void*)&ser);
	pthread_create(&th2,NULL,send_comsum,(void*)&ser);

	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
	//std::string out;
	//while(1)
	
	//{
	//	ser._recv(out);
	  //  std::cout<<"Server: "<<out<<std::endl;
	//}
	return 0;
}
