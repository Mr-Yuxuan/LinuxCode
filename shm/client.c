#include"comm.h"
int main()
{
	int shmid=get_shm();
	char*buf=at_shm(shmid);
    int i=0;
while(1)
{
   
  for(;i<SIZE;++i)
  {
	  buf[i]='A';
	  sleep(1);
	  buf[i+1]='\0';
  }
}	
	return 0;
}
