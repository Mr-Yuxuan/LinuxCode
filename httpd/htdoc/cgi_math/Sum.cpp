#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include"BigData.h"

void math_add(char *vals)
{
	//printf("aaaaaaa\n");
	//printf("%s",getenv("VAL"));
	char* end=vals+strlen(vals)-1;
	char *buf[3];
	buf[2]=NULL;
	int index=1;
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
	BigData s1(buf[0]);
	BigData s2(buf[1]);
    cout<<"<p>"<<s1<<"+"<<s2<<"=";
	cout<<s1+s2<<"</p>";


}
int main()
{
	char method[1024];
	char vals[1024];
	memset(method,'\0',sizeof(method));
	memset(vals,'\0',sizeof(vals));

	printf("<html>\n");
	printf("<head><h1>MATH_ADD</h1></head>\n");
	printf("<body>\n");

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
	//printf("<html>\n");
	//printf("<head>MATH_ADD</head>\n");
	//printf("<body>\n");

	math_add(vals);
	printf("</body>\n");
	printf("</html>\n");


	return 0;
}

