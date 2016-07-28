#include"comm.h"
int main()
{
    pid_t id=fork();
	int sem_id=creat_sem();
	init_sem(sem_id,0);
	if(id==0)
	{
		int semid=get_sem();
		while(1)
		{
		P(semid,0);
			printf("A");
			fflush(stdout);
			printf("A");
			fflush(stdout);
			sleep(1);
		V(semid,0);
		}
	}else
	{
		while(1)
		{
		P(sem_id,0);
			printf("B");
			fflush(stdout);
			printf("B");
			fflush(stdout);
			sleep(1);
		V(sem_id,0);
		}

	}
	destory_sem(sem_id);
	wait(NULL);
	return 0;
}
