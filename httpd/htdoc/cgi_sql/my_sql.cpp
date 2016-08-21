/*************************************************************************
	> File Name: my_sql.cpp
	> Author: cyx
	> Mail: cyx764@163.com 
	> Created Time: 2016年08月13日 星期六 18时38分38秒
 ************************************************************************/

#include"my_sql.h"
using namespace std;

mysql_api::mysql_api()
{
	_coon=mysql_init(NULL);
	_coon=mysql_real_connect(_coon,"localhost","cyx",NULL,"friends",0,NULL,0);
	mysql_set_character_set(_coon,"utf8");
	if(_coon==NULL)
	{
		cout<<"Link default"<<endl;
	}

}
mysql_api::~mysql_api()
{
	mysql_close(_coon);

}
void mysql_api::InsertSql(const char *data)
{
	int ret=mysql_query(_coon,data);

}
MYSQL_RES* mysql_api::SelectSql()
{
    int ret=mysql_query(_coon,"select*from info");
	return STDCALL mysql_store_result(_coon);

}
void mysql_api::DeleteSql(const char* data)
{
	int ret=mysql_query(_coon,data);

}
