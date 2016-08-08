#pragma once
#include<iostream>
#include<json/json.h>
class my_json
{
public:
	static void serialize(Json::Value &val,std::string& str);
	static void unserialize(Json::Value& val,const std::string& str);
};
