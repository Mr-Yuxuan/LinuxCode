/*************************************************************************
	> File Name: coom.c
	> Author: cyx
	> Mail: cyx764@163.com 
	> Created Time: 2016年07月15日 星期五 14时43分38秒
 ************************************************************************/

#include"comm.h"
static int comm_msg(int flag)
{
	key_t key=ftok(_PATH_,_PROID_);
	if(key<0)
	{
		perror("ftok:");
		return 1;
	}
	return msgget(key,flag);
}
int create_q_id()
{
	int flag=IPC_CREAT|IPC_EXCL|0666;
	return comm_msg(flag);
}
int get_q_id()
{
	int flag=IPC_CREAT;
	return comm_msg(flag);

}
void destory(int msg_id)
{
	if(msgctl(msg_id,IPC_RMID,NULL)<0)
	{
		perror("msgctl:");
	}
	return;

}
void send_msg(int msg_id,char*buf,int type)
{
   msginfo msg;
   msg.mtype=type;
   strcpy(msg.mtext,buf);
   if(msgsnd(msg_id,&msg,SIZE,0)<0)
   {
	   perror("msgsnd:");
   }
}
void recv_msg(int msg_id,char*buf,int type)
{
   msginfo msg;
   msg.mtype=type;
   if(msgrcv(msg_id,&msg,SIZE,type,0)<0)
   {
	   perror("msgsnd:");
   }
   strcpy(buf,msg.mtext);
}

