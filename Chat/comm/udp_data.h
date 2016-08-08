#pragma once
#include"my_json.h"
#include<iostream>
#include<string>
class udp_data
{
public:
	void set_nick_name(std::string &_nick);
	void set_school(std::string &_school);
	void set_msg(std::string &_msg);
	void set_cmd(std::string &_cmd);
	void get_cmd(std::string &_cmd);
	void get_msg(std::string &_msg);
	void get_nick_name(std::string &_nick);
	void get_school(std::string &_school);
	void to_val(const std::string& str);
	void to_str(std::string& str);

private:
	std::string nick_name;
	std::string school;
	std::string cmd;
	std::string msg;
};
