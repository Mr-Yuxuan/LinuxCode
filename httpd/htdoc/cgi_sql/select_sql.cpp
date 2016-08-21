/*************************************************************************
	> File Name: mysql_main.cpp
	> Author: cyx
	> Mail: cyx764@163.com 
	> Created Time: 2016年08月13日 星期六 18时59分46秒
 ************************************************************************/

#include"my_sql.h"
using namespace std;
void Select()
{
	mysql_api a;
	MYSQL_RES* ret=a.SelectSql();
	MYSQL_FIELD* cow=NULL;
	unsigned int rows=mysql_num_fields(ret);
	int i=0;
	cout<<"<tr>";
	for(;cow=mysql_fetch_field(ret);++i)
	{
		cout<<"<td>";
		cout<<cow->name;
		cout<<"</td>";
	}
	cout<<"</tr>";
	MYSQL_ROW row=mysql_fetch_row(ret);
	while(row)
	{
		cout<<"<tr>";
		for(i=0;i<rows;++i)
		{
			cout<<"<td>";
			cout<<row[i];
			cout<<"</td>";
		}
		cout<<"</tr>";
		row=mysql_fetch_row(ret);
	}

	

	//cout<<row[0]<<endl;
	return;
}

int main()
{
	
	char method[1024];
	char vals[1024];
	memset(method,'\0',sizeof(method));
	memset(vals,'\0',sizeof(vals));
	strcpy(method,getenv("METHOD"));
	if(strcmp(method,"GET")==0)
	{
		strcpy(vals,getenv("VAL"));
	}
	else
	{
		int i=0;
		char c='\0';
		int lenth=atoi(getenv("CONTENT_LENTH"));
		for(;i<lenth;++i)
		{
			read(0,&c,1);
			vals[i]=c;
		}
		
	}
	cout<<"<html>";
	cout<<"<body>";
	cout<<"<table border=\"1\">";	
	Select();
	cout<<"</table>";
	cout<<"</body>";
	cout<<"</html>";
	return 0;
}
