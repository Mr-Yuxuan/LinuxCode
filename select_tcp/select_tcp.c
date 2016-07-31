#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/select.h>
int SockCreat(const char* _ip,int _port)
{
	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("socket\n");
		exit(2);
	}
	int opt=1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_port=htons(_port);
	local.sin_addr.s_addr=inet_addr(_ip);


	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		perror("bind\n");
		exit(3);
	}
	if(listen(sock,5)<0)
	{
		perror("listen\n");
		exit(4);
	}
	return sock;

}
int fds[64];
const int fds_nums=sizeof(fds)/sizeof(fds[0]);
int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("error:%s [ip] [port]\n",argv[0]);
		exit(1);
	}
	int listen_sock=SockCreat(argv[1],atoi(argv[2]));
	fd_set rset;
	FD_ZERO(&rset);
	FD_SET(listen_sock,&rset);
	int max_fd;
    int i=0;
	for(;i<fds_nums;++i)
	{
        fds[i]=-1;
	}
	fds[0]=listen_sock;
	while(1)
	{
		i=0;
		max_fd=-1;
		for(;i<fds_nums;++i)
		{
           if(fds[i]>0)
		   {
			   FD_SET(fds[i],&rset);
			   max_fd=max_fd<fds[i]?fds[i]:max_fd;
		   }
		}
	    struct timeval time={0,500};
		switch(select(max_fd+1,&rset,NULL,NULL,NULL)){
			case -1:
				   perror("select\n");
		 		   break;
			case 0:
		 		   printf("timeout ...\n");
				   break;
			default:
				   //printf("hah\n");
				   for(i=0;i<fds_nums;++i){
	 				   if(i==0&& (FD_ISSET(listen_sock,&rset)))
					   {
						   struct  sockaddr_in peer;
				           socklen_t len=sizeof(peer);
                           int new_fd=accept(fds[0], (struct sockaddr*)&peer, &len);
		                   if(new_fd>0)
						   {
 							   printf("Get new fd\n");
							    int  j=0;
							   for(;j<fds_nums;++j)
							   { 
 								     if(fds[j]==-1)
								   {
 								  	   fds[j]=new_fd;
									   break;
								   }
							   }
							   if(j==fds_nums)
								   close(new_fd);
							   
						   }}
						   else
						   {
 							   if(FD_ISSET(fds[i] ,&rset))
							   {
 								   char  buf[1024];
								   memset(buf,'\0',sizeof(buf));
								   ssize_t _s=read(fds[i],buf,sizeof(buf)-1);
								   if(_s<0){
 									    perror("read\n");
									   exit(5);
								   }
								   if(_s==0)
								   {
 									   printf("client done...\n");
									   close(fds[i]);
									   fds[i]=-1;
								   }
							   
								   else
								   {
									   printf("Client# %s",buf);

								   }
								   


							   }
						   

                   }
		}
				   break;
		}
	}
	return 0;
}
