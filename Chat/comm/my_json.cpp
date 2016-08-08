#include"my_json.h"
void my_json::serialize(Json::Value &val,std::string& str)
{
	Json::FastWriter write;
	str=write.write(val);
}
void my_json::unserialize(Json::Value& val,const std::string& str)
{
   Json::Reader read;
   read.parse(str,val,false);
}
