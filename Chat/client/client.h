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
#include<vector>
#include"chat_win.h"
#include"udp_data.h"
#include<curses.h>
#include<sstream>
class Client
{
public:
	void add_flist(const std::string &str);
	void del_flist(const std::string &str);
	Client(const std::string &_remote=_IP_,const int &_port=_PORT_);
	~Client();
	ssize_t _recv(std::string &out);
	ssize_t _send(std::string &in);
	void init();
	std::vector<std::string> flist;
private:
	int sock;
	std::string remote_ip;
	int port;

};
