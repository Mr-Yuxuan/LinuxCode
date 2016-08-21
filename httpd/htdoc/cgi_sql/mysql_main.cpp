/*************************************************************************
	> File Name: mysql_main.cpp
	> Author: cyx
	> Mail: cyx764@163.com 
	> Created Time: 2016年08月13日 星期六 18时59分46秒
 ************************************************************************/

#include"my_sql.h"
using namespace std;
int main()
{
	mysql_api a;
//	a.InsertSql("INSERT INTO info(name, age, school)VALUES(\"阿立\",5,\"陕西科技大学\");");
	MYSQL_RES* ret=a.SelectSql();
	MYSQL_FIELD* cow=NULL;
	unsigned int rows=mysql_num_fields(ret);
	int i=0;
	for(;cow=mysql_fetch_field(ret);++i)
	{
		cout<<cow->name<<" ";
	}
	cout<<endl;
	MYSQL_ROW row=mysql_fetch_row(ret);
	while(row)
	{
		for(i=0;i<rows;++i)
		{
			cout<<row[i]<<" "<<" ";
		}
		cout<<endl;
		row=mysql_fetch_row(ret);
	}

	

	//cout<<row[0]<<endl;
	return 0;
}

