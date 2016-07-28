#include"comm.h"
int comm_sem(int flag)
{
	key_t id=ftok(KEY_PATH,PRO_ID);
	return semget(id,1,flag);
}
void init_sem(int semid,int which)
{
  union semun _semun;
  _semun.val=1;
  semctl(semid,which,SETVAL,_semun);
}
int creat_sem()
{
	int flag=IPC_CREAT|IPC_EXCL|
0644;
	return comm_sem(flag);
}
int get_sem()
{
	int flag=IPC_CREAT;
	return comm_sem(flag);
}
void destory_sem(int semid)
{
   if(semctl(semid,0,IPC_RMID,NULL)<0)
   {
	   perror("semctl:");
   }
}
void P(int semid,int which)
{
   op_sem(semid,-1,which);
}
void V(int semid,int which)
{
   op_sem(semid,1,which);
}
void op_sem(int semid,int op,int which)
{
	struct sembuf sem;
	memset(&sem,'\0',sizeof(sem));
	sem.sem_num=which;
	sem.sem_op=op;
	sem.sem_flg=0;
	semop(semid,&sem,1);
}
