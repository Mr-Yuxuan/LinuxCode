#include"comm.h"
int comm_shm(int flag)
{
  key_t id=ftok(PATH,PRO_ID);
  return shmget(id,SIZE,flag);
}
int create_shm()
{
	int flag=IPC_CREAT|IPC_EXCL|0644;
	return comm_shm(flag);
}
int get_shm()
{
	int flag=IPC_CREAT;
	return comm_shm(flag);
}
char* at_shm(int shmid)
{
   return (char*)shmat(shmid,NULL,0);
}
int dt_shm(const void*shmaddr)
{
	return shmdt(shmaddr);
}
void destory(int shmid)
{
	shmctl(shmid,IPC_RMID,NULL);
}
