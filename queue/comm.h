#pragma once
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define _PATH_ "/home/cyx/c"
#define _PROID_ 0
#define SIZE 1024
#include<string.h>
#include<stdlib.h>
#define SERVER 1
#define CLIENT 2
typedef struct _msginfo
{
   long mtype;
   char mtext[SIZE];
}msginfo;

int create_q_id();
int get_q_id();
void destory(int msg_id);
void send_msg(int msg_id,char*buf,int type);
void recv_msg(int msg_id,char*buf,int type);
