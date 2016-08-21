#pragma once
#include<iostream>
#include<string>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include"mysql/mysql.h"

class mysql_api
{
public:
	mysql_api();
	~mysql_api();
	void InsertSql(const char *data);
	MYSQL_RES* SelectSql();
	void DeleteSql(const char* data);

private:
	MYSQL* _coon;

};
