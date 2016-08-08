
#include"udp_data.h"

void udp_data::set_nick_name(std::string &_nick)
	{
          nick_name=_nick;
	}
void udp_data::set_school(std::string &_school)
	{
          school=_school;
	}
void udp_data::set_msg(std::string &_msg)
	{
          msg=_msg;
	}
void udp_data::set_cmd(std::string &_cmd)
	{
          cmd=_cmd;
	}
void udp_data::get_nick_name(std::string &_nick)
	{
          _nick=nick_name;
	}
void udp_data::get_msg(std::string &_msg)
	{
          _msg=msg;
	}
void udp_data::get_school(std::string &_school)
	{
          _school=school;
	}
void udp_data::get_cmd(std::string &_cmd)
	{
          _cmd=cmd;
	}
void udp_data::to_val(const std::string& str)
	{
        
		Json::Value val;
		my_json::unserialize(val,str);
        nick_name=val["nick_name"].asString();
        school=val["school"].asString();
        cmd=val["cmd"].asString();
        msg=val["msg"].asString();

	}
void udp_data::to_str(std::string& str)

	{
		Json::Value val;
        val["nick_name"]=nick_name;
        val["school"]=school;
        val["cmd"]=cmd;
        val["msg"]=msg;
		my_json::serialize(val,str);
	}
