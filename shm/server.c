#include"comm.h"
int main()
{
	int shmid=create_shm();
	while(1)
	{
      char*buf=at_shm(shmid);
	  printf("%s",buf);
	  sleep(1);
	  dt_shm(buf);

	}
	return 0;
}
