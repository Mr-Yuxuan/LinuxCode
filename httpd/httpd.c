#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
#include<sys/sendfile.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/epoll.h>
#define _SIZE_ 1024
//#define _DEBUG_
int Creat_sock(const char*_ip,int _port)
{
	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("socket\n");
		exit(2);
	}
	int opt=1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_port=htons(_port);
	local.sin_addr.s_addr=inet_addr(_ip);
	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		perror("bind\n");
		exit(3);
	}
	if(listen(sock,5)<0)
	{
		perror("listen\n");
		exit(4);
	}
	return sock;

}
static void clear_header(int sock)
{
	int ret=-1;
	char buf[_SIZE_];
	do{
		ret=get_line(sock,buf,sizeof(buf));
	}while((ret>0)&&(strcmp(buf,"\n")!=0));

}
static void echo_errno(int sock,int eno)
{
	char err_des[30];
	memset(err_des,'\0',sizeof(err_des));
	switch(eno)
	{
		case 301:
			strcpy(err_des,"Removed");
		    break;
		case 404:
            strcpy(err_des,"Not Found");
			break;
		case 403:
			strcpy(err_des,"Forbid");
		    break;
		case 500:
		    strcpy(err_des,"Inner Error");
			break;
		case 501:
			strcpy(err_des,"Not execute");
			break;
		default:
			break;
	}
    //send(sock,err_des,strlen(err_des),0);

}
void echo_cgi(int sock,const char* path,const char* method,const char* val)
{
	//printf("aaaaaaa\n");
	char buf[_SIZE_];
	int content_lenth=-1;
	int ret=-1;
	//char path_env[_SIZE_];
	char method_env[_SIZE_];
	char val_env[_SIZE_];
	char content_lenth_env[_SIZE_];
	memset(content_lenth_env,'\0',sizeof(content_lenth_env));
	if(strcmp(method,"GET")==0)
	{
		clear_header(sock);
	    sprintf(val_env,"VAL=%s",val);
		putenv(val_env);

	}
	else{
		do{
			ret=get_line(sock,buf,sizeof(buf));
			if(ret>0&&strncasecmp(buf,"Content-Length: ",16)==0)
			{
				content_lenth=atoi(&buf[16]);
			}
		}while(ret>0&&(strcmp(buf,"\n")!=0));
		if(content_lenth==-1)
		{
			echo_errno(sock,500);
			return;
		}
	    sprintf(content_lenth_env,"CONTENT_LENTH=%d",content_lenth);
		putenv(content_lenth_env);
    }
	
    sprintf(method_env,"METHOD=%s",method);
	putenv(method_env);
	
	printf("%s\n",method_env);
	printf("%s\n",path);
	printf("%s\n",val_env);
	//printf("%s\n",url);

	int pipe_input[2];
	if(pipe(pipe_input)<0)
	{
		echo_errno(sock,500);
		return;
	}
	int pipe_output[2];
	if(pipe(pipe_output)<0)
	{
		echo_errno(sock,500);
		return;
	}


	pid_t id=fork();
	//printf("%d\n",id);
	if(id==0)
	{
		close(pipe_input[1]);
		close(pipe_output[0]);
	    
		dup2(pipe_input[0],0);
	    dup2(pipe_output[1],1);
		//printf("%s",path);

        execl(path,path,NULL);
		//printf("mm\n");
		//close(pipe_input[0]);
		//close(pipe_output[1]);
		exit(1);



	}else
	{
		close(pipe_input[0]);
		close(pipe_output[1]);
		char c='\0';
		int i=0;
		if(content_lenth>0)
		{
			for(;i<content_lenth;++i)
		  {
			   recv(sock,&c,1,0);
			   write(pipe_input[1],&c,1);
		  }
		}
		char* status="HTTP/1.0 200 Ok\r\n\r\n";
		send(sock,status,strlen(status),0);
		while(read(pipe_output[0],&c,1)>0)
		{
			//printf("%c",c);
			send(sock,&c,1,0);
	    }
	    //printf("mm\n");	
		close(pipe_input[1]);
        close(pipe_output[0]);
		waitpid(id,NULL,0);
	}




}
int get_line(int sock,char* buf,int size)
{
	if(!buf||size<0)
	{
		return -1;
	}
	char c='\0';
	int n=0;
	int i=0;
	while((i<size-1)&&(c!='\n'))
	{
		n=recv(sock,&c,1,0);
		if(n>0)
		{
			if(c=='\r')
			{
				n=recv(sock,&c,1,MSG_PEEK);
				if(n>0&&c=='\n')
					n=recv(sock,&c,1,0);
				else
				    c='\n';
			}
			buf[i++]=c;
		}else
		   buf[i]='\n';
    }
	buf[i]='\0';
	return i;
}
void echo_www(int sock,const char* path,int size)
{
	printf("%s\n",path);
	int fd=open(path,O_RDONLY);
	if(fd<0)
	{
		echo_errno(sock,500);
		return;
	}
	char buf[_SIZE_];
	memset(buf,'\0',sizeof(buf));
	sprintf(buf,"HTTP/1.1 200 OK\r\n\r\n");
	send(sock,buf,strlen(buf),0);
	if(sendfile(sock,fd,NULL,size)<0)
	{
		echo_errno(sock,404);
		return;
	}
	close(fd);


}
void *htpdaccept(void *arg)
{
	int sock=(int)arg;
	int ret=-1;
	char buf[_SIZE_];
    char path[_SIZE_];
	char url[_SIZE_];
	char method[_SIZE_];
	char val[_SIZE_];
	int cgi=0;

	memset(buf,'\0',sizeof(buf));
	memset(path,'\0',sizeof(path));
	memset(method,'\0',sizeof(method));
	memset(url,'\0',sizeof(url));
	memset(val,'\0',sizeof(val));
    //printf("AAAAAAA\n");
#ifdef _DEBUG_
	
    do{
		ret=get_line(sock,buf,sizeof(buf));
		printf("%s",buf);
		fflush(stdout);
	}while(ret>0&&(strcmp(buf,"\n")!=0));
#else

	ret=get_line(sock,buf,sizeof(buf));
	//printf("%s",buf);

	int i=0;
	int j=0;

	do{
		method[j++]=buf[i++];
	}while((buf[i]!='\0')&&(!isspace(buf[i])));
	method[j]='\0';
	j=0;
	while(isspace(buf[i])){
	i++;
	}
	do{
		url[j++]=buf[i++];

	}while(!isspace(buf[i]));
	url[j]='\0';
	if(strcasecmp(method,"GET")==0)
	{
		int k=0;
		int n=0;
		do{
           path[k++]=url[n++];

		}while(url[n]!='\0'&&url[n]!='?');
        path[k]='\0'; 
	    //sprintf(path,"htdoc%s",path);
		if(url[n]=='?')
		{
			k=0;
			url[n]='\0';
			n++;
            do{
				val[k++]=url[n++];
			}while(url[n]!='\0');
			val[k]='\0';
			cgi=1;

		}
	}
	if(strcasecmp(method,"POST")==0)
	{
		cgi=1;
	}
	sprintf(path,"htdoc%s",url);
	if(path[strlen(path)-1]=='/')
	{
		strcat(path,"index.html");
	}
//	printf("%s\n",method);
//	printf("%s\n",path);
//	printf("%s\n",val);
//	printf("%s\n",url);
    struct stat st;
	if(stat(path,&st)<0)
	{
	    //printf("qqqq\n");	
		echo_errno(sock,404);
		return (void*)3;

	}
	else{
		if(S_ISDIR(st.st_mode))
		{
			printf("wwwww\n");
			strcpy(path,"htdoc/index.html");
//	printf("%s\n",path);
//	printf("%s\n",val);
//	printf("%s\n",url);
		}
		else if((st.st_mode&S_IXUSR)||(st.st_mode&S_IXGRP)||(st.st_mode&S_IXOTH)){
			printf("haha\n");
			cgi=1;
	}else{}

	}
	//printf("aaaaa\n");
	if(cgi)
	{
	    //printf("bbbbb\n");
	    echo_cgi(sock,path,method,val);
	}
	else{
	//printf("ccccc\n");
		//printf("haha\n");
		clear_header(sock);
		//printf("hei\n");
		echo_www(sock,path,st.st_size);
	}
	

#endif


	close(sock);
	return (void*)0;

}
int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("%s [ip] [port]",argv[0]);
		exit(1);
	}
	int listen_sock=Creat_sock(argv[1],atoi(argv[2]));
	//fcntl(listen_sock,F_SETFL,O_NONBLOCK);
	struct sockaddr_in peer;
	socklen_t len=sizeof(peer);

	
    while(1)
	{
	   int new_fd=accept(listen_sock,(struct sockaddr*)&peer,&len);
	   if(new_fd<0)
	   {
		   continue;
	   }
	   pthread_t pd;
	   pthread_create(&pd,NULL,htpdaccept,(void*)new_fd);
	   pthread_detach(pd);

	}


	return 0;
}
