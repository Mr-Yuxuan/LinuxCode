#include"server.h"
Server::Server(const std::string& _ip,const int& _port)
	:ip(_ip)
	 ,port(_port)
	 ,sock(-1)
{}
Server::~Server()
{
	if(sock!=-1)
	{
		close(sock);
	}
}
void Server::_init()
{
	sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{
		print_log(strerror(errno),__FUNCTION__,__LINE__);
		exit(1);
	}
	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_port=htons(port);
	local.sin_addr.s_addr=inet_addr(ip.c_str());

	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		print_log(strerror(errno),__FUNCTION__,__LINE__);
		exit(1);
	}

}
ssize_t Server::_recv(std::string &out)
{
	struct sockaddr_in client;
	socklen_t len=sizeof(client);
	char buf[_SIZE_];
	memset(buf,'\0',sizeof(buf));
	ssize_t _ret=recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&client,&len);
	if(_ret<0)
	{
		print_log(strerror(errno),__FUNCTION__,__LINE__);
	}
	else
	{
        out=buf;
		//std::cout<<out<<std::endl;
		pool.data_put(out);
		add_user(client);
        del_user(client,out); 

	}
	return _ret;

}
ssize_t Server::_send(std::string &in,struct sockaddr_in &cli,const socklen_t &len)
{
	ssize_t _ret=sendto(sock,in.c_str(),in.size(),0,(struct sockaddr*)&cli,len);
	if(_ret<0)
	{
		print_log(strerror(errno),__FUNCTION__,__LINE__);
    }
	return _ret;

}
void Server::broadcast()
{
	std::string in;
	pool.data_get(in);
	
	
	std::map<std::string,struct sockaddr_in>::iterator iter=oline_user.begin();
	for(;iter!=oline_user.end();++iter)
	{
		_send(in,iter->second,sizeof(iter->second));

	}

}
void Server::add_user(struct sockaddr_in &client)
{
	std::string ip_key=inet_ntoa(client.sin_addr);
	std::map<std::string,struct sockaddr_in>::iterator iter=oline_user.find(ip_key);
	if(iter==oline_user.end())
	{
		//std::cout<<"new user: "<<ip_key<<std::endl;
		oline_user.insert(std::pair<std::string,struct sockaddr_in>(ip_key,client));
	}
	return;


}
void Server::del_user(struct sockaddr_in &client,const std::string &str)
{
	std::string ip_key=inet_ntoa(client.sin_addr);
	udp_data data;
	data.to_val(str);
	std::string s;
	data.get_cmd(s);
	if(s=="q")
{
	std::map<std::string,struct sockaddr_in>::iterator iter=oline_user.find(ip_key);
	if(iter==oline_user.end())
	{
		return;
	}
	else
	{
		oline_user.erase(ip_key);
		return;
	}
}
return;

}
