#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/stat.h>
#include<fcntl.h>
void my_daemon()
{
	int fd0;
	struct sigaction sa;
	umask(0);
	pid_t id=fork();
	if(id!=0)
		exit(0);
	setsid();
	chdir("/");

	close(0);
	fd0=open("/dev/null",O_RDWR);
    dup2(fd0,1);
	dup2(fd0,2);
	sa.sa_handler=SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags=0;
	sigaction(SIGCHLD,&sa,NULL);


}
int main()
{
	int fd1;
	my_daemon();
	while(1)
	{
		fd1=open("dev/pts/",O_RDWR);
		dup2(fd1,1);
		sleep(1);
	    printf("haha\n");
	}

	return 0;
}
