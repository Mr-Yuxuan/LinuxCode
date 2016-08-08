/*************************************************************************
	> File Name: Client.cpp
	> Author: cyx
	> Mail: cyx764@163.com 
	> Created Time: 2016年07月08日 星期五 00时57分38秒
 ************************************************************************/

#include"client.h"
Client::Client(const std::string& _remote,const int& _port)
	:remote_ip(_remote)
	 ,port(_port)
	 ,sock(-1)
{}
Client::~Client()
{
  if(sock!=-1)
   {
	   close(sock);
   }
}
void Client::del_flist(const std::string &str)
{
	std::vector<std::string>::iterator iter=flist.begin();
	for(;iter!=flist.end();)
	{
		if(*iter==str)
		{
			iter=flist.erase(iter);
		}
		else
			++iter;
	}
}
void Client::init()
{
    sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{
		print_log(strerror(errno),__FUNCTION__,__LINE__);
		exit(1);
	}
	return;

}
ssize_t Client::_recv(std::string &out)
{
	
	struct sockaddr_in remote;
	socklen_t len=sizeof(remote);
	char buf[_SIZE_];
	memset(buf,'\0',sizeof(buf));
	ssize_t _ret=recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&remote,&len);
	if(_ret<0)
	{
		print_log(strerror(errno),__FUNCTION__,__LINE__);
	}
	else
	{
		out=buf;
	}
	return _ret;

}
ssize_t Client::_send(std::string &in)
{
	struct sockaddr_in remote;
	remote.sin_family=AF_INET;
	remote.sin_port=htons(port);
    remote.sin_addr.s_addr=inet_addr(remote_ip.c_str());  
	socklen_t len=sizeof(remote);
    ssize_t _ret=sendto(sock,in.c_str(),in.size(),0,(struct sockaddr*)&remote,len);
    if(_ret<0)
	{
		print_log(strerror(errno),__FUNCTION__,__LINE__);

	}
	return _ret;

}
void Client::add_flist(const std::string& str)
{
	int i=0;
	for(;i<flist.size();++i)
	{
		if(str==flist[i])
			return;
	}
	flist.push_back(str);
	return;
}
