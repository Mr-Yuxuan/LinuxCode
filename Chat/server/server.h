#pragma once
#include<iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include"comm.h"
#include"data_pool.h"
#include"udp_data.h"
#include<map>
class Server
{
	void add_user(struct sockaddr_in &client);
	void del_user(struct sockaddr_in &client,const std::string &str);
public:
	Server(const std::string &_ip=_IP_,const int &_port=_PORT_);
	~Server();
	void _init();
	ssize_t _recv(std::string &out);
	ssize_t _send(std::string &in,struct sockaddr_in &cli,const socklen_t &len);
	void broadcast();

private:
	int sock;
	std::string ip;
	int port;
	data_pool pool;
	std::map<std::string,struct sockaddr_in> oline_user;

};
