#include"my_sql.h"
using namespace std;
void insert(char* vals)
{
	
	char* end=vals+strlen(vals)-1;
	char *buf[4];
	buf[3]=NULL;
	int index=2;
	while(index>=0)
	{
		if(*end=='=')
		{
			buf[index--]=end+1;
        }
		if(*end=='&')
		{
			*end='\0';
		}
		end--;
	}
	string sql("INSERT INTO info(name, age, school)VALUES(\"");
	sql+=buf[0];
	sql+="\",";
	sql+=buf[1];
	sql+=",\"";
	sql+=buf[2];
	sql+="\");";
	//cout<<sql.c_str()<<endl;
	mysql_api data;
	data.InsertSql(sql.c_str());
	cout<<"Insert Sucessful"<<endl;


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
	insert(vals);
	return 0;
}
